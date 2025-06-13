#include "init.hpp"
#include "defines.hpp"
#include "libs.hpp"
#include "state.hpp"

// iniciando as variaveis
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_TIMER *timer = nullptr;  // Corrigido o nome
ALLEGRO_EVENT ev;

// Iniciando fonte
ALLEGRO_FONT *font = NULL;

// Iniciando audio
ALLEGRO_AUDIO_STREAM *background_music = NULL;

// Iniciando Imagens
ALLEGRO_BITMAP *buttonBackDeselect = NULL;
ALLEGRO_BITMAP *buttonBackSelect = NULL;
ALLEGRO_BITMAP *buttonInsertDeselect = NULL;
ALLEGRO_BITMAP *buttonInsertSelect = NULL;
ALLEGRO_BITMAP *nameCampDeselect = NULL;
ALLEGRO_BITMAP *nameCampSelect = NULL;
ALLEGRO_BITMAP *nameCampNewGameError = NULL;
ALLEGRO_BITMAP *nameLoadGameError = NULL;
ALLEGRO_BITMAP *buttonExitDeselect = NULL;
ALLEGRO_BITMAP *buttonExitSelect = NULL;
ALLEGRO_BITMAP *buttonDifficultySelect = NULL;
ALLEGRO_BITMAP *buttonLeaderboardSelect = NULL;
ALLEGRO_BITMAP *buttonLoadGameSelect = NULL;
ALLEGRO_BITMAP *buttonNewGameSelect = NULL;
ALLEGRO_BITMAP *buttonSettingsSelect = NULL;
ALLEGRO_BITMAP *buttonDifficultyDeselect = NULL;
ALLEGRO_BITMAP *buttonLeaderboardDeselect = NULL;
ALLEGRO_BITMAP *buttonLoadGameDeselect = NULL;
ALLEGRO_BITMAP *buttonNewGameDeselect = NULL;
ALLEGRO_BITMAP *buttonSettingsDeselect = NULL;
ALLEGRO_BITMAP *logoNormal = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *icone = NULL;
ALLEGRO_BITMAP *lights = NULL;
ALLEGRO_BITMAP *clouds = NULL;
ALLEGRO_BITMAP *clouds2 = NULL;
ALLEGRO_BITMAP *little = NULL;
ALLEGRO_BITMAP *ground = NULL;
ALLEGRO_BITMAP *ground2 = NULL;
ALLEGRO_BITMAP *flappy = NULL;
ALLEGRO_BITMAP *pipe_green = NULL;

bool init() {
  al_init();

  // iniciando objetos
  al_init_primitives_addon();
  al_init_image_addon();

  // iniciando inputs
  al_install_mouse();
  al_install_keyboard();

  // iniciando audio
  al_install_audio();
  al_init_acodec_addon();
  al_reserve_samples(16);
  background_music = al_load_audio_stream("assets/SoundTrack.ogg", 8, 4096);
  if (background_music) {
    al_attach_audio_stream_to_mixer(background_music, al_get_default_mixer());
    al_set_audio_stream_playmode(background_music, ALLEGRO_PLAYMODE_LOOP);
  }

  // iniciando fonte
  al_init_ttf_addon();
  al_init_font_addon();
  font = al_load_font("assets/TextFont.ttf", 24, 0);

  // iniciando imagens
  buttonBackDeselect = al_load_bitmap("assets/buttonBackDeselect.png");
  buttonBackSelect = al_load_bitmap("assets/buttonBackSelect.png");
  buttonInsertDeselect = al_load_bitmap("assets/buttonInsertDeselect.png");
  buttonInsertSelect = al_load_bitmap("assets/buttonInsertSelect.png");
  nameCampDeselect = al_load_bitmap("assets/nameCampDeselect.png");
  nameCampSelect = al_load_bitmap("assets/nameCampSelect.png");
  nameCampNewGameError = al_load_bitmap("assets/nameCampNewGameError.png");
  nameLoadGameError = al_load_bitmap("assets/nameLoadGameError.png");
  buttonExitDeselect = al_load_bitmap("assets/buttonExitDeselect.png");
  buttonExitSelect = al_load_bitmap("assets/buttonExitSelect.png");
  buttonDifficultySelect = al_load_bitmap("assets/buttonDifficultySelect.png");
  buttonLeaderboardSelect =
      al_load_bitmap("assets/buttonLeaderboardSelect.png");
  buttonLoadGameSelect = al_load_bitmap("assets/buttonLoadGameSelect.png");
  buttonNewGameSelect = al_load_bitmap("assets/buttonNewGameSelect.png");
  buttonSettingsSelect = al_load_bitmap("assets/buttonSettingsSelect.png");
  buttonDifficultyDeselect =
      al_load_bitmap("assets/buttonDifficultyDeselect.png");
  buttonLeaderboardDeselect =
      al_load_bitmap("assets/buttonLeaderboardDeselect.png");
  buttonLoadGameDeselect = al_load_bitmap("assets/buttonLoadGameDeselect.png");
  buttonNewGameDeselect = al_load_bitmap("assets/buttonNewGameDeselect.png");
  buttonSettingsDeselect = al_load_bitmap("assets/buttonSettingsDeselect.png");
  logoNormal = al_load_bitmap("assets/logoNormal.png");
  background = al_load_bitmap("assets/background.png");
  icone = al_load_bitmap("assets/icon.png");
  lights = al_load_bitmap("assets/LightStrip.png");
  clouds = al_load_bitmap("assets/Clouds.png");
  clouds2 = al_load_bitmap("assets/Clouds.png");
  little = al_load_bitmap("assets/Frame1.png");
  little2 = al_load_bitmap("assets/Frame2.png");
  little3 = al_load_bitmap("assets/Frame3.png");
  bird1 = al_load_bitmap("assets/B1.png");
  bird2 = al_load_bitmap("assets/B2.png");
  bird3 = al_load_bitmap("assets/B3.png");
  ground = al_load_bitmap("assets/Ground.png");
  ground2 = al_load_bitmap("assets/Ground.png");
  pipe_green = al_load_bitmap("assets/pippe-green.png");  // pipe para testar

  // Verificar se foram criados com sucesso
  if (!display || !event_queue || !timer) {
    fprintf(stderr, "Erro ao criar display, event_queue ou timer!\n");
    return false;
  }

  al_set_display_icon(display, icone);

  // registra fontes na fila (obrigatorio)
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_mouse_event_source());
  al_register_event_source(event_queue, al_get_timer_event_source(timer));

  // titulo da janela
  al_set_window_title(display, "Flappy Bird");

  // IMPORTANTE: Associa display e a fila ao statico do estado
  State::setGlobals(display, event_queue);

  // iniciando o timer
  al_start_timer(timer);
}

void deinit() {
  // destruir fontes
  if (font) al_destroy_font(font);

  // destruir audio
  if (background_music) al_destroy_audio_stream(background_music);

  // destruir imagens
  if (buttonBackDeselect) al_destroy_bitmap(buttonBackDeselect);
  if (buttonBackSelect) al_destroy_bitmap(buttonBackSelect);
  if (buttonInsertDeselect) al_destroy_bitmap(buttonInsertDeselect);
  if (buttonInsertSelect) al_destroy_bitmap(buttonInsertSelect);
  if (nameCampDeselect) al_destroy_bitmap(nameCampDeselect);
  if (nameCampSelect) al_destroy_bitmap(nameCampSelect);
  if (nameCampNewGameError) al_destroy_bitmap(nameCampNewGameError);
  if (nameLoadGameError) al_destroy_bitmap(nameLoadGameError);
  if (buttonExitDeselect) al_destroy_bitmap(buttonExitDeselect);
  if (buttonExitSelect) al_destroy_bitmap(buttonExitSelect);
  if (buttonDifficultySelect) al_destroy_bitmap(buttonDifficultySelect);
  if (buttonLeaderboardSelect) al_destroy_bitmap(buttonLeaderboardSelect);
  if (buttonLoadGameSelect) al_destroy_bitmap(buttonLoadGameSelect);
  if (buttonNewGameSelect) al_destroy_bitmap(buttonNewGameSelect);
  if (buttonSettingsSelect) al_destroy_bitmap(buttonSettingsSelect);
  if (buttonDifficultyDeselect) al_destroy_bitmap(buttonDifficultyDeselect);
  if (buttonLeaderboardDeselect) al_destroy_bitmap(buttonLeaderboardDeselect);
  if (buttonLoadGameDeselect) al_destroy_bitmap(buttonLoadGameDeselect);
  if (buttonNewGameDeselect) al_destroy_bitmap(buttonNewGameDeselect);
  if (buttonSettingsDeselect) al_destroy_bitmap(buttonSettingsDeselect);
  if (logoNormal) al_destroy_bitmap(logoNormal);
  if (icone) al_destroy_bitmap(icone);
  if (lights) al_destroy_bitmap(lights);
  if (background) al_destroy_bitmap(background);
  if (clouds) al_destroy_bitmap(clouds);
  if (clouds2) al_destroy_bitmap(clouds2);
  if (little) al_destroy_bitmap(little);
  if (little2) al_destroy_bitmap(little2);
  if (little3) al_destroy_bitmap(little3);
  if (bird1) al_destroy_bitmap(bird1);
  if (bird2) al_destroy_bitmap(bird2);
  if (bird3) al_destroy_bitmap(bird3);
  if (ground) al_destroy_bitmap(ground);
  if (ground2) al_destroy_bitmap(ground2);
  if (pipe_green) al_destroy_bitmap(pipe_green);

  if (timer) {
    al_stop_timer(timer);
    al_destroy_timer(timer);
  }

  if (event_queue) al_destroy_event_queue(event_queue);
  if (display) al_destroy_display(display);
  al_uninstall_system();
}