#pragma once
#include "../defines.hpp"
#include "../init.hpp"
#include "../state.hpp"

class LoadName : public State {
 public:
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
  void enter() override;
  std::string user_name_string = "";
  int buttonPositionSelected = 2;
  int nameError = 0;
  std::vector<Button> menuButtons = {
      {"Back", 0}, {"Insert", 0}, {"NameCamp", 1}};
};