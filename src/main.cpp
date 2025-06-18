#include <memory>
#include "../include/init.hpp"
#include "../include/states/main_menu.hpp"
#include "../include/states/load_game.hpp"
#include "../include/states/leaderboard_menu.hpp"
#include "../include/states/play.hpp"
#include "../include/states/difficulty_menu.hpp"
#include "../include/motion.hpp"


int main(){

  init();
  //definindo a screen inicial
  ScreenState screen = MAIN_MENU;
  bool onetime = true;

  //inicializando estados
  std::unique_ptr<MainMenu> mainMenu = std::make_unique<MainMenu>();
  std::unique_ptr<Play> play = std::make_unique<Play>();
  std::unique_ptr<LoadName> loadName = std::make_unique<LoadName>();
  std::unique_ptr<DifficultyMenu> difficultyMenu = std::make_unique<DifficultyMenu>();
  std::unique_ptr<LeaderboardMenu> leaderboardMenu = std::make_unique<LeaderboardMenu>();
  std::unique_ptr<Motion> motion = std::make_unique<Motion>();



  while (screen != EXIT) {
    ALLEGRO_EVENT ev;
    bool redraw = false;
    al_wait_for_event(event_queue, &ev);
    //loop para processar eventos
    do{
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
          screen = EXIT;
        } else if (ev.type == ALLEGRO_EVENT_TIMER){
          redraw = true;
          ALLEGRO_EVENT tmp;
          //evita super alimentacao
          while (al_peek_next_event(event_queue, &tmp) &&
                tmp.type == ALLEGRO_EVENT_TIMER)
                al_get_next_event(event_queue, &tmp);

        } else {
          //eventos que nao sao TIMER nem CLOSE
          if (screen == MAIN_MENU) {
            screen = mainMenu->loop(ev);
          } else if (screen == PLAY) {
            screen = play->loop(ev);
          } else if (screen == LOAD_NAME) {
            screen = loadName->loop(ev);
          } else if (screen == DIFFICULTY_MENU) {
            screen = difficultyMenu->loop(ev);
          } else if (screen == LEADERBOARD_MENU) {
            screen = leaderboardMenu->loop(ev);
          }
        }
  } while(al_get_next_event(event_queue, &ev));
  // desenha a flipa a tela em 60 vezes por segundo
  if (redraw) {
    if (screen == MAIN_MENU) {
            screen = mainMenu->draw(*motion);
    } else if (screen == PLAY) {
            if (onetime){
                      play->init_objects();
                      onetime = false;
            }
            screen = play->draw(*motion);
    } else if (screen == LOAD_NAME) {
            screen = loadName->draw(*motion);
    } else if (screen == DIFFICULTY_MENU) {
            screen = difficultyMenu->draw(*motion);
          } else if (screen == LEADERBOARD_MENU) {
            screen = leaderboardMenu->draw(*motion);
          }
    al_flip_display();
    }
  }
  deinit();
  return 0;
}