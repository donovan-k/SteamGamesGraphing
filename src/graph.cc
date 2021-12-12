#include <list>
#include <stack>

#include "graph.h"

// constructor for creating empty graph with size V
Graph::Graph(int V) : games_(nullptr) {
  this->V = V;
  adj = new std::list<int>[V];
}

// constructor for creating graph from vector of games
Graph::Graph(std::vector<Game> *const games) : games_(games) {
  V = games->size();
  adj = new std::list<int>[V];

  // goes through each game and compares it with every other game to
  // see if they are similar and put an edge between the index positions
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      if (i == j)
        continue;
      if (Similar::areSimilar(games->at(i), games->at(j), 0.9)) {
        addEdge(i, j);
      }
    }
  }
}

// destructor
Graph::~Graph() { delete[] adj; }

// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, std::vector<bool> &visited) {
  // Mark the current node as visited and print it
  visited[v] = true;
  // cout << v << " ";

  // Recur for all the vertices adjacent to this vertex
  std::list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!visited[*i])
      DFSUtil(*i, visited);
}

void Graph::DFSUtil(int v, std::vector<bool> &visited,
                    std::vector<int> &component) {
  // Mark the current node as visited and print it
  visited[v] = true;
  component.push_back(v);
  // cout << v << " ";

  // Recur for all the vertices adjacent to this vertex
  std::list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!visited[*i])
      DFSUtil(*i, visited, component);
}

Graph Graph::getTranspose() {
  Graph g(V);
  for (int v = 0; v < V; v++) {
    // Recur for all the vertices adjacent to this vertex
    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
      g.adj[*i].push_back(v);
    }
  }
  return g;
}

void Graph::addEdge(int v, int w) {
  adj[v].push_back(w); // Add w to v’s list.
}

void Graph::fillOrder(int v, std::vector<bool> &visited, std::stack<int> &s) {
  // Mark the current node as visited and print it
  visited[v] = true;

  // Recur for all the vertices adjacent to this vertex
  std::list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!visited[*i])
      fillOrder(*i, visited, s);

  // All vertices reachable from v are processed by now, push v
  s.push(v);
}

// The main function that finds and prints all strongly connected
// components
void Graph::printSCCs() {
  std::stack<int> s;

  // Mark all the vertices as not visited (For first DFS)
  std::vector<bool> visited(V, false);

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
      // cout << endl;
    }
  }
}

std::vector<std::vector<int>> Graph::getSCCs() {

  std::vector<std::vector<int>> SCCs;

  std::stack<int> s;

  // Mark all the vertices as not visited (For first DFS)
  std::vector<bool> visited(V, false);

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
  while (!s.empty()) {
    // Pop a vertex from stack
    int v = s.top();
    s.pop();

    // Print Strongly connected component of the popped vertex
    if (visited[v] == false) {
      std::vector<int> current_component;
      gr.DFSUtil(v, visited, current_component);
      SCCs.push_back(current_component);
      // cout << endl;
    }
  }
  return SCCs;
}

// Get game from index position
Game Graph::getGame(int index) const { return games_->at(index); }

// Get games that are similar (have edges) to game at index ind
std::vector<Game> Graph::getSimilarGames(int ind) const {
  // get the list of siimlar games
  std::list<int> similar_indexes = adj[ind];

  // reserve space for the similar games vector
  std::vector<Game> similar_games;
  similar_games.reserve(similar_indexes.size());

  // from the index of the similar game extract the game object
  // associated with it
  for (int i : similar_indexes) {
    similar_games.push_back(games_->at(i));
  }

  return similar_games;
}

// list<int> Graph::getSimilarGames(int ind) const {
//   // get the list of siimlar games
//   list<int> similar_indexes = adj[ind];

//   return similar_indexes;
// }

bool Graph::areSimilar(int i, int j) const {
  std::list<int> similar_games = adj[i];

  for (int k : similar_games) {
    if (k == j) {
      return true;
    }
  }

  return false;
}

std::list<int> *Graph::getAdjacencyList() { return adj; }

int Graph::size() const { return V; }

bool Graph::isStronglyConnected() {
  // Mark all the vertices as not visited (For first DFS)
  std::vector<bool> visited(V, false);

  // Do DFS traversal starting from first vertex.
  DFSUtil(0, visited);

  // If DFS traversal doesn’t visit all vertices, then return false.
  for (int i = 0; i < V; i++)
    if (visited[i] == false)
      return false;

  // Creates a reversed graph
  Graph gr = getTranspose();

  // Mark all the vertices as not visited (For second DFS)
  for (int i = 0; i < V; i++)
    visited[i] = false;

  // Do DFS for reversed graph starting from first vertex.
  //  Starting Vertex must be same starting point of first DFS
  gr.DFSUtil(0, visited);

  // If all vertices are not visited in second DFS, then
  // return false
  for (int i = 0; i < V; i++)
    if (visited[i] == false)
      return false;

  return true;
}
