#include <iostream>
#include <list>
#include <stack>

#include "Graph.h"

using namespace std;

// constructor for creating empty graph with size V
Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];
}

// constructor for creating graph from vector of games
Graph::Graph(const vector<Game>& games) {
  V = games.size();
  adj = new list<int>[V];
  games_ = games;

  // goes through each game and compares it with every other game to 
  // see if they are similar and put an edge between the index positions
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      if (i == j) continue;
      if (Similar::areSimilar(games[i], games[j])) {
        addEdge(i, j);
      }
    }
  }
}

// destructor
Graph::~Graph() {
  delete[] adj;
}

// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, bool visited[]) {
  // Mark the current node as visited and print it
  visited[v] = true;
  cout << v << " ";

  // Recur for all the vertices adjacent to this vertex
  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!visited[*i])
      DFSUtil(*i, visited);
}

Graph Graph::getTranspose() {
  Graph g(V);
  for (int v = 0; v < V; v++) {
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
      g.adj[*i].push_back(v);
    }
  }
  return g;
}

void Graph::addEdge(int v, int w) {
  adj[v].push_back(w); // Add w to v’s list.
}

void Graph::fillOrder(int v, bool visited[], stack<int> &s) {
  // Mark the current node as visited and print it
  visited[v] = true;

  // Recur for all the vertices adjacent to this vertex
  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!visited[*i])
      fillOrder(*i, visited, s);

  // All vertices reachable from v are processed by now, push v
  s.push(v);
}

// The main function that finds and prints all strongly connected
// components
void Graph::printSCCs() {
  stack<int> s;

  // Mark all the vertices as not visited (For first DFS)
  bool *visited = new bool[V];
  for (int i = 0; i < V; i++)
    visited[i] = false;

  // Fill vertices in stack according to their finishing times
  for (int i = 0; i < V; i++)
    if (visited[i] == false)
      fillOrder(i, visited, s);

  // Create a reversed graph
  Graph gr = getTranspose();

  // Mark all the vertices as not visited (For second DFS)
  for (int i = 0; i < V; i++)
    visited[i] = false;

  // Now process all vertices in order defined by Stack
  while (s.empty() == false) {
    // Pop a vertex from stack
    int v = s.top();
    s.pop();

    // Print Strongly connected component of the popped vertex
    if (visited[v] == false) {
      gr.DFSUtil(v, visited);
      cout << endl;
    }
  }
}

// Get game from index position
Game Graph::getGame(int index) const {
  return games_.at(index);
}

// Get games that are similar (have edges) to game at index ind
vector<Game> Graph::getSimilarGames(int ind) const {
  // get the list of siimlar games
  list<int> similar_indexes = adj[ind];

  // reserve space for the similar games vector
  vector<Game> similar_games;
  similar_games.reserve(similar_indexes.size());

  // from the index of the similar game extract the game object 
  // associated with it
  for (int i : similar_indexes) {
    similar_games.push_back(games_.at(i));
  }

  return similar_games;
}

std::list<int> * Graph::getAdjacencyList() {
  return adj;
}
