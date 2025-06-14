#include "../include/init.hpp"
#include "../include/states/states.hpp"

int main() {
  init();
  // definindo a screen inicial
  ScreenState screen = MAIN_MENU;

  while (screen != EXIT) {
    if (screen == MAIN_MENU) {
      screen = mainMenu.loop();
    } else if (screen == PLAY) {
      screen = play.loop();
    } else if (screen == LOAD_NAME) {
      screen = loadName.loop();
    } else if (screen == DIFFICULTY_MENU) {
      screen = difficultyMenu.loop();
    }
  }
  deinit();
  return 0;
}