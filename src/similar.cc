#include "similar.h"

/**
 * function for comparing two games to see if they are similar
 * tolerance should be between 0 and 1 and the higher it is the less likely two
 * games will be similar
 */
bool Similar::areSimilar(const Game &game1, const Game &game2,
                         float tolerance) {

  float similar_score = 0.0;
  similar_score += compareTokens(game1.popular_tags, game2.popular_tags);
  similar_score += compareTokens(game1.game_details, game2.game_details);
  similar_score += (game1.genre == game2.genre);

  return similar_score / 3.0f > tolerance;
}

float Similar::compareTokens(const std::vector<std::string> &tag1,
                              const std::vector<std::string> &tag2) {
  float similar_score = 0.0;
  for (auto str1 : tag1) {
    for (auto str2 : tag2) {
      if (str1 == str2) {
        similar_score += 1.0f;
      }
    }
  }

  return 2.0f * similar_score / float(tag1.size() + tag2.size());
}
