#include "BFS.h"
#include "Graph.h"
#include "game.h"
#include <list>
#include <iostream>
#include <string>

BFSg::BFSg(Graph * graphx){
  vert = graphx->size();//sets the size of the graph
  al = graphx->getAdjacencyList();
}

void BFSg::BFS(int s, vector<Game> games){//visits each vertex

  bool *wasVisited = new bool[vert];//makes pointer to an array keeping track of whether or not the node has been checked
  for(int i = 0; i < vert; i++)
    wasVisited[i] = false;//goes through each of the nodes and sets their visited value to unvisited
  list<int> Q;//creates a queue to keep track of the search
  wasVisited[s] = true;//current node has been visited
  Q.push_back(s);//queue initial node
  list<int>::iterator it;//iterator to find adjacent vertecies
  while(!Q.empty() && int j <=20){//search through until queue is empty
    s = Q.front();//set searcher to the front of  the queue
    cout << games[s].name << " \n"; //textual feedback
    Q.pop_front();//remove from queue, it is being checked
    for(it = al[s].begin(); it != al[s].end(); ++it){
      if(!wasVisited[*it]){
        wasVisited[*it] = true;//if it has not been visited, mark as visited and queue it up
        Q.push_back(*it)
        j++
      }
    }
  }
}
