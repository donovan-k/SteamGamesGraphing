
#include<iostream>
#include<list>
using namespace std;
class BFSg
{
  int vertex;//number of vertices
  list<int> *al;//points to adjacency lists, might only be used for testing
public:
  BFSg(int vertex);//constructor
  void edgeInstall(int v, int w);//adds edge for testing
  void BFS(int s);//prints BFS traversal
};
