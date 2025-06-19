#include "../../include/states/play.hpp"
#include "../../include/states/main_menu.hpp"  // Para 'new MainMenu()'

Play::Play(){
  logoGameOver = std::make_unique<Image>("assets/logoGameOver.png", 0, -200);
  buttonTryagainSelect = std::make_unique<Image>("assets/buttonTryagainSelect.png", 496.5, 390);
  buttonTryagainDeselect = std::make_unique<Image>("assets/buttonTryagainDeselect.png", 496.5, 390);
  buttonExitSelect = std::make_unique<Image>("assets/buttonExitSelect.png", 496.5, 490);
  buttonExitDeselect = std::make_unique<Image>("assets/buttonExitDeselect.png", 496.5, 490);
  buttonPause = std::make_unique<Image>("assets/buttonPause.png", 40, 0);
  font = std::make_unique<TextFont>("assets/TextFont.ttf", 40);
  font->setColor(255,255,255);
}

void Play::enter() {
  // Este código é chamado toda vez que o jogo começa.
  // Garante que cada partida seja nova e limpa.
  flappy = std::make_unique<FlappyBird>();
  flappy->reset();
  flappy->set_current_player(player);
  status = ScreenState::PLAY;  // Reseta o status interno para "jogando"
}

// O método agora usa o membro 'flappy' da própria classe.
State* Play::handle_input(const ALLEGRO_EVENT& ev) {
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
    switch (status) {
      case ScreenState::PLAY:
        if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
          flappy->get_state() == 0 ? flappy->starter() : flappy->jump();
        } else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
          status = ScreenState::PAUSE;
          flappy->breaker();
        }
        break;

      case ScreenState::PAUSE:
        if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
          status = ScreenState::PLAY;
          flappy->unbreaker();
        }else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
          return new MainMenu();
        }
        break;

      case ScreenState::GAME_OVER:
        if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
        ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {

          if (menuButtons[buttonPositionSelected].name == "TryAgain") {
          std::cerr << "Botão TryAgain selecionado!" << std::endl;
          status = ScreenState::PLAY;
          flappy->reset();
          } else if (menuButtons[buttonPositionSelected].name == "Exit") {
          std::cerr << "Botão Exit selecionado!" << std::endl;
          for (auto& button : menuButtons) {
          button.buttonSelectState = 0;
          }
          buttonPositionSelected = 0;
          menuButtons[buttonPositionSelected].buttonSelectState = 1;
          return new MainMenu();
          }

        } else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
          flappy->reset();
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

State* Play::update(Motion& motion) {
  // A lógica do jogo só avança se o status interno for PLAY.
  if (status == ScreenState::PLAY) {
    flappy->update();
    flappy->control_pipes();
    flappy->update_score();
    flappy->change_velocity();

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

void Play::draw(Motion& motion) {
  motion.draw();
  flappy->draw();

  if (status == PAUSE) {
    buttonPause->Draw();
    font->writeText("Press Esc to back to Main Menu.",ALLEGRO_ALIGN_CENTER, 615, 340);
    font->writeText("Press Space to resume playing.",ALLEGRO_ALIGN_CENTER, 615, 390);
    // Desenhe aqui a tela de pause
    // para liberar o jogo basta mudar o status para PLAY e puxar a função
    // flappy->unbreak(); de um tempo até soltar o unbreak
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

    // desenhe aqui a tela do game over
    // se tiver botao de retry, muda o status para PLAY e chama flappy->reset();
    // se for trocar de state(voltar para o menu) tbm de um reset
  }
}
