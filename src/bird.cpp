#include "../include/bird.hpp"

void Bird::update(){
    y+=vy;
    vy+=gravity;
}

void Bird::draw() const{
    float rotation=vy*ROTATION;
    al_draw_rotated_bitmap(obj_sprite,width/2,height/2,x,y,rotation,0);
}

void Bird::jump(){
    vy=jumpForce;
}

void Bird::destroy_bitmaps() {
    if (obj_sprite) {
        al_destroy_bitmap(obj_sprite);
        obj_sprite = nullptr;
    }
}
