Introduction
This project, steamer, is a program which generates game recommendations
based on provided tags, and develops a visualization of the similarities of
games. This is accomplished by first developing graphs of similar games, and 
creating a force directed graph of those graphs and by performing BFS traversal 
of a strongly connected components graph

Overview
The program first creates a vector of games, then generates a strongly connected 
components graph and BFS traversal graph of that vector. It will the draw the graph 
using the force directed method and save that graph as a .png file. From there, it 
will group the graph according to genre. The user is then provided with an 
opportunity to enter the title of a game. The program will receive the file, compare
it to the vector of games, and generate an index. The index is used in a BFS traversal 
to output the twenty most similar games.

Individual discussions

BFS
The Breadth First Search algorithm was used in the process of game recommendation.
The BFS files contained the ability to traverse a strongly connected adjency list to
provide the twenty titles which are closest to the inputted, as determined by the similar
and strongly connected components portions. 

Conclusion
This project was an exercise in the production of a complete program, beginning with the
idea of what we want it to do, and then creating features and methods to achieve that goal.
This process gave great insight in not only the creation processes of programming and data 
structures, but the intricacies of group work. Furthermore, this exercise proved the methods
used were functional in a practical application. The outputs work, and a force directed graph
is generated, which proves the efficacy of our solution.
