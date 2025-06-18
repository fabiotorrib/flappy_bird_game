#pragma once

#include "flappy_bird_controller.hpp"
#include "init.hpp"
#include "state.hpp"

class AllegroController {
 private:
  int screen_width;
  int screen_height;

  std::unique_ptr<State> current_state;
  std::unique_ptr<Motion> motion;
  FlappyBird game;

 public:
  AllegroController(float screen_w, float screen_h);
  ~AllegroController();

  bool initialize();
  bool load();
  void cleanup();

  // Métodos de renderização
  void run();
};