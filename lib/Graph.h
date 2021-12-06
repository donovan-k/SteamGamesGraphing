#ifndef SCC_H
#define SCC_H

#include <iostream>
#include <list>
#include <stack>
#include <vector>

#include "similar.h"
#include "game.h"

using std::vector;

class Graph {
  int V;                        // No. of vertices
  std::list<int> *adj;          // An array of adjacency lists
  const vector<Game>& games_;   // Reference to the vector of games
  

  // Fills Stack with vertices (in increasing order of finishing
  // times). The top element of stack has the maximum finishing
  // time
  void fillOrder(int v, bool visited[], std::stack<int> &Stack);

  // A recursive function to print DFS starting from v
  void DFSUtil(int v, bool visited[]);

public:
  // constructor for creating empty graph with size V
  Graph(int V);

  // constructor for creating graph from vector of games
  Graph(const vector<Game>& games);
  
  // destructor
  ~Graph();

  // adds an edge in the graph from vertex v to vertex w
  void addEdge(int v, int w);

  // The main function that finds and prints strongly connected
  // components
  void printSCCs();

  // Function that returns reverse (or transpose) of this graph
  Graph getTranspose();

  // Get game from index position
  Game getGame(int index) const;

  // Get games that are similar (have edges) to game at index ind
  vector<Game> getSimilarGames(int ind) const;

  // Get method for adjacency list
  std::list<int> * getAdjacencyList();

};

#endif // SCC_H
