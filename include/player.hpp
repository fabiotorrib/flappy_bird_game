#pragma once

#include "libs.hpp"

class Player {
 private:
  std::string name;
  int score;

 public:
  Player(std::string name);  // construtor

  // getters e setters
  std::string GetName();
  int GetScore();
  void SetScore(int points);

  static std::vector<Player> ReadLeaderboard(std::string file_name);
  static void SortLeaderboard(std::vector<Player>& ranking);
  static void SaveLeaderboard(std::string fileName,
                              std::vector<Player>& ranking);
  static void ShowLeaderboard(std::vector<Player>& ranking, ALLEGRO_FONT* font);
  bool operator<(const Player& other_p);  // sobrecarga do operador <
};
