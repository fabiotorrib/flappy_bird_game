#pragma once

#include "GameObject.hpp"

class Pipe : public GameObject {
private:
    float vx;
    float gap_size;
    bool scored;

public:
    Pipe(ALLEGRO_BITMAP* img, float x, float y)
        : GameObject(img, x, y, al_get_bitmap_width(img), al_get_bitmap_height(img)),
          vx(PIPE_SPEED), gap_size(GAP_SIZE), scored(false) {}

    void update();
    void draw() const override;
    bool is_off_screen() const;
    bool check_score(float bird_x);
};