#include "BFS.h"
#include<queue>
#include<list>

Graph::Graph(int vertex){
  this->vertex = vertex;//updates BFS vertex
  al = new list<int>[vertex];//creates a new adjacency list
}
void Graph::addEdge(int v, int w){
  al[v].push_back(w);//adds edge by adding something to the al
}
void Graph::BFS(int s){//visits each vertex
  bool *wasVisited = new bool[vertex];//makes pointer to an array keeping track of whether or not the node has been checked
  for(int i = 0; i < vertex; i++)
    wasVisited[i] = false;//goes through each of the nodes and sets their visited value to unvisited
 list<int> Q;//creates a queue to keep track of the search
  wasVisited[s] = true;//current node has been visited
  Q.push_back(s);//queue initial node
  list<int>::iterator it;//iterator to find adjacent vertecies
  while(!Q.empty()){//search through until queue is empty
    s = Q.front();//set searcher to the front of  the queue
    cout << s << " ";//textual feedback
    Q.pop_front();//remove from queue, it is being checked
    for(it = al[s].begin(); it != al[s].end(); ++it){
      if(!wasVisited[*it]){
        wasVisited[*it] = true;//if it has not been visited, mark as visited and queue it up
        Q.push_back(*it);
      }
    }
  }
}