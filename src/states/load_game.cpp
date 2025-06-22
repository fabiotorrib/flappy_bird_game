#include "../../include/states/load_game.hpp"
#include <memory>
/**
 * @file load_game.cpp
 * @brief Implementação da classe LoadName, responsável pela tela de inserção de nome do jogador.
 * @details Este módulo gerencia a entrada de texto para o nome do jogador, valida o nome
 * para um novo jogo ou carrega um jogador existente, e lida com a navegação e exibição de erros.
 */

/** Bibliotecas necessárias */
#include <memory>
#include "../../include/states/load_game.hpp"
#include "../../include/assets.hpp"
#include "../../include/init.hpp"
#include "../../include/states/main_menu.hpp"
#include "../../include/states/play.hpp"

/**
 * @brief Construtor da classe LoadName.
 * @details Carrega todos os recursos gráficos (imagens, fontes) e sonoros
 * necessários para a tela de inserção de nome.
 */
LoadName::LoadName() {
  buttonBackSelect =
      std::make_unique<Image>("assets/buttonBackSelect.png", 170, 490);
  buttonBackDeselect =
      std::make_unique<Image>("assets/buttonBackDeselect.png", 170, 490);
  buttonInsertSelect =
      std::make_unique<Image>("assets/buttonInsertSelect.png", 825, 490);
  buttonInsertDeselect =
      std::make_unique<Image>("assets/buttonInsertDeselect.png", 825, 490);
  nameCampSelect =
      std::make_unique<Image>("assets/nameCampSelect.png", 40, 100);
  nameCampDeselect =
      std::make_unique<Image>("assets/nameCampDeselect.png", 40, 100);
  nameFont = std::make_unique<TextFont>("assets/TextFont.ttf", 46);
  nameFont->setColor(0, 0, 0);
  errorFont = std::make_unique<TextFont>("assets/TextFont.ttf", 50);
  errorFont->setColor(218, 15, 15);
}

/**
 * @brief Executado ao entrar no estado. Prepara a tela para uma nova interação.
 * @details Limpa o nome do jogador e qualquer mensagem de erro de uma visita anterior
 * e redefine o foco do menu para o campo de inserção de nome.
 */
void LoadName::enter() {
  this->playerNameString = "";
  this->errorSituation = noError;

  // Reseta o estado visual de todos os botões.
  for (auto& button : menuButtons) {
    button.buttonSelectState = 0;
  }

  // Define o campo selecionado inicial como o campo de texto.
  buttonPositionSelected = 2;
  menuButtons[buttonPositionSelected].buttonSelectState = 1;
}

/**
 * @brief Gerencia toda a entrada de teclado do usuário.
 * @param ev O evento da Allegro a ser processado.
 * @return State* Ponteiro para o próximo estado. Retorna 'nullptr' para fechar,
 * 'new MainMenu()' ou 'new Play()' para transição, ou 'this' para permanecer.
 */
State* LoadName::handle_input(const ALLEGRO_EVENT& ev) {
  if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

  // Trata a seleção de uma opção com Enter ou Espaço.
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
       ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
    selectSound->playSound(0.3);
    if (menuButtons[buttonPositionSelected].name == "Insert") {
      std::cerr << "Botão Insert selecionado!" << std::endl;
      std::cerr << "Nome: " << playerNameString << std::endl;
      // Valida o nome inserido e decide a próxima ação.
      if (playerNameString != "") {
        if (inputNameScreen == "NewGame") {
          // Se for um novo jogo, verifica se o nome já existe.
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
          // Se for para carregar um jogo, verifica se o nome existe para carregá-lo.
          bool player_found = false;
          for (const auto& existing_player : ranking) {
            if (existing_player.GetName() == playerNameString) {
              player = existing_player;  // Atribui o jogador existente (com seu
                                         // score) à variável global
              player_found = true;
              break;  
            }
          }

          if (player_found) {
            playerNameString = "";
            errorSituation = noError;  // Limpa qualquer erro anterior
            return new Play();         // Inicia o jogo
          } else {
            // Erro se o nome não foi encontrado no ranking
            errorSituation = noexistName;
          }
        }
      } else {
        errorSituation = noName; // Erro se nenhum nome foi digitado.
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

  // --- Lógica de Entrada de Texto ---
  // Ativa apenas quando o campo de nome está selecionado
  if (menuButtons[2].buttonSelectState) {
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
      if (!playerNameString.empty()) {
        playerNameString.pop_back();
        std::cerr << "Caractere apagado" << std::endl;
      }
    } else if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
      // Adiciona caracteres ASCII imprimíveis ao nome, convertendo para maiúsculo.
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

  // Permite retornar ao menu principal com a tecla ESC, cancelando a seleção.
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
    errorSituation = noError; // Reseta a situação de erro.
    return new MainMenu();
  }

  // Trata a navegação entre os botões com as setas direcionais.
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

/**
 * @brief Atualiza a lógica do estado do movimento/animação de fundo a cada quadro.
 * @param motion Referência ao objeto de controle de animação do fundo.
 * @return State* Retorna 'this' para indicar a permanência no estado atual.
 */
State* LoadName::update(Motion& motion) {
  motion.update();
  return this;
}

/**
 * @brief Desenha todos os elementos visuais do estado na tela.
 * @param motion Referência para desenhar o fundo animado.
 * @details Renderiza os botões, o campo de texto com o nome do jogador e as
 * mensagens de erro, se houver, com base no estado atual da interação.
 */
void LoadName::draw(Motion& motion) {
  motion.draw();
  
  // Desenha os botões de acordo com o estado de seleção.
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

  // Desenha o nome que o jogador está digitando.  
  nameFont->writeText(playerNameString.c_str(), ALLEGRO_ALIGN_LEFT, 280, 283);

  // Exibe a mensagem de erro apropriada, se houver.
  if (errorSituation == existName) {
    errorFont->writeText("Your player is already registered",
                         ALLEGRO_ALIGN_CENTER, 640, 380);
  }
  if (errorSituation == noexistName) {
    errorFont->writeText("This player does not exist!", ALLEGRO_ALIGN_CENTER,
                         640, 380);
  }
  if (errorSituation == successInsert) {
    errorFont->writeText("Name entered successfully.", ALLEGRO_ALIGN_CENTER,
                         640, 380);
  }
  if (errorSituation == noName) {
    errorFont->writeText("No name entered. Please enter a name!",
                         ALLEGRO_ALIGN_CENTER, 640, 380);
  }
}
