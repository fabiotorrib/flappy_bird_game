#include "game_object.hpp"

void GameObject::set_x(float new_x) {
  x = new_x;
}

void GameObject::set_y(float new_y) {
  y = new_y;
}

void GameObject::set_vx(float new_vx) {
  vx = new_vx;
}

void GameObject::set_vy(float new_vy) {
  vy = new_vy;
}

float GameObject::get_x() const {
  return x;
}

float GameObject::get_y() const {
  return y;
}

float GameObject::get_width() const {
  return width;
}

float GameObject::get_height() const {
  return height;
}
