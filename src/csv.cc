#include "csv.h"

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
    return {}; // TODO return error
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
    return {}; // TODO return error
  }
  const char c = buffer.front();
  buffer.pop_front();
  std::deque<char> result;
  result.push_front(c);
  return result;
}
