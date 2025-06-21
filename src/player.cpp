#include "../include/player.hpp"
#include <ostream>  // Necessário para o bônus do Doctest
#include "../include/init.hpp"

//construtor
Player::Player(std::string name, int score) : name(name), score(score) {
}

// getters para obter nome e pontuação
std::string Player::GetName() const {
  return name;
}
int Player::GetScore() const {
  return score;
}

//setter para atualizar pontuação
void Player::SetScore(int points) {
  score = points;
}

//checar se o nome já foi inserido anteriormente
bool Player::CheckingName(std::vector<Player>& ranking, std::string& Name) {
  for (const Player& p : ranking) {
    if (p.GetName() == Name) {
      return true;
    }
  }
  return false;
}

//sobrecarga do operador <, para ordenação do ranking com sort
bool Player::operator<(const Player& other_p) const {
  return this->score > other_p.score;
}

//permite imprimir jogador/pontuação usando std::cout<<
std::ostream& operator<<(std::ostream& os, const Player& p) {
  os << "Player(Name: \"" << p.GetName() << "\", Score: " << p.GetScore()
     << ")";
  return os;
}

//ler arquivo com nomes/scores para criar um vector com o ranking ainda desordenado
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

//salvar no arquivo os nomes e scores dos jogadores
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
//salvar no arquivo os nomes e scores dos jogadores, atualizando a pontuação para a mais alta em caso de repetição de nome
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

//ordenar ranking
void Player::SortLeaderboard(std::vector<Player>& ranking) {
  sort(ranking.begin(), ranking.end());
}
