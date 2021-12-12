#include "Graph.h"
#include "game.h"
#include <list>
#include <iostream>
#include <string>
using namespace std;
class BFSg
{
  int vert;//number of vertices
  list<int> *al;//points to adjacency lists
public:
  BFSg(Graph * graphx);//constructor
  void BFS(int s, vector<Game> games);//prints BFS traversal
};
