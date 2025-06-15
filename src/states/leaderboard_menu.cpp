#include "defines.hpp"
#include "init.hpp"
#include "player.hpp"
#include "states/main_menu.hpp"
#include "states/states.hpp"  //necessario para modificar o objeto play (ou qualquer outro)

ScreenState LeaderboardMenu::loop() {
  // aqui sao implementados os eventos de teclado e mouse
  while (al_get_next_event(queue, &ev)) {
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return ScreenState::EXIT;

    if (ev.type == ALLEGRO_EVENT_TIMER) motion.loop();

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
         ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
      al_play_sample(selectSound, 0., 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
      if (menuButtons[buttonPositionSelected].name == "Exit") {
      } else if (menuButtons[buttonPositionSelected].name == "NextPage") {
      }
    }

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
      return ScreenState::MAIN_MENU;
    }
    ///////

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_DOWN:
        case ALLEGRO_KEY_LEFT:
          menuButtons[buttonPositionSelected].buttonSelectState = 0;

          if (buttonPositionSelected == 1)
            buttonPositionSelected = 0;
          else
            buttonPositionSelected++;

          menuButtons[buttonPositionSelected].buttonSelectState = 1;
          break;

        case ALLEGRO_KEY_UP:
        case ALLEGRO_KEY_RIGHT:
          if (ev.keyboard.keycode == ALLEGRO_KEY_UP ||
              ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
            menuButtons[buttonPositionSelected].buttonSelectState = 0;

            if (buttonPositionSelected == 0)
              buttonPositionSelected = 1;
            else
              buttonPositionSelected--;

            menuButtons[buttonPositionSelected].buttonSelectState = 1;
          }
          break;
      }
    }
  }
  if (campLeaderboard) {
    al_draw_bitmap(campLeaderboard, 100, 100, 0);
  } else {
    al_clear_to_color(al_map_rgb(0, 0, 0));
  }

  int x_name_col = SCREEN_W / 4;  // Posição inicial para "Rank. Nome"
  int x_score_col =
      SCREEN_W / 1.35;  // Posição para a Pontuação (alinhada à direita)

  int y_inicial = SCREEN_H / 2.5;
  int vertical_distance = 45;

  for (size_t i = 0; i < ranking.size() && i < 10; ++i) {
    int y_pos = y_inicial + i * vertical_distance;

    std::string name_and_rank_text =
        std::to_string(i + 1) + ". " + ranking[i].GetName();
    std::string score_text = std::to_string(ranking[i].GetScore());

    al_draw_text(font, al_map_rgb(255, 255, 255), x_name_col, y_pos,
                 ALLEGRO_ALIGN_LEFT, name_and_rank_text.c_str());

    al_draw_text(font, al_map_rgb(255, 255, 255), x_score_col, y_pos,
                 ALLEGRO_ALIGN_RIGHT, score_text.c_str());
  }

  al_draw_text(font, al_map_rgb(200, 200, 200), SCREEN_W / 2, SCREEN_H - 80,
               ALLEGRO_ALIGN_CENTER, "Pressione ESC ou ENTER para voltar");

  al_flip_display();

  return ScreenState::LEADERBOARD_MENU;
}
