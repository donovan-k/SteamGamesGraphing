#include "bfs.h"
#include "graph.h"
#include <queue>
#include <vector>

BFSg::BFSg(Graph *graphx) {
  vert = graphx->size(); // sets the size of the graph
  al = graphx->getAdjacencyList();
}
std::vector<int> BFSg::BFS(int index, int size) { // visits each vertex
  std::vector<int> result;
  result.reserve(size);
  std::vector<bool> wasVisited(vert, false);
  std::queue<int> Q;        // creates a queue to keep track of the search
  wasVisited[index] = true; // current node has been visited
  Q.push(index);            // queue initial node
  list<int>::iterator it;   // iterator to find adjacent vertecies
  while (!Q.empty() &&
         result.size() < size) { // search through until queue is empty
    index = Q.front();           // set searcher to the front of  the queue
    // cout << s << " \n";//textual feedback
    Q.pop(); // remove from queue, it is being checked
    for (it = al[index].begin(); it != al[index].end(); ++it) {
      if (!wasVisited[*it]) {
        wasVisited[*it] =
            true; // if it has not been visited, mark as visited and queue it up
        Q.push(*it);
        result.push_back(*it);
      }
    }
  }
  return result;
}
