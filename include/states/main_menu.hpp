#pragma once
#include "init.hpp"
#include "state.hpp"

extern std::string inputNameScreen;

class MainMenu : public State {
 public:
  State* loop(FlappyBird* game);
  int buttonPositionSelected = 0;
  std::vector<Button> menuButtons = {{"NewGame", 1},     {"LoadGame", 0},
                                     {"Settings", 0},    {"Difficulty", 0},
                                     {"Leaderboard", 0}, {"Exit", 0}};
};
