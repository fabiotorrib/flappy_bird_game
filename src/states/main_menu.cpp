#include "../../include/states/main_menu.hpp"


std::string inputNameScreen = "";

ScreenState MainMenu::loop(const ALLEGRO_EVENT& ev) {
  // aqui sao implementados os eventos de teclado

    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return ScreenState::EXIT;

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
         ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
      al_play_sample(selectSound, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
      if (menuButtons[buttonPositionSelected].name == "NewGame") {
        std::cerr << "Botão NewGame selecionado!" << std::endl;
        inputNameScreen = "NewGame";
        return ScreenState::LOAD_NAME;
      } else if (menuButtons[buttonPositionSelected].name == "LoadGame") {
        std::cerr << "Botão LoadGame selecionado!" << std::endl;
        inputNameScreen = "LoadGame";
        return ScreenState::LOAD_NAME;
      } else if (menuButtons[buttonPositionSelected].name == "Settings") {
        std::cerr << "Botão Settings selecionado!" << std::endl;
      } else if (menuButtons[buttonPositionSelected].name == "Difficulty") {
        std::cerr << "Botão Difficulty selecionado!" << std::endl;
        return ScreenState::DIFFICULTY_MENU;
      } else if (menuButtons[buttonPositionSelected].name == "Leaderboard") {
        std::cerr << "Botão Leaderboard selecionado!" << std::endl;
        return ScreenState::LEADERBOARD_MENU;
      } else if (menuButtons[buttonPositionSelected].name == "Exit") {
        std::cerr << "Botão Exit selecionado!" << std::endl;
        return ScreenState::EXIT;
      }
    }

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
      menuButtons[buttonPositionSelected].buttonSelectState = 0;

      if (buttonPositionSelected == 5)
        buttonPositionSelected = 0;
      else
        buttonPositionSelected++;

      menuButtons[buttonPositionSelected].buttonSelectState = 1;
    }
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        ev.keyboard.keycode == ALLEGRO_KEY_UP) {
      menuButtons[buttonPositionSelected].buttonSelectState = 0;

      if (buttonPositionSelected == 0)
        buttonPositionSelected = 5;
      else
        buttonPositionSelected--;

      menuButtons[buttonPositionSelected].buttonSelectState = 1;
    }
      return ScreenState::MAIN_MENU;
}

  // aqui sao implementados as partes visuais
  // Desenha a logo
ScreenState MainMenu::draw(Motion& motion) {
    motion.loop();
    al_draw_bitmap(logoNormal, -20, -10, 0);
    // Desenha o botão NewGame
    if (menuButtons[0].buttonSelectState)
      al_draw_bitmap(buttonNewGameSelect, 496.5, 270, 0);
    else
      al_draw_bitmap(buttonNewGameDeselect, 496.5, 270, 0);

    // Desenha o botão LoadGame
    if (!menuButtons[1].buttonSelectState)
      al_draw_bitmap(buttonLoadGameSelect, 496.5, 340, 0);
    else
      al_draw_bitmap(buttonLoadGameDeselect, 496.5, 340, 0);

    // Desenha o botão Settings
    if (!menuButtons[2].buttonSelectState)
      al_draw_bitmap(buttonSettingsSelect, 496.5, 410, 0);
    else
      al_draw_bitmap(buttonSettingsDeselect, 496.5, 410, 0);

    // Desenha o botão Difficulty
    if (!menuButtons[3].buttonSelectState)
      al_draw_bitmap(buttonDifficultySelect, 496.5, 480, 0);
    else
      al_draw_bitmap(buttonDifficultyDeselect, 496.5, 480, 0);

    // Desenha o botão Leaderboard
    if (!menuButtons[4].buttonSelectState)
      al_draw_bitmap(buttonLeaderboardSelect, 496.5, 550, 0);
    else
      al_draw_bitmap(buttonLeaderboardDeselect, 496.5, 550, 0);

    // Desenha o botão Exit
    if (!menuButtons[5].buttonSelectState)
      al_draw_bitmap(buttonExitSelect, 496.5, 620, 0);
    else
      al_draw_bitmap(buttonExitDeselect, 496.5, 620, 0);
  return ScreenState::MAIN_MENU;
}
