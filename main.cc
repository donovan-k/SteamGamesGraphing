#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

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

  Graph graph(&games);

  __pid_t pid = fork();
  if (pid == 0) {
    ForceDirectedDraw draw(&graph, 100, 100);
    draw.drawGraph("graph.png", 1);
    exit(0);
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
    const vector<Game> &similar = graph.getSimilarGames(index);
    for (const Game &g : similar) {
      std::cout << g.name << " by " << g.developer << ": " << g.desc_snippet
                << "\n";
    }
  }

  int stat;
  wait(&stat);
  return stat;
}
