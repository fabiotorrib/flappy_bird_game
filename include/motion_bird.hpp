#pragma once

#include "init.hpp"
#include "defines.hpp"
#include <allegro5/allegro_primitives.h>

class MotionBird {

    private:

    //Variavel que vai definir qual if deverá rodar dentro do ciclo da animção
    float valueB = 0;

    //Contador que manterá animação acontecendo frame a frame
    //E delimita quantos frames cada if ficará rodando
    float contB = 8;

    float position_x = 0;
    float position_y = 0;
    float frames = 0;

    public:
    void loop();

    void setterX(float);
    void setterY(float);

};