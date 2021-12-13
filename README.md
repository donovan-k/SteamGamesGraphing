# jmliao2-dkitten2-shackma2-pganot2
Final project for jmliao2-dkitten2-shackma2-pganot2

## Description
Our project makes a graph out of steam game objects and there is an
edge between the two games if they are similar. The graph is contained
using an adjacency list, and there is a traversal of the games
structure, a strongly connected components algorithm, and a force
directed algorithm used to draw an interpretation of the graph.

## Location of code, resources, and presentation
The location of the code is all in the src folder. The data set we
used were parts of a kaggle data set found at the site
https://www.kaggle.com/trolukovich/steam-games-complete-dataset. The
format must have all the columns in this data set. The results of the
code include a force directed graph drawing located in graph.png and
the rest is user interactive so you have to run main to see the output
in terminal.
Video of the presentation can be found here: https://drive.google.com/file/d/1E1Szs0MkrRyXQDGlFdn89EKZdH8ZurCc/view?usp=sharing

## Building
```bash
make # for building the ./steamer executable
make test # for build the ./test executable
```

## Usage
```bash
./steamer <database.csv>
```

**NOTE:** the dataset from kaggle is too large to process in a
comfortable amount of time.  A good number of entries is around 300.

## Testing
```bash
./test
```
