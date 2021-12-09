#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <deque>
#include "game.h"

std::string lex_token_string(std::deque<char>& buffer);
Game parse_game(const std::string& s);

#endif // INPUT_H
