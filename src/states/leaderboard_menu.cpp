#include <allegro5/allegro_primitives.h>  // usado nesse exemplo aqui
#include <map>
#include <string>
#include <vector>
#include "../../include/defines.hpp"
#include "../../include/init.hpp"
#include "../../include/states/main_menu.hpp"
#include "../../include/states/states.hpp"  //necessario para modificar o objeto play (ou qualquer outro)
#include "player.hpp"

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
  player.ShowLeaderboard(ranking, font);
  al_flip_display();
  return ScreenState::LEADERBOARD_MENU;
}
