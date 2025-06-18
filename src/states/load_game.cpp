#include "../../include/states/main_menu.hpp"
#include "../../include/states/load_game.hpp"  //necessario para modificar o objeto play (ou qualquer outro)


ScreenState LoadName::loop(const ALLEGRO_EVENT& ev) {
  // aqui sao implementados os eventos de teclado e mouse
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return ScreenState::EXIT;

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
         ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
      al_play_sample(selectSound, 0., 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
      if (menuButtons[buttonPositionSelected].name == "Insert") {
        std::cerr << "Botão Insert selecionado!" << std::endl;
        std::cerr << "Nome: " << user_name_string << std::endl;
        if (user_name_string != "") {
          if (inputNameScreen == "NewGame") {
            if (player.CheckingName(ranking, user_name_string)){
              nameError = 1;
            } else {
              nameError = 3;
              player = Player(user_name_string, 0);
              player.SaveLeaderboard("Leaderboard.txt", ranking, player);
              user_name_string = "";
              nameError = 0;
              return PLAY;
            }
          } else if (inputNameScreen == "LoadGame") {
            if (!player.CheckingName(ranking, user_name_string)){
              nameError = 2;
            } else {
              nameError = 3;
              player = Player(user_name_string, 0);
              player.SaveLeaderboard("Leaderboard.txt", ranking, player);
              user_name_string = "";
              nameError = 0;
              return PLAY;
            }
          }
        } else {
          nameError = 4;
        }
        std::cerr << nameError << std::endl;
      } else if (menuButtons[buttonPositionSelected].name == "Back") {
        std::cerr << "Botão Back selecionado!" << std::endl;
        user_name_string = "";
        nameError = 0;
        menuButtons[buttonPositionSelected].buttonSelectState = 0;
        buttonPositionSelected = 2;
        menuButtons[buttonPositionSelected].buttonSelectState = 1;
        return ScreenState::MAIN_MENU;
      } else if (menuButtons[buttonPositionSelected].name == "NameCamp") {
        menuButtons[buttonPositionSelected].buttonSelectState = 0;
        buttonPositionSelected = 1;
        menuButtons[buttonPositionSelected].buttonSelectState = 1;
        std::cerr << "Campo de texto selecionado!" << std::endl;
      }
      
    }

    if (menuButtons[2].buttonSelectState) {
      if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
          ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
        if (!user_name_string.empty()) {
          user_name_string.pop_back();
          std::cerr << "Caractere apagado" << std::endl;
        }
      } else if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
        if (ev.keyboard.unichar >= 32 && ev.keyboard.unichar <= 126) {
          if (user_name_string.length() < MAX_INPUT_LENGTH) {
            user_name_string += toupper(static_cast<char>(ev.keyboard.unichar));
            std::cerr << "Caractere adicionado: "
                      << static_cast<char>(
                            toupper(static_cast<char>(ev.keyboard.unichar)))
                      << std::endl;
          }
        }
      }
    }

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
      nameError = 0;
      return ScreenState::MAIN_MENU;
    }
    ///////

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_DOWN:
        case ALLEGRO_KEY_LEFT:
          menuButtons[buttonPositionSelected].buttonSelectState = 0;

          if (buttonPositionSelected == 2)
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
              buttonPositionSelected = 2;
            else
              buttonPositionSelected--;

            menuButtons[buttonPositionSelected].buttonSelectState = 1;
          }
          break;
      }
    }
  return ScreenState::LOAD_NAME;
  }




ScreenState LoadName::draw(Motion& motion) {
      motion.loop();
      // Desenha o botão NewGame
      if (menuButtons[0].buttonSelectState)
        al_draw_bitmap(buttonBackSelect, 170, 490, 0);
      else
        al_draw_bitmap(buttonBackDeselect, 170, 490, 0);

      if (menuButtons[1].buttonSelectState)
        al_draw_bitmap(buttonInsertSelect, 825, 490, 0);
      else
        al_draw_bitmap(buttonInsertDeselect, 825, 490, 0);

      if (menuButtons[2].buttonSelectState)
        al_draw_bitmap(nameCampSelect, 40, 100, 0);
      else
        al_draw_bitmap(nameCampDeselect, 40, 100, 0);

      al_draw_text(font, al_map_rgb(0, 0, 0), 280, 286, ALLEGRO_ALIGN_LEFT,
                  user_name_string.c_str());

      if (nameError == 1) {
        al_draw_text(font, al_map_rgb(218, 15, 15), 640, 380,
                    ALLEGRO_ALIGN_CENTER, "Your player is already registered");
      }
      if (nameError == 2) {
        al_draw_text(font, al_map_rgb(218, 15, 15), 640, 380,
                    ALLEGRO_ALIGN_CENTER, "This player does not exist!");
      }
      if (nameError == 3) {
        al_draw_text(font, al_map_rgb(218, 15, 15), 640, 380,
                    ALLEGRO_ALIGN_CENTER, "Name entered successfully.");
      }
      if (nameError == 4) {
        al_draw_text(font, al_map_rgb(218, 15, 15), 640, 380,
                    ALLEGRO_ALIGN_CENTER,
                    "No name entered. Please enter a name!");
      }
  
  return ScreenState::LOAD_NAME;
  }
