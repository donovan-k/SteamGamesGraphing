#include "bfs.h"
#include "graph.h"
#include <list>

BFSg::BFSg(Graph *graphx) {
  vert = graphx->size(); // sets the size of the graph
  al = graphx->getAdjacencyList();
}
void BFSg::BFS(int s) { // visits each vertex
  std::vector<bool> wasVisited(vert, false);
  list<int> Q;            // creates a queue to keep track of the search
  wasVisited[s] = true;   // current node has been visited
  Q.push_back(s);         // queue initial node
  list<int>::iterator it; // iterator to find adjacent vertecies
  while (!Q.empty()) {    // search through until queue is empty
    s = Q.front();        // set searcher to the front of  the queue
    // cout << s << " \n";//textual feedback
    Q.pop_front(); // remove from queue, it is being checked
    for (it = al[s].begin(); it != al[s].end(); ++it) {
      if (!wasVisited[*it]) {
        wasVisited[*it] =
            true; // if it has not been visited, mark as visited and queue it up
        Q.push_back(*it);
      }
    }
  }
}
