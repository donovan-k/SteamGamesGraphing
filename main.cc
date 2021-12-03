#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "game.h"
#include "input.h"

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

  std::cout << "We have " << games.size() << " games in total!\n";
  for (const Game& game : games) {
    std::cout << game.name << ": " << game.popular_tags << "\n";
  }
}