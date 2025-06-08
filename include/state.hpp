#pragma once

#include "defines.hpp"
#include "init.hpp"
#include "libs.hpp"
class FlappyBird;

class State {
 public:
  virtual ~State() = default;

  // essa sera a funcao em que sera implementada a logica de cada estado
  virtual State* loop(FlappyBird* game = nullptr) = 0;
  // usada para associar ao display criado no init()
  static void setGlobals(ALLEGRO_DISPLAY* d, ALLEGRO_EVENT_QUEUE* q);

 protected:
  // essas variaveis podem ser acessadas por qualquer filha
  static ALLEGRO_DISPLAY* display;
  static ALLEGRO_EVENT_QUEUE* queue;
  static ALLEGRO_EVENT ev;
};
