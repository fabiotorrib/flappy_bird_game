#pragma once

#include "defines.hpp"
#include "game_object.hpp"
#include "libs.hpp"

class Bird : public GameObject {
 private:
  float rotation;

 public:
  Bird(float x = 0, float y = 0) : GameObject(x, y, 34, 24), rotation(0) {
  }

  ~Bird() = default;

  void update();
  float get_rotation() const;
};
