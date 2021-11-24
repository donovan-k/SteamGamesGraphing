
#include<iostream>
#include<list>
using namespace std;
class Graph//this may need altered
{
  int vertex;//number of vertices
  list<int> *al;//points to adjacency lists
public:
  Graph(int vertex);//constructor
  void addEdge(int v, int w);//adds edge and may not be necessary
  void BFS(int s);//prints BFS traversal
};
