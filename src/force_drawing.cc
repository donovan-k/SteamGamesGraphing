#include "force_drawing.h"
#include <climits>
#include <cmath>
#include <random>
#include <vector>

ForceDirectedDraw::ForceDirectedDraw(Graph *const graph, int width, int height)
    : graph_(graph) {
  width_ = width;
  height_ = height;
}

std::vector<std::pair<float, float>>
ForceDirectedDraw::computePositions(int iterations) {
  // method uses the barycentric method to draw graph
  const std::list<int> *adj_list = graph_->getAdjacencyList();

  const float area = float(width_ * height_);
  const float k = std::sqrt(area / graph_->size());

  std::vector<std::pair<float, float>> position =
      generateRandomPositions(graph_->size());
  std::vector<std::pair<float, float>> displacment(graph_->size());

  float temp = 0.5f * float(std::min(width_, height_));
  const float cool = temp / iterations;
  for (int i = 0; i < iterations; i++) {
    // calculate repulsive forces
    for (int v = 0; v < position.size(); v++) {
      displacment[v] = {0.0, 0.0};
      for (int u = 0; u < position.size(); u++) {
        if (v == u) {
          continue;
        }
        // calculate difference vector and unit vector
        const std::pair<float, float> diff = {
            position[v].first - position[u].first,
            position[v].second - position[u].second,
        };
        const float diff_mag =
            std::sqrt(diff.first * diff.first + diff.second * diff.second);
        if (diff_mag == 0.0) {
          continue;
        }
        const std::pair<float, float> diff_norm = {
            diff.first / diff_mag,
            diff.second / diff_mag,
        };
        // find the displacement vector
        const float force = k * k / diff_mag;
        displacment[v].first += diff_norm.first * force;
        displacment[v].second += diff_norm.second * force;
      }
    }

    // calculate attractive forces
    for (int v = 0; v < graph_->size(); v++) {
      const std::list<int> &v_list = adj_list[v];
      for (const int u : v_list) {
        // calculate difference vector and unit vector for vector i
        const std::pair<float, float> diff_vec = {
            position[v].first - position[u].first,
            position[v].second - position[u].second,
        };
        const float diff_mag = std::sqrt(diff_vec.first * diff_vec.first +
                                         diff_vec.second * diff_vec.second);
        if (diff_mag == 0.0) {
          continue;
        }
        const std::pair<float, float> diff_norm = {
            diff_vec.first / diff_mag,
            diff_vec.second / diff_mag,
        };
        const float force = diff_mag * diff_mag / k;
        // find the displacement vector for vector i
        displacment[v].first -= diff_norm.first * force;
        displacment[v].second -= diff_norm.second * force;

        // find the displacement vector for vector edge
        displacment[u].first += diff_norm.first * force;
        displacment[u].second += diff_norm.first * force;
      }
    }

    // adjust position of each vertex
    for (int v = 0; v < graph_->size(); v++) {
      const std::pair<float, float> disp = displacment[v];
      const float disp_mag =
          std::sqrt(disp.first * disp.first + disp.second * disp.second);
      if (disp_mag == 0.0) {
        continue;
      }
      const std::pair<float, float> disp_norm = {
          disp.first / disp_mag,
          disp.second / disp_mag,
      };

      position[v].first += disp_norm.first * std::min(disp_mag / 2.0f, temp);
      position[v].second += disp_norm.second * std::min(disp_mag / 2.0f, temp);

      // keep the vertex in bounds
      position[v] = {
          std::min(width_ / 2.0f, std::max(-width_ / 2.0f, position[v].first)),
          std::min(height_ / 2.0f,
                   std::max(-height_ / 2.0f, position[v].second)),
      };
    }

    // cool the temp down as the layout approaches a better config
    temp -= cool;
  }

  return position;
}

cs225::PNG ForceDirectedDraw::drawPositions(
    const std::vector<std::pair<float, float>> &positions) {
  cs225::PNG png(width_, height_);

  const std::list<int> *adj_list = graph_->getAdjacencyList();
  // go through each position and color that pixel a random color
  static std::random_device rd;
  static std::default_random_engine rng(rd());
  static std::uniform_real_distribution<> dist(0, 360);

  for (int v = 0; v < positions.size(); v++) {
    const auto &pos = positions[v];
    const int hue = int(dist(rng));
    const float dot_size = 1.0 + std::sqrt(float(adj_list[v].size()));
    const int minx = int((width_ / 2.0f + pos.first) - dot_size / 2.0f);
    const int miny = int((height_ / 2.0f + pos.second) - dot_size / 2.0f);
    for (int x = minx; x < minx + dot_size; x++) {
      if (x < 0 || x >= width_) {
        continue;
      }
      for (int y = miny; y < miny + dot_size; y++) {
        if (y < 0 || y >= height_) {
          continue;
        }
        png.getPixel(x, y) = cs225::HSLAPixel(hue, 1, 0.5, 1.0);
      }
    }
  }

  return png;
}

std::vector<std::pair<float, float>>
ForceDirectedDraw::generateRandomPositions(int size) {
  std::vector<std::pair<float, float>> positions;
  positions.reserve(size);

  // random things
  static std::random_device rd;
  static std::default_random_engine rng(rd());
  std::uniform_real_distribution<> w_dist(-width_ / 2.0f, width_ / 2.0f);
  std::uniform_real_distribution<> h_dist(-height_ / 2.0f, height_ / 2.0f);
  for (int i = 0; i < size; i++) {
    positions.push_back({w_dist(rng), h_dist(rng)});
  }

  return positions;
}
