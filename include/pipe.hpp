#pragma once

#include "defines.hpp"
#include "game_object.hpp"

class Pipe : public GameObject {
 private:
  float gap_size;
  bool scored;

 public:
  Pipe(float x = 0, float y = 0)
      : GameObject(x, y, 52, 320), gap_size(GAP_SIZE), scored(false) {
  }

  void update();
  bool check_score(float bird_x);
  bool is_off_screen() const;
};