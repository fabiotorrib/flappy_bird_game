#include "../include/init.hpp"


void init(){
    
    al_init();

    //iniciando objetos
    al_init_primitives_addon();
    al_init_image_addon();

    //iniciando inputs
    al_install_mouse();
    al_install_keyboard();

}



void deinit(){








}