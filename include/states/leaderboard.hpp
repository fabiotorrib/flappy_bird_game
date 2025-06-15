#pragma once
#include <vector>
#include "../defines.hpp"
#include "../state.hpp"

class LeaderboardMenu : public State {
 public:
  ScreenState loop() override;
  int buttonPositionSelected = 1;
  std::vector<Button> menuButtons = {{"Exit", 0}, {"NextPage", 1}};
};