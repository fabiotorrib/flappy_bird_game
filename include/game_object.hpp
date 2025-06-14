#pragma once

#include "init.hpp"

class GameObject {
 protected:
  float x, y;
  float vx, vy;
  float width, height;

 public:
  GameObject(float x, float y, float width, float height)
      : x(x), y(y), vx(0), vy(0), width(width), height(height) {
  }

  virtual void update() = 0;
  void set_x(float new_x);
  void set_y(float new_y);
  void set_vx(float new_vx);
  void set_vy(float new_vy);
  float get_x() const;
  float get_y() const;
  float get_width() const;
  float get_height() const;

  virtual ~GameObject() {
  }
};
