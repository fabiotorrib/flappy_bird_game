#include "../../include/states/play.hpp"
#include "../../include/states/main_menu.hpp"  // Para 'new MainMenu()'

//#include <iostream>

void Play::enter() {
  // Este código é chamado toda vez que o jogo começa.
  // Garante que cada partida seja nova e limpa.
  flappy = std::make_unique<FlappyBird>();
  flappy->reset();
  flappy->set_current_player(player);  // 'player' é a sua variável global
  status = ScreenState::PLAY;          // Reseta o status interno para "jogando"
}

// O método agora usa o membro 'flappy' da própria classe.
State* Play::handle_input(const ALLEGRO_EVENT& ev) {
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
    switch (status) {
      case ScreenState::PLAY:
        if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
          // Correto: usando o ponteiro 'flappy' que pertence à classe Play
          flappy->get_state() == 0 ? flappy->starter() : flappy->jump();
        } else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
          status = ScreenState::PAUSE;
          flappy->breaker();
        }
        break;

      case ScreenState::PAUSE:
        if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
          status = ScreenState::PLAY;
          flappy->unbreaker();
        }
        break;

      case ScreenState::GAME_OVER:
        if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
          // Para reiniciar, criamos uma instância completamente nova do estado
          // Play. O novo 'enter()' cuidará da inicialização.
          return new Play();
        } else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
          // Retorna um novo estado MainMenu para voltar ao menu.
          return new MainMenu();
        }
        break;
      default:
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
    // Correto: usando o ponteiro 'flappy' que pertence à classe.
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

  // O 'update' por si só nunca causa uma transição para outra tela.
  // Ele apenas atualiza o estado do mundo do jogo. Por isso,
  // sempre retorna 'this'.
  return this;
}

void Play::draw(Motion& motion) {
  motion.draw();
  flappy->draw();

  if (status == PAUSE) {
    // Desenhe aqui a tela de pause
    // para liberar o jogo basta mudar o status para PLAY e puxar a função
    // flappy->unbreak(); de um tempo até soltar o unbreak
  }
  if (status == GAME_OVER) {
    // desenhe aqui a tela do game over
    // se tiver botao de retry, muda o status para PLAY e chama flappy->reset();
    // se for trocar de state(voltar para o menu) tbm de um reset
  }
}
