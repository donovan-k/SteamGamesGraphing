#include "input.h"

#include <deque>
#include <string>

#include "csv.h"
#include "game.h"

std::string lex_token_string(std::deque<char> &buffer) {
  std::deque<char> output;
  lex_token(buffer, output);
  return {output.begin(), output.end()};
}

std::vector<std::string> lex_csv(const std::string& s) {
  std::vector<std::string> result;
  std::deque<char> buffer{s.begin(), s.end()};
  std::string next;
  while ((next = lex_token_string(buffer)) != "") {
    result.push_back(next);
  }
  return result;
}

Game parse_game(const std::string &s) {
  Game game;
  std::deque<char> buffer(s.begin(), s.end());
  game.url = lex_token_string(buffer);
  game.types = lex_token_string(buffer);
  game.name = lex_token_string(buffer);
  game.desc_snippet = lex_token_string(buffer);
  game.recent_reviews = lex_token_string(buffer);
  game.all_reviews = lex_token_string(buffer);
  game.release_date = lex_token_string(buffer);
  game.developer = lex_token_string(buffer);
  game.publisher = lex_token_string(buffer);
  game.popular_tags = lex_csv(lex_token_string(buffer));
  game.game_details = lex_csv(lex_token_string(buffer));
  game.languages = lex_csv(lex_token_string(buffer));
  game.achievements = lex_token_string(buffer);
  game.genre = lex_csv(lex_token_string(buffer));
  game.game_description = lex_token_string(buffer);
  game.mature_content = lex_token_string(buffer);
  game.minimum_requirements = lex_token_string(buffer);
  game.recommended_requirements = lex_token_string(buffer);
  game.original_price = lex_token_string(buffer);
  game.discount_price = lex_token_string(buffer);
  return game;
}
