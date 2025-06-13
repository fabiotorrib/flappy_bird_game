#pragma once

#include "bird.hpp"
#include "defines.hpp"
#include "game_object.hpp"
#include "libs.hpp"
#include "pipe.hpp"

class FlappyBird {
 private:
  Bird bird;
  std::vector<Pipe> pipes;
  int score;

 public:
  // Use a lista de inicialização para construir o objeto 'bird'
  FlappyBird(float width = 1200, float height = 800)
      : bird((float)SCREEN_W / 3, (float)SCREEN_H / 2), score(0) {
    // O corpo do construtor agora pode ficar vazio
  }

  // Métodos principais
  void update();
  void jump();
  void reset();
  void setPlayerName(const std::string& name);

  // Getters para a interface
  const Bird& get_bird() const {
    return bird;
  }
  const std::vector<Pipe>& get_pipes() const {
    return pipes;
  }
  int get_score() {
    return score;
  }

  // Checagem de colisões
  bool check_bird_collision(const GameObject& other) const;
  bool check_collision_with_boundaries() const;
  void spawn_pipe();
  void update_score();
};
