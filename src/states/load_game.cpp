#include "../include/states/load_game.hpp"
#include "../include/init.hpp"
#include "../include/states/main_menu.hpp"
#include "../include/states/play.hpp"
#include "../../include/assets.hpp"
#include <memory>

LoadName::LoadName() {
  buttonBackSelect = std::make_unique<Image>("assets/budttonBackSelect.png", 170, 490);
  buttonBackDeselect = std::make_unique<Image>("assets/buttonBackDeselect.png", 170, 490);
  buttonInsertSelect = std::make_unique<Image>("assets/buttonInsertSelect.png", 825, 490);
  buttonInsertDeselect = std::make_unique<Image>("assets/buttonInsertDeselect.png", 825, 490);
  nameCampSelect = std::make_unique<Image>("assets/nameCampSelect.png", 40, 100);
  nameCampDeselect = std::make_unique<Image>("assets/nameCampDeselect.png", 40, 100);
  nameFont = std::make_unique<TextFont>("assets/TextFont.ttf", 30);
  nameFont->setColor(0, 0, 0);
  errorFont = std::make_unique<TextFont>("assets/TextFont.ttf", 24);
  errorFont->setColor(218, 15, 15);
}

void LoadName::enter() {
  // Limpa os dados da última visita a esta tela
  this->playerNameString = "";
  this->errorSituation = noError;

  for (auto& button : menuButtons) {
    button.buttonSelectState = 0;
  }
  buttonPositionSelected = 2;
  menuButtons[buttonPositionSelected].buttonSelectState = 1;
}

State* LoadName::handle_input(const ALLEGRO_EVENT& ev) {
  // aqui sao implementados os eventos de teclado e mouse
  if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
       ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
    selectSound->playSound(0.3);
    if (menuButtons[buttonPositionSelected].name == "Insert") {
      std::cerr << "Botão Insert selecionado!" << std::endl;
      std::cerr << "Nome: " << playerNameString << std::endl;
      if (playerNameString != "") {
        if (inputNameScreen == "NewGame") {
          if (player.CheckingName(ranking, playerNameString)) {
            errorSituation = existName;
          } else {
            errorSituation = successInsert;
            player = Player(playerNameString, 0);
            player.SaveLeaderboard("Leaderboard.txt", ranking, player);
            playerNameString = "";
            errorSituation = noError;
            return new Play();
          }
        } else if (inputNameScreen == "LoadGame") {
          bool player_found = false;
          // Itera sobre o ranking para encontrar o jogador existente
          for (const auto& existing_player : ranking) {
            if (existing_player.GetName() == playerNameString) {
              player = existing_player;  // Atribui o jogador existente (com seu
                                         // score) à variável global
              player_found = true;
              break;  // Para o loop assim que encontrar
            }
          }

          if (player_found) {
            playerNameString = "";
            errorSituation = noError;      // Limpa qualquer erro anterior
            return new Play();  // Inicia o jogo
          } else {
            // O nome não foi encontrado no ranking
            errorSituation = noexistName;
          }
        }
      } else {
        errorSituation = noName;
      }
      std::cerr << errorSituation << std::endl;
    } else if (menuButtons[buttonPositionSelected].name == "Back") {
      std::cerr << "Botão Back selecionado!" << std::endl;
      playerNameString = "";
      errorSituation = 0;
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
      if (!playerNameString.empty()) {
        playerNameString.pop_back();
        std::cerr << "Caractere apagado" << std::endl;
      }
    } else if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
      if (ev.keyboard.unichar >= 32 && ev.keyboard.unichar <= 126) {
        if (playerNameString.length() < MAX_INPUT_LENGTH) {
          playerNameString += toupper(static_cast<char>(ev.keyboard.unichar));
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
    errorSituation = noError;
    return new MainMenu();
  }

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
  motion.update();

  return this;
}

void LoadName::draw(Motion& motion) {
  motion.draw();
  // Desenha o botão NewGame
    if (menuButtons[0].buttonSelectState)
      buttonBackSelect->Draw();
    else
      buttonBackDeselect->Draw();

    if (menuButtons[1].buttonSelectState)
      buttonInsertSelect->Draw();
    else
      buttonInsertDeselect->Draw();

    if (menuButtons[2].buttonSelectState)
      nameCampSelect->Draw();
    else
      nameCampDeselect->Draw();

  nameFont->writeText(playerNameString.c_str(), ALLEGRO_ALIGN_LEFT, 280, 283);

    if (errorSituation == existName) {
      errorFont->writeText("Your player is already registered", ALLEGRO_ALIGN_CENTER, 640, 380);
    }
    if (errorSituation == noexistName) {
      errorFont->writeText("This player does not exist!", ALLEGRO_ALIGN_CENTER, 640, 380);
    }
    if (errorSituation == successInsert) {
      errorFont->writeText("Name entered successfully.", ALLEGRO_ALIGN_CENTER, 640, 380);
    }
    if (errorSituation == noName) {
      errorFont->writeText("No name entered. Please enter a name!", ALLEGRO_ALIGN_CENTER, 640, 380);
    }
}
