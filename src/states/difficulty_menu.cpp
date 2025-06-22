/**
 * @file difficulty_menu.cpp
 * @brief Implementação da classe DifficultyMenu, que gerencia a tela de seleção de dificuldade.
 * @details Este módulo contém a lógica para manipulação de entrada do usuário,
 * atualização de estado e renderização dos elementos gráficos da tela de dificuldade.
 */

/** Bibliotecas necessárias */
#include <memory>
#include "../../include/states/difficulty_menu.hpp"
#include "../../include/init.hpp"
#include "../../include/states/main_menu.hpp"

/**
 * @brief Construtor da classe DifficultyMenu.
 * @details Inicializa e carrega todos os recursos gráficos (imagens e fontes)
 * necessários para a tela de seleção de dificuldade.
 */
DifficultyMenu::DifficultyMenu(){
    buttonDifficultyEasy = std::make_unique<Image>("assets/buttonDifficultyEasy.png", 40, 80);
    buttonDifficultyNormal = std::make_unique<Image>("assets/buttonDifficultyNormal.png", 40, 80);
    buttonDifficultyHard = std::make_unique<Image>("assets/buttonDifficultyHard.png", 40, 80);
    buttonSaveSelect = std::make_unique<Image>("assets/buttonSaveSelect.png", 496.5, 600);
    buttonSaveDeselect = std::make_unique<Image>("assets/buttonSaveDeselect.png", 496.5, 600);
    font = std::make_unique<TextFont>("assets/TextFont.ttf", 50);
    font->setColor(218, 15, 15);
}

/**
 * @brief Processa a entrada do usuário (teclado).
 * @param ev O evento da Allegro a ser processado.
 * @return Retorna um ponteiro para o próximo estado do jogo. Pode ser 'this' para
 * continuar neste estado, 'nullptr' para fechar, ou um novo MainMenu para retornar.
 */
State* DifficultyMenu::handle_input(const ALLEGRO_EVENT& ev) {
  if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

  // Trata a seleção de uma opção com Enter ou Espaço.
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
       ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
    selectSound->playSound(0.3);
    if (menuButtons[buttonPositionSelected].name == "Easy") {
      std::cout << "Dificuldade Easy selecionada!" << std::endl;
      difficultySelected = "Easy";
      difficulty =  0;
      buttonPositionSelected = 3;
      menuButtons[buttonPositionSelected].buttonSelectState = 1;
    } else if (menuButtons[buttonPositionSelected].name == "Normal") {
      std::cout << "Dificuldade Normal selecionada!" << std::endl;
      difficultySelected = "Normal";
      difficulty = 1;
      buttonPositionSelected = 3;
      menuButtons[buttonPositionSelected].buttonSelectState = 1;
    } else if (menuButtons[buttonPositionSelected].name == "Hard") {
      std::cout << "Dificuldade Hard selecionada!" << std::endl;
      difficultySelected = "Hard";
      difficulty = 2;
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
      else if (difficultySelected == "Hard")
        buttonPositionSelected = 2;

      menuButtons[buttonPositionSelected].buttonSelectState = 1;

      return new MainMenu();
    }
  }

  // Permite retornar ao menu principal com a tecla ESC, cancelando a seleção
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
    difficultySelected = "noOne";
    return new MainMenu();
  }

  // Trata a navegação entre os botões com as setas direcionais.
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

/**
 * @brief Executa ações ao entrar neste estado do menu.
 * @details Garante que o menu de dificuldade seja inicializado em um estado padrão,
 * com a dificuldade "Normal" pré-selecionada.
 */
void DifficultyMenu::enter() {
  difficultySelected = "Normal";

  // Reseta a seleção visual de todos os botões.
  for (auto& button : menuButtons) {
    button.buttonSelectState = 0;
  }

  // Define a seleção inicial para o botão "Normal".
  buttonPositionSelected = 1;
  menuButtons[buttonPositionSelected].buttonSelectState = 1;
}

/**
 * @brief Atualiza a lógica do estado a cada quadro.
 * @param motion Referência ao objeto de controle de animação do fundo.
 * @return Retorna 'this' para indicar a permanência no estado atual.
 */
State* DifficultyMenu::update(Motion& motion) {
  motion.update(); // Atualiza a animação de fundo.
  return this;
}

/**
 * @brief Desenha todos os elementos visuais do estado na tela.
 * @param motion Referência ao objeto de controle para desenhar o fundo animado.
 * @details Renderiza a imagem de fundo e os botões de acordo com a seleção atual
 * do usuário, além de um texto informativo.
 */
void DifficultyMenu::draw(Motion& motion) {
  motion.draw();

  // Desenha o fundo apropriado para a dificuldade selecionada.
  if (menuButtons[0].buttonSelectState)
    buttonDifficultyEasy->Draw();
  else if (menuButtons[1].buttonSelectState)
    buttonDifficultyNormal->Draw();
  else if (menuButtons[2].buttonSelectState)
    buttonDifficultyHard->Draw();

  // Desenha o botão de salvar no estado correto (selecionado ou não)
  if (menuButtons[3].buttonSelectState) {
    buttonSaveSelect->Draw();
  } else {
    buttonSaveDeselect->Draw();
  }

  // Escreve na tela qual dificuldade está selecionada no momento.
  if (difficultySelected == "Easy")
    font->writeText("Easy Difficulty selected!", ALLEGRO_ALIGN_CENTER, 640, 495);
  else if (difficultySelected == "Normal")
    font->writeText("Normal Difficulty selected!", ALLEGRO_ALIGN_CENTER, 640, 495);
  else if (difficultySelected == "Hard")
    font->writeText("Hard Difficulty selected!", ALLEGRO_ALIGN_CENTER, 640, 495);
}
