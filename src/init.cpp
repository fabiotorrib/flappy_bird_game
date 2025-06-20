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

ALLEGRO_FONT *font = NULL;

// Inciando Imagens
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *icone = NULL;
ALLEGRO_AUDIO_STREAM *background_music = NULL;
ALLEGRO_BITMAP *bird1 = NULL;
ALLEGRO_BITMAP *bird2 = NULL;
ALLEGRO_BITMAP *bird3 = NULL;
ALLEGRO_BITMAP *ground = NULL;
ALLEGRO_BITMAP *ground2 = NULL;
ALLEGRO_BITMAP *campLeaderboard = NULL;
ALLEGRO_BITMAP *flappy = NULL;
ALLEGRO_BITMAP *pipe1 = NULL;
ALLEGRO_BITMAP *pipeout = NULL;
ALLEGRO_BITMAP *clouds = NULL;
ALLEGRO_BITMAP *clouds2 = NULL;

void init() {
  al_init();

  // iniciando objetos
  al_init_primitives_addon();
  al_init_image_addon();

  // iniciando inputs
  al_install_keyboard();

  // iniciando audio
  al_install_audio();
  al_init_acodec_addon();
  al_reserve_samples(16);

  // iniciando fonte
  al_init_ttf_addon();
  al_init_font_addon();
  font = al_load_font("assets/TextFont.ttf", 50, 0);

  // iniciando imagens
  background = al_load_bitmap("assets/background.png");
  icone = al_load_bitmap("assets/icon.png");
  bird1 = al_load_bitmap("assets/B1.png");
  bird2 = al_load_bitmap("assets/B2.png");
  bird3 = al_load_bitmap("assets/B3.png");
  ground = al_load_bitmap("assets/Ground.png");
  ground2 = al_load_bitmap("assets/Ground.png");
  campLeaderboard = al_load_bitmap("assets/campLeaderboard.png");
  flappy = al_load_bitmap("assets/Flappy.png");
  pipe1 = al_load_bitmap("assets/PipeWithBottom.png");
  pipeout = al_load_bitmap("assets/PipeWithout.png");
  clouds = al_load_bitmap("assets/Clouds.png");
  clouds2 = al_load_bitmap("assets/Clouds.png");

  // iniciando display
  display = al_create_display(SCREEN_W, SCREEN_H);
  event_queue = al_create_event_queue();
  timer_FPS = al_create_timer(1.0 / FPS);
  al_set_display_icon(display, icone);

  // registra fontes na fila (obrigatorio)
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_timer_event_source(timer_FPS));

  // titulo da janela
  al_set_window_title(display, "Flappy Bird");
  al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

  // associa display e a fila ao statico do estado
  State::setGlobals(display, event_queue);

  // iniciando o timer
  al_start_timer(timer_FPS);

  // Inicia a música de fundo e sons globais
  static std::unique_ptr<Music> backgroundMusic =
      std::make_unique<Music>("assets/SoundTrack.ogg");
  backgroundMusic->playMusic();

  loadGlobalAssets();
}

void deinit() {
  unloadGlobalAssets();
  al_destroy_font(font);

  // destruir imagens
  al_destroy_bitmap(icone);
  al_destroy_bitmap(background);
  al_destroy_bitmap(bird1);
  al_destroy_bitmap(bird2);
  al_destroy_bitmap(bird3);
  al_destroy_bitmap(ground);
  al_destroy_bitmap(ground2);
  al_destroy_bitmap(flappy);
  al_destroy_bitmap(pipe1);
  al_destroy_bitmap(pipeout);
  al_destroy_bitmap(clouds);
  al_destroy_bitmap(clouds2);

  al_stop_timer(timer_FPS);
  al_destroy_timer(timer_FPS);
  al_destroy_event_queue(event_queue);
  al_destroy_display(display);
  al_uninstall_system();
}