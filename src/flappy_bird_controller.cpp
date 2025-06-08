#include "flappy_bird_controller.hpp"

void FlappyBird::update() {
  bird.update();

  // Atualiza pipes e remove os que saíram da tela
  for (auto it = pipes.begin(); it != pipes.end();) {
    it->update();
    if (it->is_off_screen()) {
      it = pipes.erase(it);
    } else {
      ++it;
    }
  }
}

void FlappyBird::jump() {
  bird.set_vy(JUMP_FORCE);
}

void FlappyBird::reset() {
  // Reseta o bird para posição inicial
  bird.set_x(SCREEN_W / 3);
  bird.set_y(SCREEN_H / 2);
  bird.set_vy(0);

  // Limpa todos os pipes
  pipes.clear();
}

void FlappyBird::setPlayerName(const std::string& name) {
  // Implementar lógica de nome do jogador nn sei como vai ser isso ainda
}

bool FlappyBird::check_bird_collision(const GameObject& other) const {
  // Verifica se a coordenada horizontal do meio do bird está dentro da largura
  // do pipe
  bool is_inside_other_horizontal =
      (bird.get_x() + bird.get_width() / 2.0f >= other.get_x()) &&
      (bird.get_x() + bird.get_width() / 2.0f <=
       other.get_x() + other.get_width());

  // Verifica colisão com a parte superior ou inferior do pipe
  if (is_inside_other_horizontal &&
      ((bird.get_y() <= other.get_y()) ||
       (bird.get_y() + bird.get_height() >= other.get_y() + GAP_SIZE))) {
    return true;  // Há colisão
  }
  return false;  // Não há colisão
}

bool FlappyBird::check_collision_with_boundaries() const {
  // Verifica colisão com o teto
  if (bird.get_y() <= 0) {
    return true;
  }
  // Verifica colisão com o chão
  if (bird.get_y() + bird.get_height() >= SCREEN_H) {
    return true;
  }
  return false;  // Não há colisão com os limites
}

void FlappyBird::spawn_pipe() {
  // Cria um novo pipe na borda direita da tela
  Pipe p(SCREEN_W, 100 + rand() % (SCREEN_H - MIN_PIPE_H));
  p.set_vx(PIPE_SPEED);  // Define a velocidade do pipe
  pipes.push_back(p);
  std::cout << "INFO: Cano gerado na posicao x=" << p.get_x()
            << ", y=" << p.get_y() << std::endl;
}

void FlappyBird::update_score() {
  // Implementar lógica de score se necessário
  for (auto& pipe : pipes) {
    if (pipe.check_score(bird.get_x())) {
      // Incrementar score aqui
    }
  }
}