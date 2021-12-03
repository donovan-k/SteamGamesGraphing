#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "game.h"
#include "input.h"

int main(int argc, char* argv[]) {
  std::vector<Game> games;

  std::ifstream fin("test.csv");
  if (!fin.is_open()) {
    std::cerr << argv[0] << ": cannot open 'test.csv' for reading: No such file or directory\n";
    abort();
  }
  std::string line;
  getline(fin, line);
  while (getline(fin, line)) {
    games.push_back(parse_game(line));
  }

  std::cout << "We have " << games.size() << " games in total!\n";
  for (const Game& game : games) {
    std::cout << game.name << ": " << game.popular_tags << "\n";
  }
}
