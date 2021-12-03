#include "input.h"

#include <deque>
#include <string>

#include "csv.h"
#include "game.h"

std::string lex_token_string(std::deque<char>& buffer) {
  std::deque<char> output;
  lex_token(buffer, output);
  return {output.begin(), output.end()};
}

Game parse_game(const std::string& s) {
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
  game.popular_tags = lex_token_string(buffer);
  game.game_details = lex_token_string(buffer);
  game.languages = lex_token_string(buffer);
  game.achievements = lex_token_string(buffer);
  game.genre = lex_token_string(buffer);
  game.game_description = lex_token_string(buffer);
  game.mature_content = lex_token_string(buffer);
  game.minimum_requirements = lex_token_string(buffer);
  game.recommended_requirements = lex_token_string(buffer);
  game.original_price = lex_token_string(buffer);
  game.discount_price = lex_token_string(buffer);
  return game;
}
