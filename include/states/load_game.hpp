#pragma once
#include "init.hpp"
#include "state.hpp"

class LoadName : public State {
 public:
  State* loop(FlappyBird* game);
  std::string user_name_string = "";
  int buttonPositionSelected = 2;
  int nameError = 0;
  std::vector<Button> menuButtons = {
      {"Back", 0}, {"Insert", 0}, {"NameCamp", 1}};
};