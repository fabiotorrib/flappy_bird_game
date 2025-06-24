#include "../include/motion.hpp"
#include <allegro5/allegro_primitives.h>
#include <memory>
#include "../include/defines.hpp"
#include "../include/init.hpp"
#include "assets.hpp"

// Inicializa as imagens do motion
Motion::Motion() {
  background_rain = std::make_unique<Image>("assets/background_rain.png");
  drips1 = std::make_unique<Image>("assets/Drips.png");
  drips2 = std::make_unique<Image>("assets/Drips.png");
  thunder = std::make_unique<Image>("assets/Thunder.png");
  thunder1 = std::make_unique<Image>("assets/Thunder1.png");

  background_snow = std::make_unique<Image>("assets/background_snow.png");
  flakesLittle = std::make_unique<Image>("assets/flakesLittle.png");
  flakesLittle2 = std::make_unique<Image>("assets/flakesLittle.png");
  flakesBig = std::make_unique<Image>("assets/flakesBig.png");

  background = std::make_unique<Image>("assets/background.png");
  lights = std::make_unique<Image>("assets/LightStrip.png");
  clouds = std::make_unique<Image>("assets/Clouds.png");
  clouds2 = std::make_unique<Image>("assets/Clouds.png");
  little = std::make_unique<Image>("assets/Frame1.png");
  little2 = std::make_unique<Image>("assets/Frame2.png");
  little3 = std::make_unique<Image>("assets/Frame3.png");
  bird1 = std::make_unique<Image>("assets/B1.png");
  bird2 = std::make_unique<Image>("assets/B2.png");
  bird3 = std::make_unique<Image>("assets/B3.png");
  ground = std::make_unique<Image>("assets/Ground.png");
  ground2 = std::make_unique<Image>("assets/Ground.png");
}

// Variavel que muda o estado do clima de fundo
void Motion::setController(int x) {
  controller = x;
}

// Animação de todos sprites da tela de fundo
void Motion::update() {

  // Exceção
  if(!(controller == 1 || controller == 2 || controller == 3)){
    controller = 1;
    std::cerr << "Valor invalido setado no controller!" << std::endl;
  }

  // Atualiza a posição do clima ensolarado
  if (controller == 1) {
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
      cont = 0;
      positionB_x = 0;
    }

    if (positionF_x >= 2560) {
      positionF_x = 0;
    }

    if (positionF2_x >= 2560) {
      positionF2_x = 0;
    }
  }

  // Atualiza a posição da neve
  if (controller == 2) {
    // Atualiza a posição a cada frame
    positionF = positionF + speedFlakes;

    positionF2 = positionF2 + speedFlakes2;

    positionF3 = positionF3 + speedFlakes;

    // If's que resetam a posição da animação quando ela sai da tela
    if (positionF >= 2000) {
      positionF = 550;
    }

    if (positionF2 >= 2000) {
      positionF2 = 550;
    }

    if (positionF3 >= 2000) {
      positionF3 = 550;
    }
  }
  // Atualiza posição chuva
  if (controller == 3) {
    contF++;
    positionR1 += speedRain;

    positionR2 += speedRain;

    if (positionR1 >= 2000) {
      positionR1 = 500;
    }

    if (positionR2 >= 2000) {
      positionR2 = 500;
    }
  }
}

// Redesenhando cada imagem com a nova posição
void Motion::draw() {

  // Desenha animação ensolarada
  if (controller == 1) {

    background->Draw(0, 0);

    //Correção caso a posição do little bird ultrapasse o contador
    if(positionB_x > cont){
      cont = positionB_x + 5;
    }
    // Animação dos passaros do fundo batendo as asas
    if ((positionB_x <= cont) && (value == 0)) {
      little->Draw(positionB_x - 1280, 0);

      if (positionB_x == cont) {
        cont = cont + 9;
        value++;
      }

    } else if ((positionB_x <= cont) && (value == 1)) {
      little2->Draw(positionB_x - 1280, 2);
      if (positionB_x == cont) {
        cont = cont + 9;
        value++;
      }
    } else if ((positionB_x <= cont) && (value == 2)) {
      little3->Draw(positionB_x - 1280, 4);

      if (positionB_x == cont) {
        cont = cont + 9;
        value = 0;
      }
    }
    // Desenhando as nuvens, chão e o feixe de luz
    clouds2->Draw(positionCC_x - 1280, 0);
    clouds->Draw(positionC_x - 1280, 0);
    ground->Draw(positionF_x - 1280, 0);
    ground2->Draw(positionF2_x - 1280, 0);
    lights->Draw(positionL_x + 1280, -20);
  }
  // Desenha a animção da neve
  if (controller == 2) {
    background_snow->Draw(0, 0);
    flakesLittle->Draw(0, positionF - 1280);
    flakesLittle2->Draw(0, positionF3 - 1280);
    flakesBig->Draw(0, positionF2 - 1280);
  }
  // Desenha a animação da chuva
  if (controller == 3) {
    background_rain->Draw(0, 0);

    if ((contF <= contB + 20) && (contF >= contB) && (controll == 0)) {
      thunder->Draw(0, 0);

      if (contF == contB + 20) {
        controll = 1;
        contB += 50;
      }
    }

    if ((contF <= contB + 20) && (contF >= contB) && (controll == 1)) {
      thunder1->Draw(0, 0);

      if (contF == contB + 20) {
        controll = 0;
        contB += 1000;
      }
    }

    //Desenha os pingos de chuva
    drips1->Draw(0, positionR1 - 1280);
    drips2->Draw(0, positionR2 - 1280);
  }
}