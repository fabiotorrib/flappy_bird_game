/**
 * @file defines.hpp
 * @brief Constantes globais, macros e estruturas auxiliares do jogo.
 *
 * Contém dimensões de tela, física do pássaro, velocidades, gaps dos canos
 * e outros valores compartilhados entre módulos.
 */
#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

/**
 * @struct Button
 * @brief Estrutura auxiliar que representa um botão de menu e seu estado de seleção.
 */
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
#define GRAVITY 1.0

// multiplicador da rotacao do bird
#define ROTATION 0.05

// posicao inicial do movimento bird
#define X_INIT 350

// gap entre os canos
#define GAP_SIZE 250
#define GAP_X 300
// velocidade x do bird
#define BIRD_VEL 3
// velocidade dos pipes
#define PIPE_SPEED 5.5
#define PIPE_VERTICAL_SPEED 1.5
// text oscilation
#define OSCILATION 3.0
// velocidade oscilation gif
#define TIME_GIF_BIRD 8

#define TETO_BIRD 0.368
