#include "force_drawing.h"
#include <cmath>
#include <random>

ForceDirectedDraw::ForceDirectedDraw(Graph *const graph, int width, int height)
    : graph_(graph) {
  width_ = width;
  height_ = height;
}

vector<pair<int, int>> ForceDirectedDraw::drawGraph(const string &filename,
                                                    int iterations) {
  // method uses the barycentric method to draw graph
  const std::list<int> *adj_list = graph_->getAdjacencyList();
  std::cout << graph_->size() << std::endl;
  float area = width_ * height_;
  vector<pair<int, int>> vector_pos = generateRandomPositions(graph_->size());

  // values for computation
  float k = std::sqrt(area / graph_->size());
  vector<pair<float, float>> displacment;
  displacment.resize(graph_->size(), pair<float, float>(0.0, 0.0));

  // min and max position holders
  pair<int, int> min(INT32_MAX, INT32_MAX);
  pair<int, int> max(INT32_MIN, INT32_MIN);

  float temp = std::log10(iterations);
  for (int t = 0; t < iterations; t++) {
    // calculate repulsive forces
    for (int v = 0; v < vector_pos.size(); v++) {
      displacment[v].first = 0.0;
      displacment[v].second = 0.0;
      for (int u = 0; u < vector_pos.size(); u++) {
        if (v == u)
          continue;
        // calculate difference vector and unit vector
        pair<float, float> diff_vec =
            unitVector(vector_pos[v], vector_pos[u], false);
        pair<float, float> unit_vec =
            unitVector(vector_pos[v], vector_pos[u], true);
        float magnitude = std::sqrt(diff_vec.first * diff_vec.first +
                                    diff_vec.second * diff_vec.second);

        // find the displacement vector
        displacment[v].first += unit_vec.first * repulsiveForce(magnitude, k);
        displacment[v].second += unit_vec.second * repulsiveForce(magnitude, k);
      }
    }

    // calculate attractive forces
    for (int i = 0; i < graph_->size(); i++) {
      const std::list<int> &v_list = adj_list[i];
      for (const int edge : v_list) {
        // calculate difference vector and unit vector for vector i
        pair<float, float> diff_vec =
            unitVector(vector_pos[i], vector_pos[edge], false);
        pair<float, float> unit_vec =
            unitVector(vector_pos[i], vector_pos[edge], true);
        float magnitude = std::sqrt(diff_vec.first * diff_vec.first +
                                    diff_vec.second * diff_vec.second);

        // find the displacement vector for vector i
        displacment[i].first -= unit_vec.first * attrForce(magnitude, k);
        displacment[i].second -= unit_vec.second * attrForce(magnitude, k);

        // find the displacement vector for vector edge
        displacment[edge].first += unit_vec.first * attrForce(magnitude, k);
        displacment[edge].second += unit_vec.second * attrForce(magnitude, k);
      }
    }

    // adjust position of each vertex
    for (int v = 0; v < graph_->size(); v++) {
      pair<float, float> v_disp = displacment[v];
      float magnitude = std::sqrt(v_disp.first * v_disp.first +
                                  v_disp.second * v_disp.second);

      // adjust position of vertex v
      vector_pos[v].first +=
          (v_disp.first / magnitude) * std::min(v_disp.first, temp);
      vector_pos[v].second +=
          (v_disp.second / magnitude) * std::min(v_disp.second, temp);

      // find min and max of positions
      if (vector_pos[v].first < min.first) {
        min.first = vector_pos[v].first;
      }
      if (vector_pos[v].first > max.first) {
        max.first = vector_pos[v].first;
      }
      if (vector_pos[v].second < min.second) {
        min.second = vector_pos[v].second;
      }
      if (vector_pos[v].second > max.second) {
        max.second = vector_pos[v].second;
      }
    }

    // cool the temp down as the layout approaches a better config
    temp -= std::log10(iterations) / iterations;
  }

  normalizePositions(vector_pos, min, max);

  drawPositions(vector_pos, filename);

  return vector_pos;
}

void ForceDirectedDraw::normalizePositions(vector<pair<int, int>> &positions,
                                           pair<int, int> &min,
                                           pair<int, int> &max) {
  for (int p = 0; p < positions.size(); p++) {
    double pf =
        ((double)(positions[p].first - min.first) / (max.first - min.first)) *
        (width_ - 1);
    double ps = ((double)(positions[p].second - min.second) /
                 (max.second - min.second)) *
                (height_ - 1);
    positions[p].first = pf;
    positions[p].second = ps;
  }
}

void ForceDirectedDraw::drawPositions(const vector<pair<int, int>> &positions,
                                      const string &filename) {
  PNG *png = new PNG(width_, height_);

  // go through each position and color that pixel a random color
  int pixel_size = width_ * height_ / (1000);
  double h = 0;
  for (auto pos : positions) {
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(0, 360);
    h = dist(e2);
    HSLAPixel pixel_copy(h, 1, 0.5, 0.99);
    HSLAPixel &pixel = png->getPixel(pos.first, pos.second);

    pixel = pixel_copy;
  }

  png->writeToFile(filename);
}

vector<pair<int, int>> ForceDirectedDraw::generateRandomPositions(int size) {
  vector<pair<int, int>> positions;
  positions.reserve(size);

  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      pair<int, int> pos(i, j);
      positions.push_back(pos);
    }
  }

  // shuffle order of list
  std::random_device dev;
  std::mt19937 rng(dev());
  std::shuffle(positions.begin(), positions.end(), dev);

  // check edge case
  if (size >= width_ * height_) {
    return positions;
  }

  // Begin and End iterator
  auto first = positions.begin();
  auto last = positions.begin() + size;

  // Copy the element
  vector<pair<int, int>> positions_(first, last);

  return positions_;
}

float ForceDirectedDraw::repulsiveForce(float force, float k) {
  return k * k / force;
}

float ForceDirectedDraw::attrForce(float force, float k) {
  return force * force / k;
}

pair<float, float> ForceDirectedDraw::unitVector(const pair<int, int> &pos1,
                                                 const pair<int, int> pos2,
                                                 bool unit) {
  pair<float, float> unit_vector(pos2.first - pos1.first,
                                 pos2.second - pos1.second);

  // if not wanting unit vector return difference vector
  if (unit == false) {
    return unit_vector;
  }

  // otherwise return a unit vector between vertices
  float magnitude = unit_vector.first * unit_vector.first +
                    unit_vector.second * unit_vector.second;
  magnitude = std::sqrt(magnitude);
  unit_vector.first /= magnitude;
  unit_vector.second /= magnitude;

  return unit_vector;
}
