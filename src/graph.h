#ifndef SCC_H
#define SCC_H

#include <iostream>
#include <list>
#include <stack>
#include <vector>

#include "game.h"

class Graph {
private:
  int V;                           // No. of vertices
  std::list<int> *adj;             // An array of adjacency lists
  std::vector<Game> *const games_; // Reference to the vector of games

  // Fills Stack with vertices (in increasing order of finishing
  // times). The top element of stack has the maximum finishing
  // time
  void fillOrder(int v, std::vector<bool> &visited, std::stack<int> &Stack);

  // A recursive function to print DFS starting from v
  void DFSUtil(int v, std::vector<bool> &visited);

  // A recursive function to push the DFS to a vector starting from v
  void DFSUtil(int v, std::vector<bool> &visited, std::vector<int> &component);

public:
  // constructor for creating empty graph with size V
  Graph(int V);

  // constructor for creating graph from vector of games
  Graph(std::vector<Game> *const games, float threshold);

  // destructor
  ~Graph();

  // adds an edge in the graph from vertex v to vertex w
  void addEdge(int v, int w);

  // The main function that finds and prints strongly connected
  // components
  void printSCCs();

  /* Function that returns a vector of vectors of strongly connected integers */
  std::vector<std::vector<int>> getSCCs();

  // Function that returns reverse (or transpose) of this graph
  Graph getTranspose();

  // Get game from index position
  Game getGame(int index) const;

  // Get games that are similar (have edges) to game at index ind
  std::vector<Game> getSimilarGames(int ind) const;

  // Get games that are similar (have edges) to game at index ind
  // std::list<int> getSimilarGames(int ind) const;

  // check if two games are similar (have edges between them)
  bool areSimilar(int i, int j) const;

  // Get method for adjacency list
  std::list<int> *getAdjacencyList();

  // returns the number of vertices in the adjacency list
  int size() const;
  // Checks if a sub-graph is strongly connected;
  bool isStronglyConnected();
};

#endif // SCC_H
