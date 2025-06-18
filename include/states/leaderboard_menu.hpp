#pragma once
#include "../defines.hpp"
#include "../init.hpp"
#include "../state.hpp"

class LeaderboardMenu : public State {
 public:
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
  void enter() override;
};