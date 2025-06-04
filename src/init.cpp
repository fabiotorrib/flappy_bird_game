#include "../include/init.hpp"

// iniciando as variaveis
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_TIMER *timer_FPS = nullptr;
ALLEGRO_EVENT ev;

// Inciando Imagens
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
ALLEGRO_BITMAP *logoBorred = NULL;
ALLEGRO_BITMAP *logoNormal = NULL;
ALLEGRO_BITMAP *background = NULL;

void init()
{

    al_init();

    // iniciando objetos
    al_init_primitives_addon();
    al_init_image_addon();

    // iniciando inputs
    al_install_mouse();
    al_install_keyboard();

    // iniciando audio
    al_install_audio();

    // iniciando fonte
    al_init_ttf_addon();
    al_init_font_addon();

    // iniciando imagens
    buttonExitDeselect = al_load_bitmap("assets/buttonExitDeselect.png");
    buttonExitSelect = al_load_bitmap("assets/buttonExitSelect.png");
    buttonDifficultySelect = al_load_bitmap("assets/buttonDifficultySelect.png");
    buttonLeaderboardSelect = al_load_bitmap("assets/buttonLeaderboardSelect.png");
    buttonLoadGameSelect = al_load_bitmap("assets/buttonLoadGameSelect.png");
    buttonNewGameSelect = al_load_bitmap("assets/buttonNewGameSelect.png");
    buttonSettingsSelect = al_load_bitmap("assets/buttonSettingsSelect.png");
    buttonDifficultyDeselect = al_load_bitmap("assets/buttonDifficultyDeselect.png");
    buttonLeaderboardDeselect = al_load_bitmap("assets/buttonLeaderboardDeselect.png");
    buttonLoadGameDeselect = al_load_bitmap("assets/buttonLoadGameDeselect.png");
    buttonNewGameDeselect = al_load_bitmap("assets/buttonNewGameDeselect.png");
    buttonSettingsDeselect = al_load_bitmap("assets/buttonSettingsDeselect.png");
    logoBorred = al_load_bitmap("assets/logoBorred.png");
    logoNormal = al_load_bitmap("assets/logoNormal.png");
    background = al_load_bitmap("assets/background.png");

    // iniciando display
    display = al_create_display(SCREEN_W, SCREEN_H);
    event_queue = al_create_event_queue();
    timer_FPS = al_create_timer(1.0 / FPS);

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

void deinit()
{
    // destruir fontes
    //  al_destroy_font(font_debug);
    //  al_destroy_font();

    // destruir audio

    //

    // destruir imagens
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
    al_destroy_bitmap(logoBorred);
    al_destroy_bitmap(logoNormal);

    al_stop_timer(timer_FPS);
    al_destroy_timer(timer_FPS);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_uninstall_system();
}