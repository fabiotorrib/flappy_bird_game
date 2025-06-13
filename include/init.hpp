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

//Musicas
extern ALLEGRO_AUDIO_STREAM *background_music;

//Fontes
extern ALLEGRO_FONT* font;

//Imagens
extern ALLEGRO_BITMAP *buttonBackDeselect;
extern ALLEGRO_BITMAP *buttonBackSelect;
extern ALLEGRO_BITMAP *buttonInsertDeselect;
extern ALLEGRO_BITMAP *buttonInsertSelect;
extern ALLEGRO_BITMAP *nameCampDeselect;
extern ALLEGRO_BITMAP *nameCampSelect;
extern ALLEGRO_BITMAP *nameCampNewGameError;
extern ALLEGRO_BITMAP *nameLoadGameError;
extern ALLEGRO_BITMAP *buttonExitDeselect;
extern ALLEGRO_BITMAP *buttonExitSelect;
extern ALLEGRO_BITMAP *buttonDifficultySelect;
extern ALLEGRO_BITMAP *buttonLeaderboardSelect;
extern ALLEGRO_BITMAP *buttonLoadGameSelect;
extern ALLEGRO_BITMAP *buttonNewGameSelect;
extern ALLEGRO_BITMAP *buttonSettingsSelect;
extern ALLEGRO_BITMAP *buttonDifficultyDeselect;
extern ALLEGRO_BITMAP *buttonLeaderboardDeselect;
extern ALLEGRO_BITMAP *buttonLoadGameDeselect;
extern ALLEGRO_BITMAP *buttonNewGameDeselect;
extern ALLEGRO_BITMAP *buttonSettingsDeselect;
extern ALLEGRO_BITMAP *logoNormal;
extern ALLEGRO_BITMAP *background;
extern ALLEGRO_BITMAP *icone;
extern ALLEGRO_BITMAP *lights;
extern ALLEGRO_BITMAP *clouds;
extern ALLEGRO_BITMAP *clouds2;
extern ALLEGRO_BITMAP *little;
extern ALLEGRO_BITMAP *little2;
extern ALLEGRO_BITMAP *little3;
extern ALLEGRO_BITMAP *ground;
extern ALLEGRO_BITMAP *ground2;
extern ALLEGRO_BITMAP *bird1;
extern ALLEGRO_BITMAP *bird2;
extern ALLEGRO_BITMAP *bird3;


void init();
void deinit();

