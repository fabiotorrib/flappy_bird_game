#include "../../include/states/difficulty_menu.hpp"


ScreenState DifficultyMenu::loop(const ALLEGRO_EVENT& ev) {
  // aqui sao implementados os eventos de teclado e mouse
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return ScreenState::EXIT;

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
         ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
      al_play_sample(selectSound, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
      if (menuButtons[buttonPositionSelected].name == "Easy") {
        std::cout << "Dificuldade Easy selecionada!" << std::endl;
        difficultySelected = "Easy";
        buttonPositionSelected = 3;
        menuButtons[buttonPositionSelected].buttonSelectState = 1;
      } else if (menuButtons[buttonPositionSelected].name == "Normal") {
        std::cout << "Dificuldade Normal selecionada!" << std::endl;
        difficultySelected = "Normal";
        buttonPositionSelected = 3;
        menuButtons[buttonPositionSelected].buttonSelectState = 1;
      } else if (menuButtons[buttonPositionSelected].name == "Hard") {
        std::cout << "Dificuldade Hard selecionada!" << std::endl;
        difficultySelected = "Hard";
        buttonPositionSelected = 3;
        menuButtons[buttonPositionSelected].buttonSelectState = 1;
      } else if (menuButtons[buttonPositionSelected].name == "Save") {
        std::cout << "Dificuldade " << difficultySelected << " salva!"
                  << std::endl;

        menuButtons[buttonPositionSelected].buttonSelectState = 0;

        if (difficultySelected == "Easy")
          buttonPositionSelected = 0;
        else if (difficultySelected == "Normal")
          buttonPositionSelected = 1;
        else if (difficultySelected == "Normal")
          buttonPositionSelected = 2;

        menuButtons[buttonPositionSelected].buttonSelectState = 1;

        return ScreenState::MAIN_MENU;
      }
    }

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
      difficultySelected = "noOne";
      return ScreenState::MAIN_MENU;
    }
    ///////

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_DOWN:

          if (buttonPositionSelected == 2) {
            buttonPositionSelected = 3;
            menuButtons[buttonPositionSelected].buttonSelectState = 1;
          } else if (buttonPositionSelected == 3) {
            menuButtons[buttonPositionSelected].buttonSelectState = 0;
            buttonPositionSelected = 0;
            menuButtons[buttonPositionSelected].buttonSelectState = 1;
          } else {
            menuButtons[buttonPositionSelected].buttonSelectState = 0;
            buttonPositionSelected++;
            menuButtons[buttonPositionSelected].buttonSelectState = 1;
          }

          break;

        case ALLEGRO_KEY_UP:

          if (buttonPositionSelected == 0) {
            buttonPositionSelected = 3;
            menuButtons[buttonPositionSelected].buttonSelectState = 1;
          } else if (buttonPositionSelected == 3) {
            menuButtons[0].buttonSelectState = 0;
            menuButtons[buttonPositionSelected].buttonSelectState = 0;
            buttonPositionSelected = 2;
            menuButtons[buttonPositionSelected].buttonSelectState = 1;
          } else {
            menuButtons[buttonPositionSelected].buttonSelectState = 0;
            buttonPositionSelected--;
            menuButtons[buttonPositionSelected].buttonSelectState = 1;
          }

          break;
      }
    }
  return ScreenState::DIFFICULTY_MENU;
  }
ScreenState DifficultyMenu::draw(const ALLEGRO_EVENT& ev, Motion& motion) {
      motion.loop();
      if (menuButtons[0].buttonSelectState)
        al_draw_bitmap(buttonDifficultyEasy, 40, 80, 0);
      else if (menuButtons[1].buttonSelectState)
        al_draw_bitmap(buttonDifficultyNormal, 40, 80, 0);
      else if (menuButtons[2].buttonSelectState)
        al_draw_bitmap(buttonDifficultyHard, 40, 80, 0);

      if (menuButtons[3].buttonSelectState) {
        al_draw_bitmap(buttonSaveSelect, 496.5, 600, 0);
      } else {
        al_draw_bitmap(buttonSaveDeselect, 496.5, 600, 0);
      }

      if (difficultySelected == "Easy")
        al_draw_text(font, al_map_rgb(218, 15, 15), 640, 495,
                    ALLEGRO_ALIGN_CENTER, "Easy Difficulty selected!");
      else if (difficultySelected == "Normal")
        al_draw_text(font, al_map_rgb(218, 15, 15), 640, 495,
                    ALLEGRO_ALIGN_CENTER, "Normal Difficulty selected!");
      else if (difficultySelected == "Hard")
        al_draw_text(font, al_map_rgb(218, 15, 15), 640, 495,
                    ALLEGRO_ALIGN_CENTER, "Hard Difficulty selected!");
  return ScreenState::DIFFICULTY_MENU;
}
