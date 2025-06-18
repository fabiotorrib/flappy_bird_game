#pragma once
#include "../state.hpp"
#include "../defines.hpp"

extern std::string inputNameScreen;

class MainMenu : public State {
public:
    ScreenState loop(const ALLEGRO_EVENT& ev) override;
    ScreenState draw(Motion& motion) override;
    int buttonPositionSelected=0;
    std::vector<Button> menuButtons = {
    {"NewGame", 1},
    {"LoadGame", 0},
    {"Settings", 0},
    {"Difficulty", 0},
    {"Leaderboard", 0},
    {"Exit", 0}};
};


