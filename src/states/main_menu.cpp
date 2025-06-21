/**
 * @file main_menu.cpp
 * @brief Implementação da classe MainMenu, o estado principal e tela inicial do jogo.
 * @details Este módulo gerencia a navegação do menu principal, o carregamento de
 * todos os recursos visuais da tela e a transição para outros estados do jogo
 * (Novo Jogo, Carregar, Configurações, etc.).
 */

/** Bibliotecas necessárias */
#include <memory>
#include "../include/states/main_menu.hpp"
#include "../include/init.hpp"
#include "../include/states/difficulty_menu.hpp"
#include "../include/states/leaderboard_menu.hpp"
#include "../include/states/load_game.hpp"
#include "../include/states/settings_menu.hpp"

/**
 * @brief Construtor da classe MainMenu.
 * @details Carrega todos os recursos visuais necessários para a tela do menu,
 * incluindo o logo e as imagens para cada botão nos estados selecionado e não selecionado.
 */
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

//Variável global para comunicar ao estado LoadName qual modo ele deve operar.
std::string inputNameScreen = "";

/**
 * @brief Prepara o menu para exibição.
 * @details Esta função é chamada toda vez que o MainMenu se torna o estado ativo.
 * Ela garante que o menu seja resetado para um estado inicial consistente,
 * com o primeiro botão selecionado.
 */
void MainMenu::enter() {
  // Zera o estado de seleção de todos os botões.
  for (auto& button : menuButtons) {
    button.buttonSelectState = 0;
  }

  // Define o primeiro botão ("NewGame") como o selecionado por padrão.
  buttonPositionSelected = 0;
  if (!menuButtons.empty()) {
    menuButtons[buttonPositionSelected].buttonSelectState = 1;
  }
}

/**
 * @brief Atualiza a lógica do estado do movimento/animação de fundo a cada quadro.
 * @param motion Referência ao objeto de controle de animação do fundo.
 * @return Retorna 'this' para indicar a permanência no estado atual.
 */
State* MainMenu::update(Motion& motion) {
  motion.update();
  return this;
}

/**
 * @brief Gerencia a entrada do teclado para navegar e selecionar opções no menu.
 * @param ev O evento da Allegro a ser processado.
 * @return Retorna um ponteiro para o próximo estado do jogo, ou nullptr para sair.
 */
State* MainMenu::handle_input(const ALLEGRO_EVENT& ev) {
  if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

  // Trata a seleção de uma opção com Enter ou Espaço.
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
       ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
    selectSound->playSound(0.3);
    // A função cria uma nova instância de estado para a qual o jogo deve transitar.
    // Isso representa a transição de telas.
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
      return new SettingsMenu();
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

  // Trata a navegação entre os botões com as setas direcionais.
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

/**
 * @brief Desenha todos os elementos visuais do menu principal na tela.
 * @param motion Referência para desenhar o fundo animado.
 * @details Renderiza o logo, o fundo e cada um dos botões com base na interação do usuário.
 */
void MainMenu::draw(Motion& motion) {
  motion.draw();
  logoNormal->Draw();

  if (menuButtons[0].buttonSelectState)
    buttonNewGameSelect->Draw();
  else
    buttonNewGameDeselect->Draw();

 
  if (!menuButtons[1].buttonSelectState)
    buttonLoadGameSelect->Draw();
  else
    buttonLoadGameDeselect->Draw();

 
  if (!menuButtons[2].buttonSelectState)
    buttonSettingsSelect->Draw();
  else
    buttonSettingsDeselect->Draw();

 
  if (!menuButtons[3].buttonSelectState)
    buttonDifficultySelect->Draw();
  else
    buttonDifficultyDeselect->Draw();


  if (!menuButtons[4].buttonSelectState)
    buttonLeaderboardSelect->Draw();
  else
    buttonLeaderboardDeselect->Draw();

  if (!menuButtons[5].buttonSelectState)
    buttonExitSelect->Draw();
  else
    buttonExitDeselect->Draw();
}
