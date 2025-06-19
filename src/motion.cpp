#include "../include/motion.hpp"
#include <allegro5/allegro_primitives.h>
#include "../include/defines.hpp"
#include "../include/init.hpp"

// Animação de todos sprites da tela de fundo
void Motion::update() {

  // Altera a posição do feixe de luz
  positionL_x = positionL_x - speed_light;

  // Altera a posição das nuvens
  positionC_x = positionC_x + speed_cloud;
  positionCC_x = positionCC_x + speed_cloud;

  // Altera a posição dos pequenos passaros
  positionB_x = positionB_x + speed_little;

  // Altera a posição do chão
  positionF_x = positionF_x + speed_floor;
  positionF2_x = positionF2_x + speed_floor;

  // Reinicia a posição de cada imagem quando ela sai da tela
  if (positionL_x <= -2560) {
    positionL_x = 0;
  }

  if (positionC_x >= 2560) {
    positionC_x = 0;
  }

  if (positionCC_x >= 2560) {
    positionCC_x = 0;
  }

  if (positionB_x >= 2560) {
    positionB_x = 0;
  }

  if (positionF_x >= 2560) {
    positionF_x = 0;
  }

  if (positionF2_x >= 2560) {
    positionF2_x = 0;
  }

}
// Atualiza a tela com os frames andados
void Motion::draw() {

  // Redesenhando cada imagem com a nova posição
  al_draw_bitmap(background, 0, 0, 0);

  // Animação dos passaros do fundo batendo as asas
  // Mesma logica do Bird que bate as asas
  if ((positionB_x <= cont) && (value == 0)) {
    al_draw_bitmap(little, (positionB_x - 1280), 0, 0);

    if (positionB_x == cont) {
      cont = cont + 9;
      value++;
    }

  } else if ((positionB_x <= cont) && (value == 1)) {
    al_draw_bitmap(little2, (positionB_x - 1280), 2, 0);
    if (positionB_x == cont) {
      cont = cont + 9;
      value++;
    }
  } else if ((positionB_x <= cont) && (value == 2)) {
    al_draw_bitmap(little3, (positionB_x - 1280), 4, 0);

    if (positionB_x == cont) {
      cont = cont + 9;
      value = 0;
    }
  }

  al_draw_bitmap(clouds2, (positionCC_x - 1280), 0, 0);
  al_draw_bitmap(clouds, (positionC_x - 1280), 0, 0);
  al_draw_bitmap(ground, (positionF_x - 1280), 0, 0);
  al_draw_bitmap(ground2, (positionF2_x - 1280), 0, 0);
  al_draw_bitmap(lights, (positionL_x + 1280), -20, 0);
}

//Metodo que muda o clima para neve, mudando o background e fazendo nevar na tela
void Motion::snow_update(){

    //Atualiza a posição a cada frame
    positionF = positionF + speedFlakes;

    positionF2 = positionF2 + speedFlakes2;

    positionF3 = positionF3 + speedFlakes;

    //If's que resetam a posição da animação quando ela sai da tela
    if(positionF >= 2000 ){

        positionF = 550;
    }

    if(positionF2 >= 2000){

        positionF2 = 550;
    }

    if(positionF3 >= 2000){

        positionF3 = 550;
    }

}

//Método que atualiza a posição de cada desenho
void Motion::snow_draw(){

    al_draw_bitmap(background_snow, 0, 0, 0);
    al_draw_bitmap(flakesLittle, 0, positionF - 1280, 0);
    al_draw_bitmap(flakesLittle2, 0, positionF3 - 1280, 0);
    al_draw_bitmap(flakesBig, 0, positionF2 - 1280, 0);
}