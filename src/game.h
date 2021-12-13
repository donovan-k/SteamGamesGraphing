#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

struct Game {
  std::string url;
  std::string types;
  std::string name;
  std::string desc_snippet;
  std::string recent_reviews;
  std::string all_reviews;
  std::string release_date;
  std::string developer;
  std::string publisher;
  std::vector<std::string> popular_tags;
  std::vector<std::string> game_details;
  std::vector<std::string> languages;
  std::string achievements;
  std::vector<std::string> genre;
  std::string game_description;
  std::string mature_content;
  std::string minimum_requirements;
  std::string recommended_requirements;
  std::string original_price;
  std::string discount_price;
};
#endif // GAME_H
