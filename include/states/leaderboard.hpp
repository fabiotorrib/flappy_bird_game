#pragma once
#include "../defines.hpp"
#include "../state.hpp"

class LeaderboardMenu : public State {
 public:
  ScreenState loop(const ALLEGRO_EVENT& ev) override;
  ScreenState draw(Motion& motion) override;
  int buttonPositionSelected = 1;
  std::vector<Button> menuButtons = {{"Exit", 0}, {"NextPage", 1}};
};