#include "../include/states/main_menu.hpp"
#include "../include/init.hpp"
#include "../include/states/difficulty_menu.hpp"
#include "../include/states/leaderboard_menu.hpp"
#include "../include/states/load_game.hpp"
#include <memory>

MainMenu::MainMenu(){
    logoNormal = std::make_unique<Image>("assets/logoNormal.png", -20, -10);
    buttonNewGameSelect = std::make_unique<Image>("assets/buttonNewGameSelect.png", 496.5, 270);
    buttonNewGameDeselect = std::make_unique<Image>("assets/buttonNewGameDeselect.png", 496.5, 270);
    buttonLoadGameSelect = std::make_unique<Image>("assets/buttonLoadGameSelect.png", 496.5, 340);
    buttonLoadGameDeselect = std::make_unique<Image>("assets/buttonLoadGameDeselect.png", 496.5, 340);
    buttonSettingsSelect = std::make_unique<Image>("assets/buttonSettingsSelect.png", 496.5, 410);
    buttonSettingsDeselect = std::make_unique<Image>("assets/buttonSettingsDeselect.png", 496.5, 410);
    buttonDifficultySelect = std::make_unique<Image>("assets/buttonDifficultySelect.png", 496.5, 480);
    buttonDifficultyDeselect = std::make_unique<Image>("assets/buttonDifficultyDeselect.png", 496.5, 480);
    buttonLeaderboardSelect = std::make_unique<Image>("assets/buttonLeaderboardSelect.png", 496.5, 550);
    buttonLeaderboardDeselect = std::make_unique<Image>("assets/buttonLeaderboardDeselect.png", 496.5, 550);
    buttonExitSelect = std::make_unique<Image>("assets/buttonExitSelect.png", 496.5, 620);
    buttonExitDeselect = std::make_unique<Image>("assets/buttonExitDeselect.png", 496.5, 620);
}

std::string inputNameScreen = "";
void MainMenu::enter() {
  // Este código é chamado toda vez que o menu se torna a tela ativa.

  // Zera o estado de seleção de todos os botões
  for (auto& button : menuButtons) {
    button.buttonSelectState = 0;
  }

  // Define o primeiro botão ("NewGame") como o selecionado
  buttonPositionSelected = 0;
  if (!menuButtons.empty()) {
    menuButtons[buttonPositionSelected].buttonSelectState = 1;
  }
}

State* MainMenu::update(Motion& motion) {
  motion.update();

  return this;
}

State* MainMenu::handle_input(const ALLEGRO_EVENT& ev) {
  if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
       ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
    selectSound->playSound(0.3);
    if (menuButtons[buttonPositionSelected].name == "NewGame") {
      std::cerr << "Botão NewGame selecionado!" << std::endl;
      inputNameScreen = "NewGame";
      return new LoadName();
    } else if (menuButtons[buttonPositionSelected].name == "LoadGame") {
      std::cerr << "Botão LoadGame selecionado!" << std::endl;
      inputNameScreen = "LoadGame";
      return new LoadName();
    } else if (menuButtons[buttonPositionSelected].name == "Settings") {
      std::cerr << "Botão Settings selecionado!" << std::endl;
    } else if (menuButtons[buttonPositionSelected].name == "Difficulty") {
      std::cerr << "Botão Difficulty selecionado!" << std::endl;
      return new DifficultyMenu();
    } else if (menuButtons[buttonPositionSelected].name == "Leaderboard") {
      std::cerr << "Botão Leaderboard selecionado!" << std::endl;
      return new LeaderboardMenu();
    } else if (menuButtons[buttonPositionSelected].name == "Exit") {
      std::cerr << "Botão Exit selecionado!" << std::endl;
      return nullptr;
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
  return this;
}
// aqui sao implementados as partes visuais
// Desenha a logo
void MainMenu::draw(Motion& motion) {
  motion.draw();
  logoNormal->Draw();
  // Desenha o botão NewGame
  if (menuButtons[0].buttonSelectState)
    buttonNewGameSelect->Draw();
  else
    buttonNewGameDeselect->Draw();

  // Desenha o botão LoadGame
  if (!menuButtons[1].buttonSelectState)
    buttonLoadGameSelect->Draw();
  else
    buttonLoadGameDeselect->Draw();

  // Desenha o botão Settings
  if (!menuButtons[2].buttonSelectState)
    buttonSettingsSelect->Draw();
  else
    buttonSettingsDeselect->Draw();

  // Desenha o botão Difficulty
  if (!menuButtons[3].buttonSelectState)
    buttonDifficultySelect->Draw();
  else
    buttonDifficultyDeselect->Draw();

  // Desenha o botão Leaderboard
  if (!menuButtons[4].buttonSelectState)
    buttonLeaderboardSelect->Draw();
  else
    buttonLeaderboardDeselect->Draw();

  // Desenha o botão Exit
  if (!menuButtons[5].buttonSelectState)
    buttonExitSelect->Draw();
  else
    buttonExitDeselect->Draw();
}
