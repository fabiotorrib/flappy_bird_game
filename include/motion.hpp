#pragma once
#include <allegro5/allegro_primitives.h>
#include "assets.hpp"
#include "defines.hpp"

//Classe que faz os efeitos de parallax e animações de cenário

class Motion {
  // Posição e velocidade de cada imagem
 private:
  int controller = 1;

  float controll = 0;
  float contF = 0;
  float contB = 400;
  
  float speedRain = 6;
  float positionR1 = 400;
  float positionR2 = -320;

  float speedFlakes = 1.0;
  float positionF = 500;
  float positionF2 = 550;
  float positionF3 = -210;
  float speedFlakes2 = 0.4;

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

  std::unique_ptr<Image> background_rain;
  std::unique_ptr<Image> drips1;
  std::unique_ptr<Image> drips2;
  std::unique_ptr<Image> thunder;
  std::unique_ptr<Image> thunder1;
  std::unique_ptr<Image> background_snow;
  std::unique_ptr<Image> flakesLittle;
  std::unique_ptr<Image> flakesLittle2;
  std::unique_ptr<Image> flakesBig;
  std::unique_ptr<Image> background;
  std::unique_ptr<Image> lights;
  std::unique_ptr<Image> clouds;
  std::unique_ptr<Image> clouds2;
  std::unique_ptr<Image> little;
  std::unique_ptr<Image> little2;
  std::unique_ptr<Image> little3;
  std::unique_ptr<Image> bird1;
  std::unique_ptr<Image> bird2;
  std::unique_ptr<Image> bird3;
  std::unique_ptr<Image> ground;
  std::unique_ptr<Image> ground2;

 public:
  // Metodos para desenhar e atualiza a posição da imagem
  void draw();
  void update();

  Motion();

  void setController(int);
};