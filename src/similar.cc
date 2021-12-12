#include "similar.h"

#include <sstream>

/**
 * function for comparing two games to see if they are similar
 * tolerance should be between 0 and 1 and the higher it is the less likely two
 * games will be similar
 */
bool Similar::areSimilar(const Game &game1, const Game &game2,
                         double tolerance) {
  // getting the categories used for comparing
  std::vector<std::string> compare_string1 = {game1.popular_tags,
                                              game1.game_details, game1.genre,
                                              game1.game_description};
  std::vector<std::string> compare_string2 = {game2.popular_tags,
                                              game2.game_details, game2.genre,
                                              game2.game_description};
  size_t n_tags = compare_string1.size();

  // setting the delimiter for each category
  std::vector<char> delimiters = {',', ',', ',', ' '};

  // compare the strings of each category
  double similar_score = 0.0;
  for (size_t i = 0; i < n_tags; i++) {
    std::vector<std::string> token1 =
        getToken(compare_string1[i], delimiters[i]);
    std::vector<std::string> token2 =
        getToken(compare_string2[i], delimiters[i]);
    similar_score += compareTokens(token1, token2);
  }

  return (similar_score / n_tags) > tolerance;
}

std::vector<std::string> Similar::getToken(const std::string &str,
                                           char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream stream(str);
  std::string current;

  while (getline(stream, current, delimiter)) {
    tokens.push_back(current);
  }

  return tokens;
}

double Similar::compareTokens(const std::vector<std::string> &tag1,
                              const std::vector<std::string> &tag2) {
  int similar_score = 0;
  for (auto str1 : tag1) {
    for (auto str2 : tag2) {
      if (str1.compare(str2) == 0) {
        similar_score++;
      }
    }
  }

  return (double)similar_score / ((tag1.size() + tag2.size()) / 2.0);
}
