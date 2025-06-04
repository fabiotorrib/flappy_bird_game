#pragma once
#include <vector>
#include <string>

//resolucao
#define SCREEN_H 720
#define SCREEN_W 1280

//fps
#define FPS 60.0

//estados
enum ScreenState { MAIN_MENU, NEW_NAME, LOAD_NAME, PLAY, PAUSE, GAME_OVER, EXIT};

//Botões menus
struct Button
{
    std::string name;
    int buttonSelectState;
};






