#ifndef INPUT_H
#define INPUT_H

#include "game.h"
#include <deque>

std::string lex_token_string(std::deque<char> &buffer);
std::vector<std::string> lex_csv(std::string &s);
Game parse_game(const std::string &s);

#endif // INPUT_H
