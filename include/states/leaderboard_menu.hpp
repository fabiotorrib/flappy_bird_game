#pragma once
#include <vector>
#include "../defines.hpp"
#include "../state.hpp"

class LeaderboardMenu : public State {
 public:
  ScreenState loop() override;
};