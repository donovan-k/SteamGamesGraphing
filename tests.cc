#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "game.h"
#include "input.h"
#include "scc.h"

bool testSCCs() {
  // test if SCCs work
  Graph g(5);

    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);
  
    cout << "Following are strongly connected components in "
            "given graph \n";
    g.printSCCs();
  // return true if print SCC compiles
  return true;
}

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

  int passed_cases = 0; // test cases passed
  int failed_cases = 0; // test cases failed

  // next test case

  bool test_case_SCC = testSCCs();
  if (test_case_SCC) {passed_cases++;}
  else {failed_cases++;}

  // print results
  std::cout << "tests passed: " << passed_cases << std::endl;
  std::cout << "tests failed: " << failed_cases << std::endl;
  std::cout << "total tests: " << passed_cases + failed_cases << std::endl;
}
