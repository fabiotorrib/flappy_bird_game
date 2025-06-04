#pragma once
//libs
#include <iostream>
#include <list>
#include <string>

//libs allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_physfs.h>

//Libs criadas
#include "defines.hpp"
#include "state.hpp"

//Globais
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_EVENT ev;
extern ALLEGRO_TIMER* timer_FPS;
extern ALLEGRO_BITMAP* icon;
extern ALLEGRO_KEYBOARD_STATE keystate;
extern ALLEGRO_MOUSE_STATE mousestate;


void init();
void deinit();

