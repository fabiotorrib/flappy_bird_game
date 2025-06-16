#pragma once

#include "bird.hpp"
#include "defines.hpp"
#include "game_object.hpp"
#include "init.hpp"
#include "pipe.hpp"
#include "player.hpp"

class FlappyBird {
 private:
  Bird flappy_obj;
  PipeList pipelist;
  int state = 0;
  float time = 0;
  float velocity = PIPE_SPEED;
  float velocity_backup = 0;
  int score = 0;
  float positionF_x = 0;
  float positionF2_x = SCREEN_W;
  int change_vel = 2;
  Player *currentPlayer = nullptr;  // TROCADO: de std::optional para std::unique_ptr

 public:
  // Construtor
  FlappyBird(): flappy_obj(bird1, -100, 200,bird2, bird3),pipelist(){}

  // Métodos principais
  void draw();
  void update();
  void reset();
  void set_current_player(Player& player);
  void saveCurrentPlayerScore();
  bool check_collisions();


  //actions
  void jump();
  void starter();
  void control_pipes();
  void draw_intial_text();
  void update_score();
  void change_velocity();
  void draw_HUD();
  void draw_animated_ground(float velocity);
  void breaker();
  void unbreaker();

  //auxiliares
  int get_state();
  void set_playerscore();



  // Getters para a interface
  const Bird& get_bird() const {
    return flappy_obj;
  }
  const PipeList& get_pipes() const {
    return pipelist;
  }
};
