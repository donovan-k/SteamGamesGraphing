#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "game.h"
#include "input.h"
#include "BFS.h"

bool testBFS(){
  BFSg graphene(5);
  graphene.edgeInstall(0, 1);
  graphene.edgeInstall(1, 0);
  graphene.edgeInstall(1, 2);
  graphene.edgeInstall(2, 1);
  graphene.edgeInstall(2, 3);
  graphene.edgeInstall(3, 2);
  graphene.edgeInstall(3, 0);
  graphene.edgeInstall(0, 3);
  graphene.edgeInstall(4, 3);
  graphene.edgeInstall(3, 4);
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
