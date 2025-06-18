#include "../include/states/load_game.hpp"
#include "../include/init.hpp"
#include "../include/states/main_menu.hpp"
#include "../include/states/play.hpp"

void LoadName::enter() {
  // Limpa os dados da última visita a esta tela
  this->user_name_string = "";
  this->nameError = 0;  // 0 significa "sem erro"

  // Reseta a seleção do botão para o padrão (o campo de nome)
  for (auto& button : menuButtons) {
    button.buttonSelectState = 0;
  }
  // A posição 2, no seu código, corresponde ao campo de nome ("NameCamp")
  buttonPositionSelected = 2;
  menuButtons[buttonPositionSelected].buttonSelectState = 1;
}

State* LoadName::handle_input(const ALLEGRO_EVENT& ev) {
  // aqui sao implementados os eventos de teclado e mouse
  if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
       ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
    al_play_sample(selectSound, 0., 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    if (menuButtons[buttonPositionSelected].name == "Insert") {
      std::cerr << "Botão Insert selecionado!" << std::endl;
      std::cerr << "Nome: " << user_name_string << std::endl;
      if (user_name_string != "") {
        if (inputNameScreen == "NewGame") {
          if (player.CheckingName(ranking, user_name_string)) {
            nameError = 1;
          } else {
            nameError = 3;
            player = Player(user_name_string, 0);
            player.SaveLeaderboard("Leaderboard.txt", ranking, player);
            user_name_string = "";
            nameError = 0;
            return new Play();
          }
        } else if (inputNameScreen == "LoadGame") {
          bool player_found = false;
          // Itera sobre o ranking para encontrar o jogador existente
          for (const auto& existing_player : ranking) {
            if (existing_player.GetName() == user_name_string) {
              player = existing_player;  // Atribui o jogador existente (com seu
                                         // score) à variável global
              player_found = true;
              break;  // Para o loop assim que encontrar
            }
          }

          if (player_found) {
            // Sucesso, o jogador foi carregado
            user_name_string = "";
            nameError = 0;      // Limpa qualquer erro anterior
            return new Play();  // Inicia o jogo
          } else {
            // O nome não foi encontrado no ranking
            nameError = 2;  // "This player does not exist!"
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
      return new MainMenu();
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
    return new MainMenu();
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
  return this;
}

State* LoadName::update(Motion& motion) {
  // AVISO: Para que isto funcione perfeitamente, sua classe Motion deve ser
  // separada em motion.update() e motion.render(), como discutimos.
  motion.update();

  // O update do menu nunca causa uma transição de estado.
  return this;
}

void LoadName::draw(Motion& motion) {
  motion.draw();
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
    al_draw_text(font, al_map_rgb(218, 15, 15), 640, 380, ALLEGRO_ALIGN_CENTER,
                 "Your player is already registered");
  }
  if (nameError == 2) {
    al_draw_text(font, al_map_rgb(218, 15, 15), 640, 380, ALLEGRO_ALIGN_CENTER,
                 "This player does not exist!");
  }
  if (nameError == 3) {
    al_draw_text(font, al_map_rgb(218, 15, 15), 640, 380, ALLEGRO_ALIGN_CENTER,
                 "Name entered successfully.");
  }
  if (nameError == 4) {
    al_draw_text(font, al_map_rgb(218, 15, 15), 640, 380, ALLEGRO_ALIGN_CENTER,
                 "No name entered. Please enter a name!");
  }
}
