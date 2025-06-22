/**
 * @file play.cpp
 * @brief Implementacao da classe Play.
 * @details Controla o loop principal de jogo: entrada, atualizacao e desenho,
 *          alem de transicoes para pausa e game over.
 */

#include "../../include/states/play.hpp"
#include "../../include/states/main_menu.hpp"  // Para 'new MainMenu()'


/**
 * @brief Construtor padrao.
 * @details Carrega todos os bitmaps, botoes e fontes exigidos durante o estado
 *          de jogo.
 */
Play::Play() {
  logoGameOver = std::make_unique<Image>("assets/logoGameOver.png", 0, -200);
  buttonTryagainSelect =
      std::make_unique<Image>("assets/buttonTryagainSelect.png", 496.5, 390);
  buttonTryagainDeselect =
      std::make_unique<Image>("assets/buttonTryagainDeselect.png", 496.5, 390);
  buttonExitSelect =
      std::make_unique<Image>("assets/buttonExitSelect.png", 496.5, 490);
  buttonExitDeselect =
      std::make_unique<Image>("assets/buttonExitDeselect.png", 496.5, 490);
  buttonPause = std::make_unique<Image>("assets/buttonPause.png", 40, 0);
  font = std::make_unique<TextFont>("assets/TextFont.ttf", 40);
  font->setColor(255, 255, 255);
}

/**
 * @brief Inicia ou reinicia a partida.
 * @details Cria um novo FlappyBird, limpa pontuacao e define status PLAY.
 */
void Play::enter() {
  // Este código é chamado toda vez que o jogo começa.
  // Garante que cada partida seja nova e limpa.
  flappy = std::make_unique<FlappyBird>();
  flappy->reset();
  flappy->set_current_player(player);
  al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
  status = ScreenState::PLAY;  // Reseta o status interno para "play"
}

/**
 * @brief Processa entrada do usuario.
 * @details Mapeia teclas para pulo, pausa, retomada e menu de game over.
 * @param ev Evento Allegro recebido da fila.
 * @return Ponteiro para o estado resultante apos o processamento.
 */
State* Play::handle_input(const ALLEGRO_EVENT& ev) {
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
    switch (status) {
      case ScreenState::PLAY:
        if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
          int flappy_state = flappy->get_state();
          if (flappy_state == 1) {         // Se estiver aguardando input
            flappy->starter();             // Começa o jogo
          } else if (flappy_state == 2) {  // Se já estiver jogando
            flappy->jump();                // Pula
          }
        } else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
          status = ScreenState::PAUSE;
          flappy->breaker();
        }
        break;

      case ScreenState::PAUSE:
        if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
          status = ScreenState::PLAY;
          flappy->unbreaker();
        } else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
          return new MainMenu();
        }
        break;

      case ScreenState::GAME_OVER:
        if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
            ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
          if (menuButtons[buttonPositionSelected].name == "TryAgain") {
            std::cerr << "Botão TryAgain selecionado!" << std::endl;
            status = ScreenState::PLAY;
            Play::enter();
          } else if (menuButtons[buttonPositionSelected].name == "Exit") {
            std::cerr << "Botão Exit selecionado!" << std::endl;
            for (auto& button : menuButtons) {
              button.buttonSelectState = 0;
            }
            buttonPositionSelected = 0;
            menuButtons[buttonPositionSelected].buttonSelectState = 1;
            al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
            return new MainMenu();
          }

        } else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
          return new MainMenu();
        }
        if (ev.keyboard.keycode == ALLEGRO_KEY_UP ||
            ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
          menuButtons[buttonPositionSelected].buttonSelectState = 0;

          if (buttonPositionSelected == 0)
            buttonPositionSelected = 1;
          else
            buttonPositionSelected--;

          menuButtons[buttonPositionSelected].buttonSelectState = 1;
        }
        if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN ||
            ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {
          menuButtons[buttonPositionSelected].buttonSelectState = 0;

          if (buttonPositionSelected == 1)
            buttonPositionSelected = 0;
          else
            buttonPositionSelected++;

          menuButtons[buttonPositionSelected].buttonSelectState = 1;
        }
        break;
    }
  }
  // Se nenhuma tecla de transição de estado foi apertada, continua no estado
  // atual.
  return this;
}
/**
 * @brief Atualiza simulacao do jogo.
 * @details Avanca objetos quando status eh PLAY e detecta colisoes para
 *          transicionar a GAME_OVER.
 * @param motion Sistema de camera/transformacoes para parallax ou shake.
 * @return Ponteiro para o estado atual para continuidade.
 */
State* Play::update(Motion& motion) {
  // A lógica do jogo só avança se o status interno for PLAY.
  if (status == ScreenState::PLAY) {
    flappy->update();

    if (flappy->check_collisions()) {
      flappy->set_playerscore();
      flappy->saveCurrentPlayerScore();
      // Apenas muda o status interno. A transição para outra tela
      // (como MainMenu) será feita pelo handle_input quando o
      // jogador pressionar uma tecla.
      status = ScreenState::GAME_OVER;
    }
  }
  motion.update();

  return this;
}

/**
 * @brief Renderiza cena completa.
 * @details Desenha fundo, personagem, menus de pausa ou game over
 *          conforme o estado em curso.
 * @param motion Sistema de camera/transformacoes usado na renderizacao.
 */
void Play::draw(Motion& motion) {
  motion.draw();
  flappy->draw();

  if (status == PAUSE) {
    buttonPause->Draw();
    font->writeText("Press Esc to back to Main Menu.", ALLEGRO_ALIGN_CENTER,
                    615, 340);
    font->writeText("Press Space to resume playing.", ALLEGRO_ALIGN_CENTER, 615,
                    390);
  }
  if (status == GAME_OVER) {
    logoGameOver->Draw();

    if (menuButtons[1].buttonSelectState)
      buttonTryagainDeselect->Draw();
    else
      buttonTryagainSelect->Draw();

    if (menuButtons[0].buttonSelectState)
      buttonExitSelect->Draw();
    else
      buttonExitDeselect->Draw();
  }
}
