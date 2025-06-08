#pragma once

#include <string>

// resolucao
#define SCREEN_H 720
#define SCREEN_W 1280

// fps
#define FPS 60.0

// estados
enum ScreenState {
  MAIN_MENU,
  NEW_NAME,
  LOAD_NAME,
  PLAY,
  PAUSE,
  GAME_OVER,
  EXIT
};

// Botões menus
struct Button {
  std::string name;
  int buttonSelectState;
};

//
#define MAX_INPUT_LENGTH 33

// forca do pulo
#define JUMP_FORCE -10.0

// gravidade
#define GRAVITY 0.8

// multiplicador da rotacao do bird
#define ROTATION 0.05

// gap entre os canos
#define GAP_SIZE 150

// velocidade dos pipes
#define PIPE_SPEED -5

#define MIN_PIPE_H 350
