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

// Musicas e efeitos sonoros
extern ALLEGRO_AUDIO_STREAM *background_music;
extern ALLEGRO_SAMPLE *selectSound;

// Fontes
extern ALLEGRO_FONT *font;

// Imagens
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
extern ALLEGRO_BITMAP *buttonDifficultyEasy;
extern ALLEGRO_BITMAP *buttonDifficultyNormal;
extern ALLEGRO_BITMAP *buttonDifficultyHard;
extern ALLEGRO_BITMAP *buttonSaveSelect;
extern ALLEGRO_BITMAP *buttonSaveDeselect;
extern ALLEGRO_BITMAP *campLeaderboard;
extern ALLEGRO_BITMAP *flappy;
extern ALLEGRO_BITMAP *pipe1;
extern ALLEGRO_BITMAP *pipeout;
extern ALLEGRO_BITMAP *background_snow;
extern ALLEGRO_BITMAP *flakesLittle;
extern ALLEGRO_BITMAP *flakesLittle2;
extern ALLEGRO_BITMAP *flakesBig;

void init();
void deinit();
