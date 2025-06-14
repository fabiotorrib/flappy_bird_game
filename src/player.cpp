#include "../include/player.hpp"
#include <ostream>  // Necessário para o bônus do Doctest
#include "../include/init.hpp"

Player::Player(std::string name, int score) : name(name), score(score) {
}

std::string Player::GetName() const {
  return name;
}

int Player::GetScore() const {
  return score;
}

void Player::SetScore(int points) {
  score = points;
}

bool Player::CheckingName(std::vector<Player>& ranking, std::string& Name) {
  for (const Player& p : ranking) {
    if (p.GetName() == Name) {
      return true;
    }
  }
  return false;
}

bool Player::operator<(const Player& other_p) const {
  return this->score > other_p.score;
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
  os << "Player(Name: \"" << p.GetName() << "\", Score: " << p.GetScore()
     << ")";
  return os;
}

std::vector<Player> Player::ReadLeaderboard(std::string file_name) {
  std::vector<Player> ranking;
  std::ifstream file(file_name);
  if (file.is_open()) {
    std::string line;
    while (getline(file, line)) {
      std::istringstream name_and_score(line);
      std::string read_name;
      int points;
      if (name_and_score >> read_name >> points) {
        ranking.push_back(Player(read_name, points));
      }
    }
    file.close();
  }
  return ranking;
}

void Player::SaveLeaderboard(std::string fileName,
                             std::vector<Player>& ranking) {
  std::ofstream file(fileName, std::ios::out);
  if (!file.is_open()) {
    return;
  }
  for (auto& p : ranking) {
    file << p.GetName() << " " << p.GetScore() << std::endl;
  }
  file.close();
}
void Player::SaveLeaderboard(std::string fileName, std::vector<Player>& ranking,
                             const Player& new_player) {
  bool found = false;
  for (auto& p : ranking) {
    if (p.GetName() == new_player.GetName()) {
      if (p.GetScore() < new_player.GetScore()) {
        p.SetScore(new_player.GetScore());
      }
      found = true;
      break;
    }
  }

  if (!found) {
    ranking.push_back(new_player);  // adicionando somente novo jogador
  }

  std::ofstream file(fileName, std::ios::out);
  if (!file.is_open()) {
    return;
  }

  for (const Player& p : ranking) {
    file << p.GetName() << " " << p.GetScore() << std::endl;
  }

  file.close();
}

void Player::SortLeaderboard(std::vector<Player>& ranking) {
  sort(ranking.begin(), ranking.end());
}
