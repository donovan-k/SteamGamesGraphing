#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "game.h"
#include "input.h"
#include "Graph.h"
#include "force_drawing.h"
#include "BFS.h"

int main(int argc, char* argv[]) {
  std::vector<Game> games;

  std::string line;
  for (std::size_t i = 1; i < argc; ++i) {
    std::ifstream fin(argv[i]);
    if (!fin.is_open()) {
      std::cerr << argv[0] << ": cannot open '" << argv[i] <<
        "' for reading: No such file or directory\n";
      abort();
    }

    getline(fin, line);
    while (getline(fin, line)) {
      games.push_back(parse_game(line));
    }
  }

  Graph * graph = new Graph(&games);

  for (int i = 0; i < graph->size(); i++) {
    vector<Game> gs = graph->getSimilarGames(i);
    std::cout << graph->getGame(i).name << std::endl;
    for (Game g : gs) {
      std::cout << g.name << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
  }
  std::cout << "Recommendations based on user input: \n";
  BFSg * graphene = new BFSg(graph);
  graphene->BFS( 4, games);
  ForceDirectedDraw draw(graph, 100, 100);
  draw.drawGraph("graph.png", 1);

}
    }
    std::cout << std::endl;
    std::cout << std::endl;
  }

  ForceDirectedDraw draw(graph, 100, 100);
  draw.drawGraph("graph.png", 1);
}
