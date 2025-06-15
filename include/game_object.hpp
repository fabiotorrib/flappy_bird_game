#pragma once

#include "init.hpp"

class GameObject {
   protected:
    ALLEGRO_BITMAP* obj_sprite;
    float x, y;
    float by;
    float width, height;
    float y_final,x_final;

   public:
    GameObject(ALLEGRO_BITMAP* img, float x, float y, float width, float height)
        : obj_sprite(img), x(x), y(y), width(width), height(height) {}

    virtual void update() = 0;
    virtual void draw() = 0;
    bool check_bird_collision(const GameObject& other) const;
    bool check_collision_with_boundaries() const;
    void set_x(float new_x);
    void set_y(float new_y);
    float get_x();
    float get_y();
    void set_finals();
    float get_x_final();

    virtual ~GameObject() {}
};
