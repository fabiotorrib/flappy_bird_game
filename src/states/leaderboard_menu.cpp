#include <allegro5/allegro_primitives.h>  // usado nesse exemplo aqui
#include <map>
#include <string>
#include <vector>
#include "../../include/defines.hpp"
#include "../../include/init.hpp"
#include "../../include/states/main_menu.hpp"
#include "../../include/states/leaderboard_menu.hpp" 
#include "../../include/player.hpp"
#include "../../include/states/states.hpp" 

ScreenState LeaderboardMenu::loop() {
  // aqui sao implementados os eventos de teclado e mouse
  while (al_get_next_event(queue, &ev)) {
    //atualiza o ranking lendo o arquivo
    ranking = player.ReadLeaderboard("Leaderboard.txt");
    player.SortLeaderboard(ranking);
    player.SaveLeaderboard("Leaderboard.txt", ranking);


    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return ScreenState::EXIT;

    if (ev.type == ALLEGRO_EVENT_TIMER) motion.loop();

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
      return ScreenState::MAIN_MENU;
    }
    ///////
  }

    al_draw_bitmap(campLeaderboard, 40, 100, 0);

  int x_name_col = 270;  // Posição inicial para "Rank. Nome"
  int x_score_col = 888.14;  // Posição para a Pontuação (alinhada à direita)

  int y_inicial = 288;
  int vertical_distance = 45;

  for (size_t i = 0; i < ranking.size() && i < 7; ++i) {
    int y_pos = y_inicial + i * vertical_distance;

    std::string name_and_rank_text =
        std::to_string(i + 1) + ". " + ranking[i].GetName();

    al_draw_text(font, al_map_rgb(255, 255, 255), x_name_col, y_pos,
                 ALLEGRO_ALIGN_LEFT, name_and_rank_text.c_str());

    al_draw_textf(font, al_map_rgb(255, 255, 255), x_score_col, y_pos,
                 ALLEGRO_ALIGN_RIGHT,"%d", ranking[i].GetScore());

  }
  al_draw_textf(font, al_map_rgb(0, 0, 0), 640, 60,
                 ALLEGRO_ALIGN_CENTER,"Press Esc to back to main menu.");
  al_flip_display();
  

  return ScreenState::LEADERBOARD_MENU;
}
