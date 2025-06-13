#include "../include/state.hpp"
#include "../include/defines.hpp"
#include <allegro5/allegro_primitives.h>
#include "../include/motion_bird.hpp"

//Set's para mudarem a posição do passaro animado
void MotionBird::setterX(float n){

    position_x = position_x + n;
}

void MotionBird::setterY(float n){

    position_y = position_y + n;
}

//Animação do passaro batendo as asas
void MotionBird::loop(){

    //Cicla os frames de 1 em 1 a cada repetição para atualizar na tela
    frames = frames + 1;

    //Mantem o Bird com asa para cima durante 8 frames
    //Troca o value quando for igual a 8 para mudar para proxima imagem
    if((frames <= contB) && (valueB == 0)){
            al_draw_bitmap(bird1, position_x, position_y, 0);

            if(frames == contB){
                contB = contB + 8;
                valueB++;
            }

        }
    
    //Troca a imagem para o Bird com asa no meio durante 8 frames
    if((frames <= contB) && (valueB == 1)){
        al_draw_bitmap(bird2, position_x, position_y + 2, 0);

        if(frames == contB){
            contB = contB + 8;
            valueB++;
        }
    }

    //Troca a imagem para o Bird com asa para baixo durante 8 frames
    if((frames <= contB) && (valueB == 2)){
        al_draw_bitmap(bird3, position_x, position_y + 4, 0);

        if(frames == contB){
            contB = contB + 8;
            valueB++;
        }
    }

    //Zera o value pra reiniciar o ciclo
    //Volta a imagem para o Bird com asa no meio para reiniciar o ciclo
    if((frames <= contB) && (valueB == 3)){
        al_draw_bitmap(bird2, position_x, position_y + 2, 0);

        if(frames == contB){
            contB = contB + 8;
            valueB = 0;
        }

    }
}
