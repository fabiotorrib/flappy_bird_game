#pragma once

#include "defines.hpp"
#include "game_object.hpp"
#include "defines.hpp"
#include "init.hpp"
#include <allegro5/bitmap.h>
#include <vector>
#include <random>

class Pipe : public GameObject {
private:
    float vx = 0;
    bool scored;

public:
    Pipe(ALLEGRO_BITMAP* img, float x, float y)
        : GameObject(img, x, y, al_get_bitmap_width(img), al_get_bitmap_height(img)),
          vx(PIPE_SPEED), scored(false) {set_finals();}

    void update() override;
    void draw() override;
    bool is_off_screen() const;
    bool check_score(float bird_x);
    void set_vx(float vel);
};

class PipePair{
    public:
        Pipe bottom;
        Pipe top;
        
        PipePair(ALLEGRO_BITMAP* img,float x, float y):bottom(img,x,y),top(img,x,y-al_get_bitmap_height(img)-GAP_SIZE){}
};


class PipeList {
private:
    std::vector<PipePair> Pipes;
    bool start = false;
    int points;
    inline static std::mt19937 gen{ std::random_device{}() };
public:
    void draw();
    void set_vx(float vel);
    void update();
    void add_pipe_pair();
    void delete_pipe_pair();
    bool check_collision(GameObject& bird);
    bool check_score(float bird_x);
    bool set_start();
    int get_points();
    void reset();

};