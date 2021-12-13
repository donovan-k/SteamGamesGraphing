## Introduction

This project, steamer, is a program which generates game
recommendations based on provided tags, and develops a visualization
of the similarities of games. This is accomplished by first developing
graphs of similar games, and creating a force directed graph of those
graphs and by performing BFS traversal of a strongly connected
components graph

## Overview

The program first creates a vector of games, then generates a strongly
connected components graph and BFS traversal graph of that vector. It
will the draw the graph using the force directed method and save that
graph as a .png file. From there, it will group the graph according to
genre. The user is then provided with an opportunity to enter the
title of a game. The program will receive the file, compare it to the
vector of games, and generate an index. The index is used in a BFS
traversal to output the twenty most similar games.

## Individual discussions

### BFS Traversal
The Breadth First Search algorithm was used in the process of game
recommendation.  The BFS files contained the ability to traverse a
strongly connected adjency list to provide the twenty titles which are
closest to the inputted, as determined by the similar and strongly
connected components portions.

### Kosaraju's Algorithm for Strongly Connected Components

This algorithm was used in the process of genre creation.  Since our
graph is created from a vector of Game objects with edges determined
using the similar class, we can simply use the algorithm to find the
strongly connected components of specific indices from the vector of
Game objects.  This then allows us to separate games into similar game
genres.  The output of the function that we used (getSCCs) gives us a
2D vector of integers that represent the index of a specific game from
the vector of Game objects, with each inside vector being a separate
genre of games.

### Force Directed Graphing Algorithm

The Force Directed Graphing algorithm was used in the process of
interpreting the graph as an image.  It uses the algorithm from
https://cs.brown.edu/people/rtamassi/gdhandbook/chapters/force-directed.pdf
page 5 to move positions of graph nodes based on their edges with each
other. The output of this function produces a png image that is saved
in whatever file is stated in the main program (usually graph.png).

## What was left behind

Within our proposal we imagined an interactive GUI that the user could
click through to interface with *steamer*.  However, we realized that
the team simply did not have much GUI experience to implement such a
feature, and we did not have the time to learn those skills if we were
to keep developing *steamer*.  As such, we opted for a PNG graphic and
a CLI rather than a GUI.

## Conclusion

This project was an exercise in the production of a complete program,
beginning with the idea of what we want it to do, and then creating
features and methods to achieve that goal.  This process gave great
insight in not only the creation processes of programming and data
structures, but the intricacies of group work.  Furthermore, this
exercise proved the methods used were functional in a practical
application.  The outputs work, and a force directed graph is
generated, which proves the efficacy of our solution.  For a full
presentation, the video can be found here:
https://drive.google.com/file/d/1E1Szs0MkrRyXQDGlFdn89EKZdH8ZurCc/view?usp=sharing
