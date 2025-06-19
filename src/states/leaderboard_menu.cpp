#include "../include/states/leaderboard_menu.hpp"
#include "../include/init.hpp"
#include "../include/states/main_menu.hpp"
#include <memory>

LeaderboardMenu::LeaderboardMenu(){
  font = std::make_unique<TextFont>("assets/TextFont.ttf", 46);
  campLeaderboard = std::make_unique<Image>("assets/campLeaderboard.png", 40, 100);
}

State* LeaderboardMenu::handle_input(const ALLEGRO_EVENT& ev) {
  // aqui sao implementados os eventos de teclado e mouse
  // atualiza o ranking lendo o arquivo
  if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
    return new MainMenu();
  }

  return this;
}

void LeaderboardMenu::enter() {
  // Isso agora só acontece uma vez quando a tela abre.
  ranking = Player::ReadLeaderboard("Leaderboard.txt");
  Player::SortLeaderboard(ranking);
}

State* LeaderboardMenu::update(Motion& motion) {
  motion.update();

  return this;
}

void LeaderboardMenu::draw(Motion& motion) {
  motion.draw();
  campLeaderboard->Draw();

  int x_name_col = 270;        // Posição inicial para "Rank. Nome"
  float x_score_col = 888.14;  // Posição para a Pontuação (alinhada à direita)

  int y_inicial = 288;
  int vertical_distance = 45;

  for (size_t i = 0; i < ranking.size() && i < 7; ++i) {
    int y_pos = y_inicial + i * vertical_distance;

    std::string name_and_rank_text = std::to_string(i + 1) + ". " + ranking[i].GetName();

    font->setColor(255, 255, 255);    
    font->writeText (name_and_rank_text.c_str(), ALLEGRO_ALIGN_LEFT, x_name_col, y_pos);
    std::string score_como_texto = std::to_string(ranking[i].GetScore());
    font->setColor(255, 255, 255);
    font->writeText(score_como_texto.c_str(), ALLEGRO_ALIGN_RIGHT, x_score_col, y_pos);
  }
    font->setColor(0, 0, 0);
    font->writeText("Press Esc to back to main menu." , ALLEGRO_ALIGN_CENTER, 640, 60);
}
