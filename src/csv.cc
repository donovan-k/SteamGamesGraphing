#include "csv.h"

void lex_token(std::deque<char> &buffer, std::deque<char> &output) {
  if (buffer.empty()) {
    return;
  }

  const char c = buffer.front();
  buffer.pop_front();

  if (c == ',') {
    return;
  }

  if (c == '"') {
    lex_string(buffer, output);
    lex_token(buffer, output);
    return;
  }

  output.push_back(c);
  lex_token(buffer, output);
}

void lex_string(std::deque<char> &buffer, std::deque<char> &output) {
  if (buffer.empty()) {
    return;
  }

  const char c = buffer.front();
  buffer.pop_front();

  if (c == '"') {
    return;
  }

  if (c == '\\') {
    lex_escape(buffer, output);
    lex_string(buffer, output);
    return;
  }

  output.push_back(c);
  lex_string(buffer, output);
}

void lex_escape(std::deque<char> &buffer, std::deque<char> &output) {
  if (buffer.empty()) {
    return;
  }

  const char c = buffer.front();
  buffer.pop_front();

  output.push_front(c);
}
