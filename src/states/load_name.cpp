#include "states/load_game.hpp"
#include "states/main_menu.hpp"

State* LoadName::loop(FlappyBird* game) {
  // aqui sao implementados os eventos de teclado e mouse
  while (al_get_next_event(queue, &ev)) {
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        (ev.keyboard.keycode == ALLEGRO_KEY_ENTER)) {
      if (menuButtons[buttonPositionSelected].name == "Insert") {
        std::cerr << "Botão Insert selecionado!" << std::endl;
        std::cerr << "Nome: " << user_name_string << std::endl;
        if (user_name_string != "") {
          if (inputNameScreen == "NewGame") {
            if (user_name_string == "EXISTE")
              nameError = 1;
            else
              nameError = 3;
          } else if (inputNameScreen == "LoadGame") {
            if (user_name_string == "NAOEXISTE")
              nameError = 2;
            else
              nameError = 3;
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
        return new MainMenu();
      } else if (menuButtons[buttonPositionSelected].name == "NameCamp") {
        menuButtons[buttonPositionSelected].buttonSelectState = 0;
        buttonPositionSelected = 1;
        menuButtons[buttonPositionSelected].buttonSelectState = 1;
        std::cerr << "Campo de texto selecionado!" << std::endl;
      }
      // reseta antes de começar a partida
      // play.reset();
      // return ScreenState::PLAY;
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

    // aqui sao implementados as partes visuais
    // Desenha o background
    al_draw_bitmap(background, 0, 0, 0);

    // Desenha o botão NewGame
    if (menuButtons[0].buttonSelectState)
      al_draw_bitmap(buttonBackSelect, 102.5, 400, 0);
    else
      al_draw_bitmap(buttonBackDeselect, 102.5, 400, 0);

    if (menuButtons[1].buttonSelectState)
      al_draw_bitmap(buttonInsertSelect, 890.5, 400, 0);
    else
      al_draw_bitmap(buttonInsertDeselect, 890.5, 400, 0);

    if (menuButtons[2].buttonSelectState)
      al_draw_bitmap(nameCampSelect, 102.5, 150, 0);
    else
      al_draw_bitmap(nameCampDeselect, 102.5, 150, 0);

    al_draw_text(font, al_map_rgb(0, 0, 0), 210, 250, ALLEGRO_ALIGN_LEFT,
                 user_name_string.c_str());

    if (nameError == 1) {
      al_draw_text(font, al_map_rgb(218, 15, 15), 210, 320, ALLEGRO_ALIGN_LEFT,
                   "Your player is already registered");
    }
    if (nameError == 2) {
      al_draw_text(font, al_map_rgb(218, 15, 15), 210, 320, ALLEGRO_ALIGN_LEFT,
                   "This player does not exist!");
    }
    if (nameError == 3) {
      al_draw_text(font, al_map_rgb(218, 15, 15), 210, 320, ALLEGRO_ALIGN_LEFT,
                   "Name entered successfully.");
    }
    if (nameError == 4) {
      al_draw_text(font, al_map_rgb(218, 15, 15), 210, 320, ALLEGRO_ALIGN_LEFT,
                   "No name entered. Please enter a name!");
    }
  }
  // esse eh o update
  al_flip_display();
  return new LoadName();
}
