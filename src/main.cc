#include <fstream>
#include <iostream>
#include <deque>
#include <string>
#include <vector>

#include "game.h"

std::string lex_token_string(std::deque<char>& buffer);
std::deque<char> lex_token(std::deque<char>& buffer);
std::deque<char> lex_string(std::deque<char>& buffer);
std::deque<char> lex_escape(std::deque<char>& buffer);

std::string lex_token_string(std::deque<char>& buffer) {
  std::deque<char> result = lex_token(buffer);
  return {result.begin(), result.end()};
}

std::deque<char> lex_token(std::deque<char>& buffer) {
  if (buffer.empty()) {
    return {};
  }
  const char c = buffer.front();
  buffer.pop_front();
  if (c == ',') {
    return {};
  } else if (c == '"') {
    return lex_string(buffer);
  } else {
    std::deque<char> result = lex_token(buffer);
    result.push_front(c);
    return result;
  }
}

std::deque<char> lex_string(std::deque<char>& buffer) {
  if (buffer.empty()) {
    return {};
  }
  const char c = buffer.front();
  buffer.pop_front();
  if (c == '"') {
    return {};
  } else if (c == '\\') {
    return lex_escape(buffer);
  } else {
    std::deque<char> result = lex_string(buffer);
    result.push_front(c);
    return result;
  }
}

std::deque<char> lex_escape(std::deque<char>& buffer) {
  if (buffer.empty()) {
    return {};
  }
  const char c = buffer.front();
  buffer.pop_front();
  std::deque<char> result;
  result.push_front(c);
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<Game> games;

  std::string line;
  Game game;
  for (std::size_t i = 1; i < argc; ++i) {
    std::ifstream fin(argv[i]);
    if (!fin.is_open()) {
      std::cerr << argv[0] << ": cannot open '" << argv[i] <<
        "' for reading: No such file or directory\n";
      abort();
    }
    getline(fin, line); // skip header line
    while (getline(fin, line)) {
      std::deque<char> buffer(line.begin(), line.end());
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
      games.push_back(game);
    }
  }

  std::cout << "We have " << games.size() << " games in total!\n";
  for (const Game& game : games) {
    std::cout << game.name << ": " << game.desc_snippet << "\n";
  }
}
