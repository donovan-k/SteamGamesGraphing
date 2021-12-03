#ifndef CSV_H
#define CSV_H

#include <deque>

void lex_token(std::deque<char>& buffer, std::deque<char>& output);
void lex_string(std::deque<char>& buffer, std::deque<char>& output);
void lex_escape(std::deque<char>& buffer, std::deque<char>& output);

#endif // CSV_H