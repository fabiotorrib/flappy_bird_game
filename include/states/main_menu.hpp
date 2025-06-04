#pragma once
#include "../state.hpp"
class MainMenu : public State {
public:
    ScreenState loop() override;
};
