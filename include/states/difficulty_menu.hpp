#pragma once
#include "../defines.hpp"
#include "../init.hpp"
#include "../state.hpp"

class DifficultyMenu : public State {
 public:
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
  void enter() override;
  int buttonPositionSelected = 1;
  std::string difficultySelected = "noOne";
  std::vector<Button> menuButtons = {
      {"Easy", 0}, {"Normal", 1}, {"Hard", 0}, {"Save", 0}};
};