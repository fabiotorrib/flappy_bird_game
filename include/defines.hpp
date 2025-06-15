#pragma once
#include <string>
#include <vector>

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
  DIFFICULTY_MENU,
  LEADERBOARD_MENU,
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

//forca do pulo
#define JUMP_FORCE -2.0

//gravidade
#define GRAVITY 0.03


//multiplicador da rotacao do bird
#define ROTATION 0.2

#define X_INIT 400

//gap entre os canos
#define GAP_SIZE 180
#define GAP_X 500

// velocidade dos pipes
#define PIPE_SPEED -5

#define TETO_BIRD 0.368
#define TIME_GIF_BIRD 35
