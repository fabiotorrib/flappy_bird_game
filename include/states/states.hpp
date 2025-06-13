#pragma once
#include "main_menu.hpp"
#include "play.hpp"
#include "load_game.hpp"
#include "../motion.hpp"
#include "../motion_bird.hpp"

//criando e distribuindo os objetos globais de cada estado
inline MainMenu mainMenu;
inline Play play;
inline LoadName loadName;
inline Motion motion;
inline MotionBird motion_bird;
