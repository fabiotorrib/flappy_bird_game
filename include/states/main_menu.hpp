#pragma once
#include "../state.hpp"
#include <vector>
#include <defines.hpp>

class MainMenu : public State {
public:
    ScreenState loop() override;
    int buttonPositionSelected=0;
    std::vector<Button> menuButtons = {
    {"NewGame", 1},
    {"LoadGame", 0},
    {"Settings", 0},
    {"Difficulty", 0},
    {"Leaderboard", 0},
    {"Exit", 0}};
};


