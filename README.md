# jmliao2-dkitten2-shackma2-pganot2
Final project for jmliao2-dkitten2-shackma2-pganot2

## Description
Our project makes a graph out of steam game objects and there is an edge between the two games if they are similar. The graph is contained using an adjacency list, and there is a traversal of the games structure, a strongly connected components algorithm, and a force directed algorithm used to draw an interpretation of the graph.

## Location of code and resources
The location of the code is all in the src folder. The data set we used were parts of a kaggle data set found at the site https://www.kaggle.com/trolukovich/steam-games-complete-dataset. The format must have all the columns in this data set. The results of the code include a force directed graph drawing located in graph.png and the rest is user interactive so you have to run main to see the output in terminal.

## Instructions for executing code
Once you have VS Code able to run c++ code in clang++, you can download our code to a local repository. To run the main file, you can make the file using the command ```make CXX=clang++```. Then to run the file use the command ```./steamer <csv file>```. Where the csv file is formatted like the one. The main example is to use test.csv. The output will be in terminal and a png file located at graph.png

## Instructions for running tests code
Once you have VS Code able to run c++ code in clang++, you can download our code to a local repository. To run the test file, you can make the file using the command ```make CXX=clang++ test```. Then to run the file use the command ```./test```. We tested the main components such as the bfs traversal, strongly connected components, and the similar class which is used to make edges between games.
