#pragma once

#include "bird.hpp"
#include "defines.hpp"
#include "game_object.hpp"
#include "init.hpp"
#include "pipe.hpp"
#include "player.hpp"  // Adicione o include para a classe Player

class FlappyBird {
 private:
  Bird bird;
  std::vector<Pipe> pipes;
  int score;
  std::unique_ptr<Player>
      currentPlayer;  // TROCADO: de std::optional para std::unique_ptr

 public:
  // Construtor
  FlappyBird(float width = 1200, float height = 800)
      : bird((float)SCREEN_W / 3, (float)SCREEN_H / 2),
        score(0),
        currentPlayer(nullptr) {  // TROCADO: inicializa com nullptr
    (void)width;                  // Silencia avisos de variável não usada
    (void)height;
  }

  // Métodos principais
  void update();
  void jump();
  void reset();
  void setPlayerName(const std::string& name);
  void saveCurrentPlayerScore();

  // Getters para a interface
  const Bird& get_bird() const {
    return bird;
  };
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
