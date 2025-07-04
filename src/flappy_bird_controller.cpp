/**
 * @file flappy_bird_controller.cpp
 * @brief Controlador de fluxo do jogo (pontuação, eventos globais).
 */

#include "../include/flappy_bird_controller.hpp"
#include <allegro5/bitmap_draw.h>
#include <iostream>
#include "../include/bird.hpp"

//contrutor
FlappyBird::FlappyBird()
    : bird1 (std::make_unique<Image>("assets/B1.png")),
      bird2 (std::make_unique<Image>("assets/B2.png")),
      bird3 (std::make_unique<Image>("assets/B3.png")),
      pipe  (std::make_unique<Image>("assets/PipeWithBottom.png")),
      ground(std::make_unique<Image>("assets/Ground.png")),
      ground2(std::make_unique<Image>("assets/Ground.png")),
      pointSound   (std::make_unique<Sound>("assets/Score.ogg")),
      gameOverSound(std::make_unique<Sound>("assets/GameOver.ogg")),
      flappy_obj(bird1->getBitmap(), -100, 200,
                 bird2->getBitmap(), bird3->getBitmap()),
      pipelist(pipe->getBitmap()) {}


// funcao de desenhar as coisas
/**
 * @brief Desenha todos os elementos do jogo de acordo com o estado atual.
 */
void FlappyBird::draw() {
  // A animação do chão e das nuvens agora acontece em todos os estados

  switch (state) {
    case 0:  // Animação de Entrada
      flappy_obj.draw();
      break;
    case 1:  // Aguardando Input
      flappy_obj.draw();
      draw_intial_text();  // Mostra "PRESS SPACE"
      break;
    case 2:  // Jogando
      flappy_obj.draw();
      pipelist.draw();
      draw_HUD();
      break;
  }
  draw_animated_ground(
      state == 2 ? velocity : BIRD_VEL);  // Chão se move mais devagar na intro
}

/**
 * @brief Atualiza lógica do jogo segundo o estado e aplica física.
 */
void FlappyBird::update() {
  switch (state) {
    case 0:                 // Animação de Entrada
      flappy_obj.update();  // Isso vai mover o pássaro até X_INIT
      if (flappy_obj.get_x() >= X_INIT) {
        state = 1;  // Pássaro chegou, agora vamos aguardar o input
      }
      break;

    case 1:  // Aguardando Input
      // Não faz nada, o pássaro fica parado esperando o starter()
      break;

    case 2:                 // Jogando
      flappy_obj.update();  // Agora a gravidade se aplica

      // Lógica do jogo que só acontece quando está jogando
      pipelist.set_start();
      pipelist.set_vx(velocity);
      pipelist.update();
      control_pipes();
      update_score();
      change_velocity();
      break;
  }
}

/**
 * @brief Reinicia variáveis, pontos e objetos para começar uma nova partida.
 */
void FlappyBird::reset() {
  state = 0;
  time = 0;
  velocity = PIPE_SPEED;
  velocity_backup = 0;
  score = 0;
  positionF_x = 0;
  positionF2_x = SCREEN_W;
  change_vel = 5;
  flappy_obj.reset_xy();
  flappy_obj.set_break(false);
  pipelist.set_difficulty(difficulty_game);
  pipelist.reset();
}

// PLAYER
/**
 * @brief Define o jogador que receberá pontuação ao final da partida.
 */
void FlappyBird::set_current_player(Player& player) {
  currentPlayer = &player;
}
/**
 * @brief Copia a pontuação atual do jogo para o objeto Player.
 */
void FlappyBird::set_playerscore() {
  currentPlayer->SetScore(score);
}

/**
 * @brief Salva o placar do jogador corrente no arquivo de ranking.
 */
void FlappyBird::saveCurrentPlayerScore() {
  currentPlayer->SaveLeaderboard("Leaderboard.txt", ranking, *currentPlayer);
}

// funcao checa colisoes
/**
 * @brief Verifica colisões do pássaro com canos ou limites da tela.
 * @return true se ocorrer colisão.
 */
bool FlappyBird::check_collisions() {
  if ((flappy_obj.check_collision_with_boundaries() && velocity != 0) ||
      (pipelist.check_collision(flappy_obj))) {
    gameOverSound->playSound(1.0);
    velocity = 0;
    flappy_obj.set_break(true);
    return true;
  }
  return false;
}

// ACTIONS

/**
 * @brief Solicita pulo do pássaro se o jogo estiver em andamento.
 */
void FlappyBird::jump() {
  if (velocity != 0 && state == 2) {
    flappy_obj.jump();
  }
}

/**
 * @brief Inicia a partida a partir do estado de espera.
 */
void FlappyBird::starter() {
  // starter() agora transita do estado 1 (Aguardando) para o 2 (Jogando)
  if (state == 1) {
    state = 2;
    flappy_obj.jump();
  }
}

/**
 * @brief Gerencia criação e remoção de canos na tela.
 */
void FlappyBird::control_pipes() {
  pipelist.add_pipe_pair();
  pipelist.delete_pipe_pair();
}

/**
 * @brief Desenha o texto piscante "PRESS SPACE TO PLAY".
 */
void FlappyBird::draw_intial_text() {
  time += 1.0 / FPS;
  float alpha = 0.5f + 0.5f * sinf(OSCILATION * time);
  ALLEGRO_COLOR cor = al_map_rgba_f(1, 1, 1, alpha);
  al_draw_text(font, cor, SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTRE,
               "PRESS SPACE TO PLAY");
}

/**
 * @brief Atualiza contagem de pontos e toca som quando necessário.
 */
void FlappyBird::update_score() {
  if(pipelist.check_score(flappy_obj.get_x())){
    pointSound->playSound(0.3);
  };
  score = pipelist.get_points();
}

/**
 * @brief Aumenta gradualmente a velocidade dos canos conforme pontuação.
 */
void FlappyBird::change_velocity() {
  if (difficulty_game != 0){
    if (score % change_vel == 0 && score != 0) {
      velocity += 0.25;
      change_vel += 2;
    }
  }
}

/**
 * @brief Desenha a pontuação atual na tela.
 */
void FlappyBird::draw_HUD() {
  al_draw_textf(font, al_map_rgb(255, 255, 255), 60, 30, ALLEGRO_ALIGN_CENTRE,
                "%d", score);
}

/**
 * @brief Desenha o chão em rolagem contínua para efeito de movimento.
 * @param velocity Velocidade de deslocamento.
 */
void FlappyBird::draw_animated_ground(float velocity) {
  positionF_x -= velocity;
  positionF2_x -= velocity;

  if (positionF_x <= -1280) {
    positionF_x = 0;
  }

  if (positionF2_x <= 0) {
    positionF2_x = 1280;
  }

  ground->Draw(positionF_x, 0);
  ground2->Draw(positionF2_x, 0);
}

/**
 * @brief Pausa o movimento (usado em menus).
 */
void FlappyBird::breaker() {
  velocity_backup = velocity;
  velocity = 0;
  flappy_obj.set_break(true);
}

/**
 * @brief Restaura o movimento após pausa.
 */
void FlappyBird::unbreaker() {
  velocity = velocity_backup;
  flappy_obj.set_break(false);
}

// AUXILIARES

/**
 * @brief Retorna o estado interno atual.
 */
int FlappyBird::get_state() {
  return state;
}
