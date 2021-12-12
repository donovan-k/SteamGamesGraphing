#pragma once

#include <string>
#include <utility>
#include <vector>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "graph.h"

class ForceDirectedDraw {
public:
  // constructs a force directed object
  ForceDirectedDraw(Graph *const graph, int width, int height);

  // draws the graph on a png and saves to file "filename"
  std::vector<std::pair<float, float>> computePositions(int iterations);
  // draws the positions of each vertex on a png
  cs225::PNG
  drawPositions(const std::vector<std::pair<float, float>> &positions);

private:
  Graph *const graph_;
  int width_, height_;

  // finds the difference/unit vector of 2 vectors (unit when unit == true)
  // (different when unit == false)
  std::pair<float, float> unitVector(const std::pair<float, float> &pos1,
                                     const std::pair<float, float> pos2,
                                     bool unit);

  // generates a random sequence of positions in the image to draw a vertices
  // (nodes) of size
  std::vector<std::pair<float, float>> generateRandomPositions(int size);
};
