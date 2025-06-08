#pragma once
#include "flappy_bird_controller.hpp"
#include "init.hpp"
#include "state.hpp"

class Play : public State {
 public:
  State* loop(FlappyBird* game);
  // a funcao reset e utilizada ao iniciar uma nova partida
  void reset();
};