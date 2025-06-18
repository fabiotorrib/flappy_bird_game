#pragma once

// Bibliotecas C++
#include <iostream>
#include <memory>
#include <string>

// Bibliotecas Allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

// Declaração das classes
class Image;
class Music;
class Sound;
class TextFont;

// Iniciar e deletar asssets globais
void loadGlobalAssets();
void unloadGlobalAssets();

// Classes para utilização dos Assets
class Image {
 private:
  ALLEGRO_BITMAP *image = NULL;
  float x, y;

 public:
  Image(const char *diretorio);
  Image(const char *diretorio, float x, float y);
  void Draw(float x, float y);
  void Draw();
  ~Image();
};

class Music {
 private:
  ALLEGRO_AUDIO_STREAM *music = NULL;

 public:
  Music(const char *diretorio);
  void playMusic();
  ~Music();
};

class Sound {
 private:
  ALLEGRO_SAMPLE *sound = NULL;

 public:
  Sound(const char *diretorio);
  void playSound(float volume);
  ~Sound();
};

class TextFont {
 private:
  ALLEGRO_FONT *font = NULL;
  int r, g, b = 0;

 public:
  TextFont(const char *diretorio, int size);
  void setColor(int r, int g, int b);
  void writeText(const char *texto, int alinhamento, float x, float y);
  ~TextFont();
};