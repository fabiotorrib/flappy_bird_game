#pragma once
#include <cmath>
#include <string>
#include <vector>

// resolucao
#define SCREEN_H 720
#define SCREEN_W 1280

// fps
#define FPS 60.0

// estados
enum ScreenState {
  PLAY,
  PAUSE,
  GAME_OVER,
};

// Botões menus
struct Button {
  std::string name;
  int buttonSelectState;
};
const float MAX_ROTATION_UP = -M_PI / 6.0f;   // Limite para cima (-30 graus)
const float MAX_ROTATION_DOWN = M_PI / 6.0f;  // Limite para baixo (+90 graus)

//
#define MAX_INPUT_LENGTH 33

// forca do pulo
#define JUMP_FORCE -15.0

// gravidade
#define GRAVITY 0.8

// multiplicador da rotacao do bird
#define ROTATION 0.05

// posicao inicial do movimento bird
#define X_INIT 350

// gap entre os canos
#define GAP_SIZE 220
#define GAP_X 500
// velocidade x do bird
#define BIRD_VEL 3
// velocidade dos pipes
#define PIPE_SPEED 5.0
// text oscilation
#define OSCILATION 3.0
// velocidade oscilation gif
#define TIME_GIF_BIRD 8

#define TETO_BIRD 0.368
