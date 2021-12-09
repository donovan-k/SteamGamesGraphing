#ifndef SIMILAR_H
#define SIMILAR_H

#include "game.h"
#include <iostream>
#include <string>
#include <vector>

using std::getline;
using std::string;
using std::stringstream;
using std::vector;

class Similar {
public:
  /**
   * function for comparing two games to see if they are similar
   * tolerance should be between 0 and 1 and the higher it is the less likely
   * two games will be similar. Use tolerance between 0.5 and 0.8. 
   * Use 0.5 tolerance for less strict (more similar games for each game). 
   * Use 0.8 tolerance for more strict (less similar games for each game).
   */
  static bool areSimilar(const Game &game1, const Game &game2,
                         double tolerance);

  static vector<string> getToken(string str, char delimiter);

  static double compareTokens(const vector<string> &tag1,
                              const vector<string> &tag2);
};

#endif // SIMILAR_H
