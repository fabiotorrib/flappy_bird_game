#pragma once
// libs
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>

// libs allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_physfs.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/bitmap.h>

// Libs criadas
#include "assets.hpp"
#include "defines.hpp"
#include "player.hpp"
#include "state.hpp"

class Player;

// Globais
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer_FPS;
extern ALLEGRO_BITMAP *icon;
extern ALLEGRO_KEYBOARD_STATE keystate;
extern Player player;
extern std::vector<Player> ranking;
extern bool g_sound_on;
extern int difficulty;

// Fontes
extern ALLEGRO_FONT *font;

// Sons globais
extern std::unique_ptr<Sound> selectSound;
extern std::unique_ptr<Music> backgroundMusic;

void init();
void deinit();
