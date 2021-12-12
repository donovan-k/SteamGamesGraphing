#include "graph.h"
#include <iostream>
#include <list>

class BFSg {
  int vert;           // number of vertices
  std::list<int> *al; // points to adjacency lists
public:
  BFSg(Graph *graphx);                       // constructor
  std::vector<int> BFS(int index, int size); // prints BFS traversal
};
