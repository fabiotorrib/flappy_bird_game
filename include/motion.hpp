#pragma once
#include <allegro5/allegro_primitives.h>
#include "defines.hpp"

class Motion {
  // Posição e velocidade de cada imagem
 private:
  bool remake;
  float positionL_x = 0;
  float speed_light = 0.5;

  float positionC_x = 0;
  float positionCC_x = -1280;
  float speed_cloud = 0.6;

  float positionB_x = 0;
  float speed_little = 1;
  float cont = 16;
  float value = 0;

  float positionF_x = 1280;
  float positionF2_x = 0;
  float speed_floor = 2.5;

 public:
  void draw();
  void update();
};