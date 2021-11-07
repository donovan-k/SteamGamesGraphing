## CS 225 Data Structures

## Group Proposal


## Resources
Force Directed Graph Algorithm:
http://cs.brown.edu/people/rtamassi/gdhandbook/chapters/force-directed.pdf
Steam resources:
https://steamdb.info/
https://steamcommunity.com/dev Steam’s official API
https://www.kaggle.com/trolukovich/steam-games-complete-dataset (this one has like 40k games with game descriptions)

## Leading Questions
What do we want to do? 
We want to use the steam data set and we will make a graph where all the nodes are unique games. There will be an edge between nodes if the two games are similar enough to each other. Deciding whether games are “similar enough” can be implemented using a TF-IDF score or similar term frequency score of the tags and/or descriptions of the individual games. If the scores are similar enough within a tolerance then there will be a node between them. We can also use a machine learning algorithm to recommend (draw an edge to another) game/node based on the current game/node.
Implement a GUI to inspect the graph and find similar games. We could have a user input for a certain game then it will output similar games for the user to play.

## What is a successful project?
An app capable of exploring related games from Steam graphically, through organization of similar tags, descriptions and (possibly) ratings.
Dataset Acquisition and Processing

We will be using either https://www.kaggle.com/trolukovich/steam-games-complete-dataset and/or https://steamcommunity.com/dev.
We can use python (pandas) to clean and combine all the data into a csv file or similar format.
Each node will be an individual game and 2 nodes will have an edge between them if they are “similar”.
Data portions with items missing or which have been identified to be wrong will be removed from the set.

## Graph Algorithms
BFS - BFS is a search where all nodes in a given 'layer' are searched before moving to the next 'layer.' It takes a graph as input, and will output nodes. BFS can have O(V+E) time complexity, where V is the number of vertices and E is the number of edges, and space complexity O(V).
Strongly (or almost) connected components - Performs a search, reverses the graph, and reperforms a search to determine which components are strongly connected. Takes a graph as input and outputs a strongly connected graph. Strongly connected components have, ideally, O(V+E) time complexity as well.
Force Directed Graphing - Force Directed Graphing receives data, and uses it to generate visually appealing graphs. The ideal time complexity for Force Directed Graphing should also be O(V+E).



## Timeline
Data acquistion/processing- Completed at least by the end of the first week
> Algorithms and functionality-
>	* BFS- Estimated completion by end of second week.
>	* Strongly Connected Components- Estimated completion by end of second week.
>	* Force Directed Graphing- Estimated completion by end of third week.
>	* GUI learn/creation- Learn things over first two weeks, creation to be decided.
>Final deliverable completion date- Completed by end of fourth week.
