#ifndef SCC_H
#define SCC_H

#include <iostream>
#include <list>
#include <stack>

class Graph {
  int V;               // No. of vertices
  std::list<int> *adj; // An array of adjacency lists

  // Fills Stack with vertices (in increasing order of finishing
  // times). The top element of stack has the maximum finishing
  // time
  void fillOrder(int v, bool visited[], std::stack<int> &Stack);

  // A recursive function to print DFS starting from v
  void DFSUtil(int v, bool visited[]);

public:
  Graph(int V);
  void addEdge(int v, int w);

  // The main function that finds and prints strongly connected
  // components
  void printSCCs();

  // Function that returns reverse (or transpose) of this graph
  Graph getTranspose();
};

#endif // SCC_H
