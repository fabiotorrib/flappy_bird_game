#pragma once
#include "../assets.hpp"
#include "../defines.hpp"
#include "../init.hpp"
#include "../motion.hpp"
#include "../state.hpp"

extern std::string inputNameScreen;

class MainMenu : public State {
 public:
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
  void enter() override;
  int buttonPositionSelected = 0;
  std::vector<Button> menuButtons = {{"NewGame", 1},     {"LoadGame", 0},
                                     {"Settings", 0},    {"Difficulty", 0},
                                     {"Leaderboard", 0}, {"Exit", 0}};
};
