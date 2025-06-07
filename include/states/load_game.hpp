#pragma once
#include "../state.hpp"
#include <vector>
#include "../defines.hpp"

class LoadName : public State {
public:
    ScreenState loop() override;
    std::string user_name_string = "";
    int buttonPositionSelected=2;
    int nameError = 0;
    std::vector<Button> menuButtons = {
    {"Back", 0},
    {"Insert", 0},
    {"NameCamp", 1}};
};