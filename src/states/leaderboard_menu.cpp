#include "../include/states/leaderboard_menu.hpp"
#include "../include/init.hpp"
#include "../include/states/main_menu.hpp"

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
  al_draw_bitmap(campLeaderboard, 40, 100, 0);

  int x_name_col = 270;        // Posição inicial para "Rank. Nome"
  float x_score_col = 888.14;  // Posição para a Pontuação (alinhada à direita)

  int y_inicial = 288;
  int vertical_distance = 45;

  for (size_t i = 0; i < ranking.size() && i < 7; ++i) {
    int y_pos = y_inicial + i * vertical_distance;

    std::string name_and_rank_text =
        std::to_string(i + 1) + ". " + ranking[i].GetName();

    al_draw_text(font, al_map_rgb(255, 255, 255), x_name_col, y_pos,
                 ALLEGRO_ALIGN_LEFT, name_and_rank_text.c_str());

    al_draw_textf(font, al_map_rgb(255, 255, 255), x_score_col, y_pos,
                  ALLEGRO_ALIGN_RIGHT, "%d", ranking[i].GetScore());
  }
  al_draw_textf(font, al_map_rgb(0, 0, 0), 640, 60, ALLEGRO_ALIGN_CENTER,
                "Press Esc to back to main menu.");
}
