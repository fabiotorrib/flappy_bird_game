#pragma once
#include "../state.hpp"
#include "../flappy_bird_controller.hpp"

class Play : public State {
private:
    std::unique_ptr<FlappyBird> flappy;
    ScreenState status = PLAY;
public:
    void init_objects();
    ScreenState loop() override;
};