#include "../include/init.hpp"
#include "../include/states/states.hpp"

int main(){

  init();
  //definindo a screen inicial
  ScreenState screen = MAIN_MENU;
  bool onetime = true;
  ALLEGRO_EVENT redraw_ev{};
  redraw_ev.type = ALLEGRO_EVENT_TIMER;

  while (screen != EXIT) {
    ALLEGRO_EVENT ev;
    bool redraw = false;
    al_wait_for_event(event_queue, &ev);

    do{
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
          screen = EXIT;
        } else if (ev.type == ALLEGRO_EVENT_TIMER){
          redraw = true;
          ALLEGRO_EVENT tmp;
          while (al_peek_next_event(event_queue, &tmp) &&
                   tmp.type == ALLEGRO_EVENT_TIMER)
                al_get_next_event(event_queue, &tmp);
        } else {
          if (screen == MAIN_MENU) {
            screen = mainMenu.loop(ev);
          } else if (screen == PLAY) {
            screen = play.loop(ev);
          } else if (screen == LOAD_NAME) {
            screen = loadName.loop(ev);
          } else if (screen == DIFFICULTY_MENU) {
            screen = difficultyMenu.loop(ev);
          } else if (screen == LEADERBOARD_MENU) {
            screen = leaderboardMenu.loop(ev);
          }
        }
  } while(al_get_next_event(event_queue, &ev));
  if (redraw) {
    if (screen == MAIN_MENU) {
            screen = mainMenu.loop(redraw_ev);
          } else if (screen == PLAY) {
            if (onetime){
                      play.init_objects();
                      onetime = false;
            }
            screen = play.loop(redraw_ev);
          } else if (screen == LOAD_NAME) {
            screen = loadName.loop(redraw_ev);
          } else if (screen == DIFFICULTY_MENU) {
            screen = difficultyMenu.loop(redraw_ev);
          } else if (screen == LEADERBOARD_MENU) {
            screen = leaderboardMenu.loop(redraw_ev);
          }
    al_flip_display();
    // static int    flips = 0;
    //   static double t0    = al_get_time();

    //   ++flips;
    //   if (al_get_time() - t0 >= 1.0) {
    //       std::cerr << "FPS: " << flips << '\n';
    //       flips = 0; t0 = al_get_time();
    //   }
    }
  }
  deinit();
  return 0;
}