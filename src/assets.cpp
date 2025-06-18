#include "../include/assets.hpp"

#include <memory>

Image::Image(const char *diretorio) {
  image = al_load_bitmap(diretorio);
  this->x = -1000;
  this->y = -1000;
  if (!image) {
    std::cout << "ERRO: Falha ao carregar a imagem em: " << diretorio
              << std::endl;
    throw std::bad_alloc();
  }
}

Image::Image(const char *diretorio, float x, float y) {
  image = al_load_bitmap(diretorio);
  this->x = x;
  this->y = y;
  if (!image) {
    std::cout << "ERRO: Falha ao carregar a imagem em: " << diretorio
              << std::endl;
    throw std::bad_alloc();
  }
}

void Image::Draw(float x, float y) { al_draw_bitmap(image, x, y, 0); }

void Image::Draw() { al_draw_bitmap(image, x, y, 0); }

Image::~Image() { al_destroy_bitmap(image); }

Music::Music(const char *diretorio) {
  music = al_load_audio_stream(diretorio, 8, 4096);
  if (!music) {
    std::cout << "ERRO: Falha ao carregar a música em: " << diretorio
              << std::endl;
    throw std::bad_alloc();
  }
  al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP);
}

void Music::playMusic() {
  al_attach_audio_stream_to_mixer(music, al_get_default_mixer());
}

Music::~Music() { al_destroy_audio_stream(music); }

Sound::Sound(const char *diretorio) {
  sound = al_load_sample(diretorio);
  if (!sound) {
    std::cout << "ERRO: Falha ao carregar o som em: " << diretorio << std::endl;
    throw std::bad_alloc();
  }
}

void Sound::playSound(float volume) {
  al_play_sample(sound, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

Sound::~Sound() { al_destroy_sample(sound); }

TextFont::TextFont(const char *diretorio, int size) {
  font = al_load_font(diretorio, size, 0);
  if (!font) {
    std::cout << "ERRO: Falha ao carregar o som em: " << diretorio << std::endl;
    throw std::bad_alloc();
  }
}

void TextFont::setColor(int r, int g, int b) {
  this->r = r;
  this->g = g;
  this->b = b;
}

void TextFont::writeText(const char *texto, int alinhamento, float x, float y) {
  al_draw_text(font, al_map_rgb(r, g, b), x, y, alinhamento, texto);
}

TextFont::~TextFont() { al_destroy_font(font); }