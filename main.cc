#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bfs.h"
#include "force_drawing.h"
#include "game.h"
#include "graph.h"
#include "input.h"

int main(int argc, char *argv[]) {
  std::vector<Game> games;

  std::string line;
  for (std::size_t i = 1; i < argc; ++i) {
    std::ifstream fin(argv[i]);
    if (!fin.is_open()) {
      std::cerr << argv[0] << ": cannot open '" << argv[i]
                << "' for reading: No such file or directory\n";
      return 1;
    }

    std::getline(fin, line);
    while (std::getline(fin, line)) {
      games.push_back(parse_game(line));
    }
  }

  Graph graph(&games, 0.3f);
  BFSg bfsg(&graph);

  ForceDirectedDraw draw(&graph, 1000, 1000);
  draw.drawPositions(draw.computePositions(10)).writeToFile("graph.png");

  std::cout << "It looks like these groupings exist!\n";
  const std::vector<std::vector<int>> sccs = graph.getSCCs();
  int genre_num = 1;
  for (const std::vector<int> &scc : sccs) {
    std::cout << "\tGenre #" << (genre_num++) << ":\n";
    for (int index : scc) {
      std::cout << "\t\t" << graph.getGame(index).name << "\n";
    }
  }

  std::string query;
  while (true) {
    std::cout
        << "Please enter your favorite game, and will try to find similar ones!"
           "\nPress enter with an empty query to quit."
           "\n\tQuery: ";
    std::getline(std::cin, query);
    if (query == "") {
      break;
    }
    int index = -1;
    for (int i = 0; i < graph.size(); i++) {
      if (graph.getGame(i).name == query) {
        index = i;
        break;
      }
    }
    if (index == -1) {
      std::cerr << "Sorry, I could not find that title within the databases.  "
                   "Please ensure that you entered the title correctly.";
      continue;
    }
    // BFS
    std::cout << "These games are similar to " << query << "!\n";
    for (const int similar_game_index : bfsg.BFS(index, 20)) {
      const Game &g = graph.getGame(similar_game_index);
      std::cout << g.name << " by " << g.developer << ": " << g.desc_snippet
                << "\n";
    }
  }
}
