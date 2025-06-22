/**
 * @file player.cpp
 * @brief Implementação da classe Player e utilidades de ranking.
 */

#include "../include/player.hpp"
#include <ostream>  // Necessário para o bônus do Doctest
#include "../include/init.hpp"

/**
 * @brief Constrói um jogador com nome e pontuação inicial.
 * @param name Nome do jogador.
 * @param score Pontuação inicial (0 por padrão).
 */
Player::Player(std::string name, int score) : name(name), score(score) {
}

/** @brief Retorna o nome do jogador. */
std::string Player::GetName() const {
  return name;
}

/** @brief Retorna a pontuação atual. */
int Player::GetScore() const {
  return score;
}

/**
 * @brief Atualiza (sobrescreve) a pontuação do jogador.
 * @param points Novo valor de pontuação.
 */
void Player::SetScore(int points) {
  score = points;
}

/**
 * @brief Verifica se um nome já existe no ranking.
 * @param ranking Vetor de jogadores.
 * @param Name Nome a procurar.
 * @return true se encontrado.
 */
bool Player::CheckingName(std::vector<Player>& ranking, std::string& Name) {
  for (const Player& p : ranking) {
    if (p.GetName() == Name) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Define critério de ordenação decrescente por pontuação.
 */
bool Player::operator<(const Player& other_p) const {
  return this->score > other_p.score;
}

/**
 * @brief Sobrecarga de operador de streaming para debug.
 */
std::ostream& operator<<(std::ostream& os, const Player& p) {
  os << "Player(Name: \"" << p.GetName() << "\", Score: " << p.GetScore()
     << ")";
  return os;
}

/**
 * @brief Lê arquivo de ranking e retorna vetor de jogadores.
 * @param file_name Caminho do arquivo.
 * @return Vetor de jogadores lido.
 */
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

/**
 * @brief Salva lista de jogadores no arquivo, sobrescrevendo conteúdo.
 */
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

/**
 * @brief Salva ranking adicionando ou atualizando um jogador.
 * @param new_player Jogador a inserir/atualizar.
 */
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

/** @brief Ordena vetor de jogadores por pontuação decrescente. */
void Player::SortLeaderboard(std::vector<Player>& ranking) {
  sort(ranking.begin(), ranking.end());
}
