#pragma once
#include <string>
#include <vector>
#include "../defines.hpp"
#include "../state.hpp"

class DifficultyMenu : public State {
 public:
  ScreenState loop() override;
  int buttonPositionSelected = 1;
  std::string difficultySelected = "noOne";
  std::vector<Button> menuButtons = {
      {"Easy", 0}, {"Normal", 1}, {"Hard", 0}, {"Save", 0}};
};