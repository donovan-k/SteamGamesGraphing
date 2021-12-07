#include "force_drawing.h"
#include <random>
#include <cmath>

ForceDirectedDraw::ForceDirectedDraw(Graph * const graph, int width, int height)
  : graph_(graph) {
    width_ = width;
    height_ = height;
}

vector<pair<int, int>> ForceDirectedDraw::drawGraph(const string& filename, int iterations) {
    // method uses the barycentric method to draw graph
    const std::list<int>* adj_list = graph_->getAdjacencyList();
    PNG img(width_, height_);
    float area = width_ * height_;
    vector<pair<int, int>> vector_pos = generateRandomPositions(graph_->size());
    float k = std::sqrt(area / graph_->size());
    vector<pair<float, float>> displacment;
    displacment.resize(graph_->size(), pair<float, float>(0,0));

    float temp = 100;
    for (int t = 0; t < iterations; t++) {
        // calculate repulsive forces
        for (int v = 0; v < vector_pos.size(); v++) {
            for (int u = 0; u < vector_pos.size(); u++) {
                if (v == u) continue;
                // calculate difference vector and unit vector
                pair<float, float> diff_vec = unitVector(vector_pos[v], vector_pos[u], false);
                pair<float, float> unit_vec = unitVector(vector_pos[v], vector_pos[u], true);
                float magnitude = std::sqrt( diff_vec.first * diff_vec.first + diff_vec.second * diff_vec.second );

                // find the displacement vector
                displacment[v].first += unit_vec.first * repulsiveForce(magnitude, k);
                displacment[v].second += unit_vec.second * repulsiveForce(magnitude, k);
            }
        }

        // calculate attractive forces
        for (int i = 0; i < graph_->size(); i++) {
            const std::list<int>& v_list = adj_list[i];
            for (const int edge : v_list) {
                // calculate difference vector and unit vector for vector i
                pair<float, float> diff_vec_i = unitVector(vector_pos[i], vector_pos[i], false);
                pair<float, float> unit_vec_i = unitVector(vector_pos[i], vector_pos[i], true);
                float magnitude_i = std::sqrt( diff_vec_i.first * diff_vec_i.first + diff_vec_i.second * diff_vec_i.second );

                // calculate difference vector and unit vector for vector edge
                pair<float, float> diff_vec = unitVector(vector_pos[edge], vector_pos[edge], false);
                pair<float, float> unit_vec = unitVector(vector_pos[edge], vector_pos[edge], true);
                float magnitude = std::sqrt( diff_vec.first * diff_vec.first + diff_vec.second * diff_vec.second );

                // find the displacement vector for vector i
                displacment[i].first -= unit_vec_i.first * attrForce(magnitude_i, k);
                displacment[i].second -= unit_vec_i.second * attrForce(magnitude_i, k);

                // find the displacement vector for vector edge
                displacment[edge].first += unit_vec.first * attrForce(magnitude, k);
                displacment[edge].second += unit_vec.second * attrForce(magnitude, k);
            }
        }

        // adjust position of each vertex
        for (int v = 0; v < graph_->size(); v++) {
            pair<float, float> v_disp = displacment[v];
            pair<float, float> diff_vec = unitVector(v_disp, v_disp, false);
            float magnitude = std::sqrt( diff_vec.first * diff_vec.first + diff_vec.second * diff_vec.second );
            
            // adjust position of vertex v
            vector_pos[v].first += (v_disp.first / magnitude) * std::min(v_disp.first, temp);
            vector_pos[v].second += (v_disp.second / magnitude) * std::min(v_disp.second, temp);

            // make sure position doesn't go outside of frame
            vector_pos[v].first = std::min(width_ - 1, std::max(0, vector_pos[v].first));
            vector_pos[v].second = std::min(height_ - 1, std::max(0, vector_pos[v].second));
        }

        // cool the temp down as the layout approaches a better config
        temp -= 100 / iterations;
    }

    drawPositions(vector_pos, filename);

    return vector_pos;
}

void ForceDirectedDraw::drawPositions(const vector<pair<int, int>>& positions, const string& filename) {
    PNG *png = new PNG(width_, height_);

    // go through each position and color that pixel black
    for (auto pos : positions) {
        HSLAPixel& pixel = png->getPixel(pos.first, pos.second);
        pixel.h = 0;
        pixel.s = 0;
        pixel.l = 0;
        pixel.a = 1;
    }

    png->writeToFile(filename);
}

void ForceDirectedDraw::drawGameSimilarGraph(string filename, int game_index) {

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

pair<float, float> ForceDirectedDraw::unitVector(const pair<int, int>& pos1, const pair<int, int> pos2, bool unit) {
    pair<float, float> unit_vector(pos2.first - pos1.first, pos2.second - pos1.second);

    // if not wanting unit vector return difference vector
    if (unit == false) {
        return unit_vector;
    }

    // otherwise return a unit vector between vertices
    float magnitude = unit_vector.first * unit_vector.first + unit_vector.second * unit_vector.second;
    magnitude = std::sqrt(magnitude);
    unit_vector.first /= magnitude;
    unit_vector.second /= magnitude;

    return unit_vector;
}
