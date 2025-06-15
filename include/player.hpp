#pragma once

#include "init.hpp"

class Player {
 private:
  std::string name;
  int score;

 public:
  Player(std::string name, int score = 0);  // construtor

  // getters e setters
  std::string GetName() const;
  int GetScore() const;
  void SetScore(int points);

  static bool CheckingName(std::vector<Player>& ranking,std::string& Name);
  static std::vector<Player> ReadLeaderboard(std::string file_name);
  static void SortLeaderboard(std::vector<Player>& ranking);
  static void SaveLeaderboard(std::string fileName,
                              std::vector<Player>& ranking, const Player& new_player);
  static void ShowLeaderboard(std::vector<Player>& ranking, ALLEGRO_FONT* font);
  bool operator<(const Player& other_p) const;  // sobrecarga do operador <
};
