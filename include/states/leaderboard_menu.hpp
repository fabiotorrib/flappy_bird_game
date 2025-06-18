#pragma once
#include "../defines.hpp"
#include "../state.hpp"

class LeaderboardMenu : public State {
 public:
  ScreenState loop(const ALLEGRO_EVENT& ev) override;
  ScreenState draw(Motion& motion) override;
};