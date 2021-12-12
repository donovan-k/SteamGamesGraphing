#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bfs.h"
#include "game.h"
#include "graph.h"
#include "input.h"
#include "similar.h"

using std::cout;

bool testSCCs() {
  // test if SCCs work
  Graph g(5);

  g.addEdge(1, 0);
  g.addEdge(0, 2);
  g.addEdge(2, 1);
  g.addEdge(0, 3);
  g.addEdge(3, 4);

  // std::cout << "Following are strongly connected components in "
  // "given graph \n";
  // // g.printSCCs();
  vector<vector<int>> SCCs = g.getSCCs();

  vector<int> test_vec;
  test_vec.push_back(0);
  test_vec.push_back(1);
  test_vec.push_back(2);

  if (test_vec.size() != SCCs[0].size()) {
    return false;
  }
  /* Return true if the vector contains the correct strongly connected
   * components */
  for (int i = 0; i < test_vec.size(); i++) {
    if (test_vec[i] != SCCs[0][i]) {
      return false;
    }
  }
  return true;
}

bool testStronglyConnected() {
  Graph g1(5);
  g1.addEdge(0, 1);
  g1.addEdge(1, 2);
  g1.addEdge(2, 3);
  g1.addEdge(3, 0);
  g1.addEdge(2, 4);
  g1.addEdge(4, 2);
  bool g1_check = g1.isStronglyConnected();

  Graph g2(4);
  g2.addEdge(0, 1);
  g2.addEdge(1, 2);
  g2.addEdge(2, 3);

  bool g2_check = g2.isStronglyConnected();

  if (g1_check == true && g2_check == false) {
    return true;
  } else {
    return false;
  }
}

bool testSimilarClass() {
  // test two games that are similar
  Game game1, game2;
  game1.popular_tags = "warhammer,dogs,cats,hunter,animal";
  game2.popular_tags = "warhammer,bunny,cats,animal,hunter";
  game1.game_details = "multiplayer,singleplayer,to the death,deathmatch,fire";
  game2.game_details = "to the death,fire,singleplayer,multiplayer,non-gmo";
  game1.genre = "adventure,action,gory,violence,shooter";
  game2.genre = "adventure,gory,shooter,puzzle,violence";
  game1.game_description =
      "in this game you will battle the hardest enemies ever";
  game2.game_description =
      "in this game you fight the most daring enemies ever";

  bool test_similar = Similar::areSimilar(game1, game2, 0.7);

  // test two games that are NOT similar
  game1.popular_tags = "dolly,dogs,courage,hunter,human";
  game2.popular_tags = "warhammer,bunny,cats,animal,hunter";
  game1.game_details = "multiplayer,singleplayer,to the death,deathmatch,fire";
  game2.game_details = "live,fire,singleplayer,cute,non-gmo";
  game1.genre = "puzzle,strategy,colorful,easy,relaxing";
  game2.genre = "adventure,gory,shooter,puzzle,violence";
  game1.game_description =
      "in this game you find your way through challenging puzzles";
  game2.game_description =
      "in this game you fight the most daring enemies ever";

  bool test_notsimilar = !Similar::areSimilar(game1, game2, 0.7);

  // if both test are true then they pass
  if (test_similar && test_notsimilar) {
    std::cout << "test similar function passed" << std::endl;
    return true;
  }

  // otherwise this test case fails
  std::cout << "test similar function FAILED" << std::endl;
  return false;
}

bool testBFS() {
  Graph graphene(5); // form 5 vertex graph
  graphene.addEdge(0, 1);
  graphene.addEdge(1, 0);
  graphene.addEdge(1, 2);
  graphene.addEdge(2, 1);
  graphene.addEdge(2, 3);
  graphene.addEdge(3, 2);
  graphene.addEdge(3, 0);
  graphene.addEdge(0, 3);
  graphene.addEdge(4, 3);
  graphene.addEdge(3, 4); // print traversal from each
  BFSg *graphen = new BFSg(&graphene);
  cout << "BFS starting with 1 \n";
  graphen->BFS(1);

  cout << "BFS starting with 2 \n";
  graphen->BFS(2);

  cout << "BFS starting with 3 \n";
  graphen->BFS(3);

  cout << "BFS starting with 4 \n";
  graphen->BFS(4);

  cout << "BFS starting with 0 \n";
  graphen->BFS(0);
  return true;
}

int main(int argc, char *argv[]) {
  std::vector<Game> games;

  std::ifstream fin("test.csv");
  if (!fin.is_open()) {
    std::cerr
        << argv[0]
        << ": cannot open 'test.csv' for reading: No such file or directory\n";
    abort();
  }
  std::string line;
  getline(fin, line);
  while (getline(fin, line)) {
    games.push_back(parse_game(line));
  }

  int passed_cases = 0; // test cases passed
  int failed_cases = 0; // test cases failed

  // test BFS
  bool test_case_BFS = testBFS();
  if (test_case_BFS)
    passed_cases++;
  else
    failed_cases++;

  // test the similar class
  bool test_case_similar = testSimilarClass();
  if (test_case_similar) {
    passed_cases++;
  } else {
    failed_cases++;
  }

  // test the strongly connected components
  bool test_case_SCC = testSCCs();
  if (test_case_SCC) {
    passed_cases++;
    std::cout << "test_case_SCC PASSED" << std::endl;
  } else {
    failed_cases++;
    std::cout << "test_case_SCC FAILED" << std::endl;
  }

  bool test_case_isSCC = testStronglyConnected();
  if (test_case_isSCC) {
    passed_cases++;
    std::cout << "test_case_isSCC PASSED" << std::endl;
  } else {
    failed_cases++;
    std::cout << "test_case_isSCC FAILED" << std::endl;
  }

  // print results
  std::cout << "tests passed: " << passed_cases << std::endl;
  std::cout << "tests failed: " << failed_cases << std::endl;
  std::cout << "total tests: " << passed_cases + failed_cases << std::endl;
}
