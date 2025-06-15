#include "../include/init.hpp"

// iniciando as variaveis
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_TIMER *timer_FPS = nullptr;
ALLEGRO_EVENT ev;
Player player = Player(" ", 0);
std::vector<Player> ranking = player.ReadLeaderboard("Leaderboard.txt");

// Iniciando fonte
ALLEGRO_FONT *font = NULL;

// Inciando Imagens
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
ALLEGRO_AUDIO_STREAM *background_music = NULL;
ALLEGRO_SAMPLE *selectSound = NULL;
ALLEGRO_BITMAP *lights = NULL;
ALLEGRO_BITMAP *clouds = NULL;
ALLEGRO_BITMAP *clouds2 = NULL;
ALLEGRO_BITMAP *little = NULL;
ALLEGRO_BITMAP *little2 = NULL;
ALLEGRO_BITMAP *little3 = NULL;
ALLEGRO_BITMAP *bird1 = NULL;
ALLEGRO_BITMAP *bird2 = NULL;
ALLEGRO_BITMAP *bird3 = NULL;
ALLEGRO_BITMAP *ground = NULL;
ALLEGRO_BITMAP *ground2 = NULL;
ALLEGRO_BITMAP *buttonDifficultyEasy = NULL;
ALLEGRO_BITMAP *buttonDifficultyNormal = NULL;
ALLEGRO_BITMAP *buttonDifficultyHard = NULL;
ALLEGRO_BITMAP *buttonSaveSelect = NULL;
ALLEGRO_BITMAP *buttonSaveDeselect = NULL;
ALLEGRO_BITMAP *campLeaderboard = NULL;

void init() {
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
  al_attach_audio_stream_to_mixer(background_music, al_get_default_mixer());
  al_set_audio_stream_playmode(background_music, ALLEGRO_PLAYMODE_LOOP);
  selectSound = al_load_sample("assets/selectSound.wav");

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
  buttonDifficultyEasy = al_load_bitmap("assets/buttonDifficultyEasy.png");
  buttonDifficultyNormal = al_load_bitmap("assets/buttonDifficultyNormal.png");
  buttonDifficultyHard = al_load_bitmap("assets/buttonDifficultyHard.png");
  buttonSaveDeselect = al_load_bitmap("assets/buttonSaveDeselect.png");
  buttonSaveSelect = al_load_bitmap("assets/buttonSaveSelect.png");
  campLeaderboard = al_load_bitmap("assets/campLeaderboard.png");

  // iniciando display
  display = al_create_display(SCREEN_W, SCREEN_H);
  event_queue = al_create_event_queue();
  timer_FPS = al_create_timer(1.0 / FPS);
  al_set_display_icon(display, icone);

  // registra fontes na fila (obrigatorio)
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_mouse_event_source());
  al_register_event_source(event_queue, al_get_timer_event_source(timer_FPS));

  // titulo da janela
  al_set_window_title(display, "Flappy Bird");

  // associa display e a fila ao statico do estado
  State::setGlobals(display, event_queue);

  // iniciando o timer
  al_start_timer(timer_FPS);
}

void deinit() {
  // destruir fontes
  al_destroy_font(font);

  // destruir audio
  al_destroy_audio_stream(background_music);
  //

  // destruir imagens
  al_destroy_bitmap(buttonBackDeselect);
  al_destroy_bitmap(buttonBackSelect);
  al_destroy_bitmap(buttonInsertDeselect);
  al_destroy_bitmap(buttonInsertSelect);
  al_destroy_bitmap(nameCampDeselect);
  al_destroy_bitmap(nameCampSelect);
  al_destroy_bitmap(nameCampNewGameError);
  al_destroy_bitmap(nameLoadGameError);
  al_destroy_bitmap(buttonExitDeselect);
  al_destroy_bitmap(buttonExitSelect);
  al_destroy_bitmap(buttonDifficultySelect);
  al_destroy_bitmap(buttonLeaderboardSelect);
  al_destroy_bitmap(buttonLoadGameSelect);
  al_destroy_bitmap(buttonNewGameSelect);
  al_destroy_bitmap(buttonSettingsSelect);
  al_destroy_bitmap(buttonDifficultyDeselect);
  al_destroy_bitmap(buttonLeaderboardDeselect);
  al_destroy_bitmap(buttonLoadGameDeselect);
  al_destroy_bitmap(buttonNewGameDeselect);
  al_destroy_bitmap(buttonSettingsDeselect);
  al_destroy_bitmap(logoNormal);
  al_destroy_bitmap(icone);
  al_destroy_bitmap(lights);
  al_destroy_bitmap(background);
  al_destroy_bitmap(clouds);
  al_destroy_bitmap(clouds2);
  al_destroy_bitmap(little);
  al_destroy_bitmap(little2);
  al_destroy_bitmap(little3);
  al_destroy_bitmap(bird1);
  al_destroy_bitmap(bird2);
  al_destroy_bitmap(bird3);
  al_destroy_bitmap(ground);
  al_destroy_bitmap(ground2);
  al_destroy_bitmap(buttonDifficultyEasy);
  al_destroy_bitmap(buttonDifficultyNormal);
  al_destroy_bitmap(buttonDifficultyHard);
  al_destroy_bitmap(buttonSaveSelect);
  al_destroy_bitmap(buttonSaveDeselect);

  al_stop_timer(timer_FPS);
  al_destroy_timer(timer_FPS);
  al_destroy_event_queue(event_queue);
  al_destroy_display(display);
  al_uninstall_system();
}