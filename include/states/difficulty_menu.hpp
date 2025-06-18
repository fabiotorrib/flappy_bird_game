#pragma once
#include "../defines.hpp"
#include "../state.hpp"

class DifficultyMenu : public State {
 public:
  ScreenState loop(const ALLEGRO_EVENT& ev) override;
  ScreenState draw(Motion& motion) override;
  int buttonPositionSelected = 1;
  std::string difficultySelected = "noOne";
  std::vector<Button> menuButtons = {
      {"Easy", 0}, {"Normal", 1}, {"Hard", 0}, {"Save", 0}};
};