#include "player.hpp"

// Construtor (pontuação é iniciada como zero)
Player::Player(std::string name) : name(name), score(0) {
}

std::string Player::GetName() {
  return name;
}

int Player::GetScore() {
  return score;
}

// setter para atualizar pontuação
void Player::SetScore(int points) {
  score = points;
}

std::vector<Player> Player::ReadLeaderboard(std::string file_name) {
  std::vector<Player> ranking;    // criando vector para o ranking
  std::ifstream file(file_name);  // abrir arquivo que contém o ranking

  if (file.is_open()) {
    std::string line;
    while (getline(file, line)) {  // enquanto houver linha a ser lida
      std::istringstream name_and_score(
          line);  // função que permite separa as partes da linha
      std::string read_name;
      int points;
      if (name_and_score >> read_name >> points) {
        Player p(read_name);
        p.SetScore(points);
        ranking.push_back(p);
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

bool Player::operator<(const Player& other_p) {
  return this->score > other_p.score;
}

// Função para ordenar a leaderboard
void Player::SortLeaderboard(std::vector<Player>& ranking) {
  sort(ranking.begin(), ranking.end());
}

void Player::ShowLeaderboard(std::vector<Player>& ranking, ALLEGRO_FONT* font) {
  al_clear_to_color(al_map_rgb(0, 0, 0));  // pinta a tela com a cor preta

  int x = 100;  // coordenadas onde os nomes começam a ser escritos
  int y = 100;
  int vertical_distance =
      40;  // distância vertical entre cada linha com nome e score

  al_draw_text(font, al_map_rgb(255, 255, 0), x, y - 50, 0,
               "LEADERBOARD:");  // imprime o título LEADERBOARD com cor amarela

  for (size_t i = 0; i < ranking.size() && i < 10;
       ++i) {  // exibe no máximo 10 players
    std::string text = std::to_string(i + 1) + ". " + ranking[i].GetName() +
                       " - " + std::to_string(ranking[i].GetScore());
    al_draw_text(font, al_map_rgb(255, 255, 255), x, y + i * vertical_distance,
                 0, text.c_str());  // c_string converte string em const char*,
                                    // necessário para Allegro
  }

  al_flip_display();

  al_rest(5.0);  // espera 5 segundos
}
