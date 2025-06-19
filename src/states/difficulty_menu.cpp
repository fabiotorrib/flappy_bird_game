#include "../include/states/difficulty_menu.hpp"
#include "../include/init.hpp"
#include "../include/states/main_menu.hpp"
#include <memory>

DifficultyMenu::DifficultyMenu(){
    buttonDifficultyEasy = std::make_unique<Image>("assets/buttonDifficultyEasy.png", 40, 80);
    buttonDifficultyNormal = std::make_unique<Image>("assets/buttonDifficultyNormal.png", 40, 80);
    buttonDifficultyHard = std::make_unique<Image>("assets/buttonDifficultyHard.png", 40, 80);
    buttonSaveSelect = std::make_unique<Image>("assets/buttonSaveSelect.png", 496.5, 600);
    buttonSaveDeselect = std::make_unique<Image>("assets/buttonSaveDeselect.png", 496.5, 600);
    font = std::make_unique<TextFont>("assets/TextFont.ttf", 24);
    font->setColor(218, 15, 15);
}

State* DifficultyMenu::handle_input(const ALLEGRO_EVENT& ev) {
  // aqui sao implementados os eventos de teclado e mouse
  if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
       ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
    selectSound->playSound(0.3);
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

      return new MainMenu();
    }
  }

  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
    difficultySelected = "noOne";
    return new MainMenu();
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
  return this;
}

void DifficultyMenu::enter() {
  difficultySelected = "Normal";

  // Reseta a seleção visual dos botões
  for (auto& button : menuButtons) {
    button.buttonSelectState = 0;
  }

  // Define a seleção inicial para o botão "Normal" (posição 1)
  buttonPositionSelected = 1;
  menuButtons[buttonPositionSelected].buttonSelectState = 1;
}

State* DifficultyMenu::update(Motion& motion) {
  motion.update();

  return this;
}

void DifficultyMenu::draw(Motion& motion) {
  motion.draw();
  if (menuButtons[0].buttonSelectState)
    buttonDifficultyEasy->Draw();
  else if (menuButtons[1].buttonSelectState)
    buttonDifficultyNormal->Draw();
  else if (menuButtons[2].buttonSelectState)
    buttonDifficultyHard->Draw();

  if (menuButtons[3].buttonSelectState) {
    buttonSaveSelect->Draw();
  } else {
    buttonSaveDeselect->Draw();
  }

  if (difficultySelected == "Easy")
    font->writeText("Easy Difficulty selected!", ALLEGRO_ALIGN_CENTER, 640, 495);
  else if (difficultySelected == "Normal")
    font->writeText("Normal Difficulty selected!", ALLEGRO_ALIGN_CENTER, 640, 495);
  else if (difficultySelected == "Hard")
    font->writeText("Hard Difficulty selected!", ALLEGRO_ALIGN_CENTER, 640, 495);
}
