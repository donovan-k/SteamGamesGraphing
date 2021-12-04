#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "game.h"
#include "input.h"
#include "scc.h"
#include "similar.h"

bool testSCCs() {
  // test if SCCs work
  Graph g(5);
  
  g.addEdge(1, 0);
  g.addEdge(0, 2);
  g.addEdge(2, 1);
  g.addEdge(0, 3);
  g.addEdge(3, 4);
  
  std::cout << "Following are strongly connected components in "
  "given graph \n";
  g.printSCCs();
  // return true if print SCC compiles
  return true;
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


bool testBFS(){
  BFSg graphene(5);//form 5 vertex graph
  graphene.edgeInstall(0, 1);
  graphene.edgeInstall(1, 0);
  graphene.edgeInstall(1, 2);
  graphene.edgeInstall(2, 1);
  graphene.edgeInstall(2, 3);
  graphene.edgeInstall(3, 2);
  graphene.edgeInstall(3, 0);
  graphene.edgeInstall(0, 3);
  graphene.edgeInstall(4, 3);
  graphene.edgeInstall(3, 4);//print traversal from each
  
  cout<<"BFS starting with 1 \n";
  graphene.BFS(1);
  
  cout<<"BFS starting with 2 \n";
  graphene.BFS(2);
  
  cout<<"BFS starting with 3 \n";
  graphene.BFS(3);
  
  cout<<"BFS starting with 4 \n";
  graphene.BFS(4);
  
  cout<<"BFS starting with 0 \n";
  graphene.BFS(0);
  
  return true;
}

int main(int argc, char* argv[]) {
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
  
  //test BFS
  bool test_case_BFS = testBFS();
  if(test_case_BFS)
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
  } else {
    failed_cases++;
  }
  
  // print results
  std::cout << "tests passed: " << passed_cases << std::endl;
  std::cout << "tests failed: " << failed_cases << std::endl;
  std::cout << "total tests: " << passed_cases + failed_cases << std::endl;
}
