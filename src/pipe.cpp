#include "../include/pipe.hpp"

void Pipe::update(){
    x+=vx;
}

void Pipe::draw() const{
    al_draw_scaled_bitmap(obj_sprite,0, 0,width, height,x, y,width, -y,0);
    al_draw_scaled_bitmap(obj_sprite,0, 0,width, height,x, y + gap_size ,width, SCREEN_H-y-gap_size,0);
}

//para quem implementar a geracao dos pipes esse metodo pode ser usado para deletar pipes fora da tela
bool Pipe::is_off_screen() const {
    return x + width < 0;
}

//checa se o bird passou por essa instancia
bool Pipe::check_score(float bird_x) {
    if (!scored && bird_x > x + width) {
        scored = true;
        return true;
    }
    return false;
}
