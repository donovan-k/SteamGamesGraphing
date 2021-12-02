#ifndef CSV_H
#define CSV_H

#include <deque>

std::deque<char> lex_token(std::deque<char>& buffer);
std::deque<char> lex_string(std::deque<char>& buffer);
std::deque<char> lex_escape(std::deque<char>& buffer);

#endif // CSV_H
