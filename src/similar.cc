#include "similar.h"

/**
 * function for comparing two games to see if they are similar
 * tolerance should be between 0 and 1 and the higher it is the less
 * likely two games will be similar
 */
bool gamesSimilar(const Game &game1, const Game &game2,
                         float threshold) {

  int score = 0;
  int total = 0;

  for (const std::string& str1 : game1.popular_tags) {
    for (const std::string& str2 : game2.popular_tags) {
      score += (str1 == str2);
    }
  }
  total += game1.popular_tags.size() + game2.popular_tags.size();

  for (const std::string& str1 : game1.game_details) {
    for (const std::string& str2 : game2.game_details) {
      score += (str1 == str2);
    }
  }
  total += game1.game_details.size() + game2.game_details.size();

  for (const std::string& str1 : game1.genre) {
    for (const std::string& str2 : game2.genre) {
      score += (str1 == str2);
    }
  }
  total += game1.genre.size() + game2.genre.size();

  return (float(score) / float(total)) > threshold;
}

