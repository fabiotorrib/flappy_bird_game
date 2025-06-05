#pragma once

#include "GameObject.hpp"

class Bird : public GameObject {
private:
    float gravity;
    float jumpForce;
    float vy = 0;
public:
    Bird(ALLEGRO_BITMAP* img,float x, float y) 
        : GameObject(img, x, y, al_get_bitmap_width(img), al_get_bitmap_height(img)), gravity(GRAVITY) , jumpForce(JUMP_FORCE) {} 

    ~Bird() = default;

    void update();
    void draw() const override;

    void jump();

    void destroy_bitmaps();
};

