#pragma once
#include "../state.hpp"
class Play : public State {
public:
    ScreenState loop() override;
    //a funcao reset e utilizada ao iniciar uma nova partida
    void reset();
};