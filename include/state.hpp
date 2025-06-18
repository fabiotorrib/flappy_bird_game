#pragma once
#include <allegro5/allegro.h>
#include "defines.hpp"
#include "motion.hpp"

class State {
 public:
  virtual ~State() = default;

  // essa sera a funcao em que sera implementada a logica de cada estado
  virtual void draw(Motion& motion) = 0;
  virtual State* update(Motion& motion) = 0;
  virtual State* handle_input(const ALLEGRO_EVENT& ev) = 0;
  virtual void enter() = 0;
  // usada para associar ao display criado no init()
  static void setGlobals(ALLEGRO_DISPLAY* d, ALLEGRO_EVENT_QUEUE* q);

 protected:
  // essas variaveis podem ser acessadas por qualquer filha
  static ALLEGRO_DISPLAY* display;
  static ALLEGRO_EVENT_QUEUE* queue;
  static ALLEGRO_EVENT ev;
};
