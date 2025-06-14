#pragma once

#include "defines.hpp"
#include "game_object.hpp"
#include "init.hpp"

class Bird : public GameObject {
 private:
  float rotation;

 public:
  Bird(float x = 0, float y = 0) : GameObject(x, y, 59, 63), rotation(0) {
  }

  ~Bird() = default;

  void update();
  float get_rotation() const;
};