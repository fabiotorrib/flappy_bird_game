/**
 * @file init.cpp
 * @brief Inicialização de Allegro, fontes, addons e recursos globais.
 */

#include "../include/init.hpp"
#include <allegro5/bitmap_io.h>
#include "../include/assets.hpp"

// iniciando as variaveis
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_TIMER *timer_FPS = nullptr;
Player player = Player(" ", 0);
std::vector<Player> ranking = player.ReadLeaderboard("Leaderboard.txt");
bool g_sound_on = true;
int difficulty = 1;

ALLEGRO_FONT *font = NULL;

// Inciando Imagens

ALLEGRO_BITMAP *icon = NULL;

std::unique_ptr<Music> backgroundMusic;

/**
 * @brief Inicializa Allegro, janela, áudio e recursos globais.
 */
void init() {
  if (!al_init()) {
    throw std::runtime_error("Falha ao inicializar o Allegro.");
  }

  // iniciando objetos
  al_init_primitives_addon();
  al_init_image_addon();

  // iniciando inputs
  if (!al_install_keyboard()) {
    throw std::runtime_error("Falha ao instalar o teclado.");
  }

  // iniciando audio
  if (!al_install_audio()) {
    throw std::runtime_error("Falha ao instalar o áudio.");
  }
  if (!al_init_acodec_addon()) {
    throw std::runtime_error("Falha ao inicializar o addon de codec de áudio.");
  }
  al_reserve_samples(16);

  // iniciando fonte
  al_init_ttf_addon();
  al_init_font_addon();
  font = al_load_font("assets/TextFont.ttf", 50, 0);
  if (!font) {
    throw std::runtime_error("Falha ao carregar a fonte: assets/TextFont.ttf");
  }

  // iniciando imagens
  icon = al_load_bitmap("assets/icon.png");
  if (!icon) {
    throw std::runtime_error("Falha ao carregar o ícone: assets/icon.png");
  }

  // iniciando display
  display = al_create_display(SCREEN_W, SCREEN_H);
  if (!display) {
    throw std::runtime_error("Falha ao criar o display.");
  }
  event_queue = al_create_event_queue();
  timer_FPS = al_create_timer(1.0 / FPS);
  al_set_display_icon(display, icon);

  al_set_display_icon(display, icon);

  // registra fontes na fila (obrigatorio)
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_timer_event_source(timer_FPS));

  // titulo da janela
  al_set_window_title(display, "Flappy Bird");
  al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);

  // associa display e a fila ao statico do estado
  State::setGlobals(display, event_queue);

  // iniciando o timer
  al_start_timer(timer_FPS);

  // Inicia a música de fundo e sons globais
  backgroundMusic = std::make_unique<Music>("assets/SoundTrack.ogg");
  backgroundMusic->playMusic();

  loadGlobalAssets();
}

/**
 * @brief Libera todos os recursos e encerra o subsistema Allegro.
 */
void deinit() {
  al_stop_timer(timer_FPS);

  backgroundMusic.reset();

  unloadGlobalAssets();

  al_destroy_font(font);
  al_destroy_bitmap(icon);

  al_destroy_timer(timer_FPS);
  al_destroy_event_queue(event_queue);
  al_destroy_display(display);
  al_uninstall_system();
}