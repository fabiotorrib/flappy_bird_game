#pragma once

#include "init.hpp"

class GameObject {
protected:
    ALLEGRO_BITMAP* obj_sprite;
    float x, y;
    float width, height;
public:
    GameObject(ALLEGRO_BITMAP* img,float x, float y, float width, float height)
        : obj_sprite(img), x(x), y(y), width(width), height(height) {}

    virtual void update() = 0;
    virtual void draw() const = 0;
    bool checkcollision(const GameObject& other);
    void set_x(float new_x);
    void set_y(float new_y);
    float get_x();
    float get_y();

    virtual ~GameObject() {}
};


