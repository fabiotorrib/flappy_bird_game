#pragma once

#include <allegro5/allegro_primitives.h>
#include "defines.hpp"
#include "game_object.hpp"

class Bird : public GameObject {
 private:
  float gravity;
  float jumpForce;
  float vy = 0;
  float rotation = 0;
  float valueB = 0;
  float contB = TIME_GIF_BIRD;
  float frames = 0;
  ALLEGRO_BITMAP* frame2;
  ALLEGRO_BITMAP* frame3;
  bool breakanimation = false;

 public:
  Bird(ALLEGRO_BITMAP* img, float x, float y, ALLEGRO_BITMAP* img2,
       ALLEGRO_BITMAP* img3)
      : GameObject(img, x, y, al_get_bitmap_width(img),
                   al_get_bitmap_height(img)),
        gravity(GRAVITY),
        jumpForce(JUMP_FORCE),
        frame2(img2),
        frame3(img3) {
  }

  ~Bird() = default;

  void update();
  void draw() override;

  void jump();
  void loop_animation(int type);
  bool check_bird_collision(const GameObject& other) const;
  void destroy_bitmaps();
  void set_by();
  void set_break(bool value);
  void reset_xy();
};
