#include "../include/states/states.hpp"
#include "../include/init.hpp"
#include "../include/state.hpp"
#include "../include/defines.hpp"
#include <allegro5/allegro_primitives.h>
#include "../include/motion.hpp"

void Motion::loop()
{
    bool remake = false;

    // Altera a varivel da posição a cada frame e verifica se ela já está fora da tela e retorna pra posição inicial

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

        // Reinicia a posição
        if (positionL_x <= -2560)
        {
            positionL_x = 0;
        }

        if (positionC_x >= 2560)
        {

            positionC_x = 0;
        }

        if (positionCC_x >= 2560)
        {

            positionCC_x = 0;
        }

        if (positionB_x >= 2560)
        {

            positionB_x = 0;
        }

        if (positionF_x >= 2560){

            positionF_x = 0;
        }
        
        if (positionF2_x >= 2560){

            positionF2_x = 0;
        }

        remake = true;

    // Atualiza a tela com os frames andados
    if (remake == true)
    {

        remake = false;

        // Redesenhando cada imagem com a nova posição
        al_draw_bitmap(background, 0, 0, 0);
        al_draw_bitmap(little, (positionB_x - 1280), 0, 0);
        al_draw_bitmap(clouds2, (positionCC_x - 1280), 0, 0);
        al_draw_bitmap(clouds, (positionC_x - 1280), 0, 0);
        al_draw_bitmap(ground, (positionF_x - 1280), 0, 0);
        al_draw_bitmap(ground2, (positionF2_x - 1280), 0, 0);
        al_draw_bitmap(lights, (positionL_x + 1280), -20, 0);
        
    }
}