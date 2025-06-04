#include "../include/init.hpp"

//iniciando as variaveis
ALLEGRO_DISPLAY*      display      = nullptr;
ALLEGRO_EVENT_QUEUE*  event_queue  = nullptr;
ALLEGRO_TIMER*        timer_FPS    = nullptr;
ALLEGRO_EVENT         ev;

void init(){

    al_init();

    //iniciando objetos
    al_init_primitives_addon();
    al_init_image_addon();

    //iniciando inputs
    al_install_mouse();
    al_install_keyboard();

    //iniciando audio
    al_install_audio();

    //iniciando fonte
    al_init_ttf_addon();
    al_init_font_addon();

    //iniciando display
    display = al_create_display(SCREEN_W, SCREEN_H);
    event_queue = al_create_event_queue();
    timer_FPS = al_create_timer(1.0 / FPS);

     // registra fontes na fila (obrigatorio)
     al_register_event_source(event_queue, al_get_display_event_source(display));
     al_register_event_source(event_queue, al_get_keyboard_event_source());
     al_register_event_source(event_queue, al_get_mouse_event_source());
     al_register_event_source(event_queue, al_get_timer_event_source(timer_FPS));

    //titulo da janela
    al_set_window_title(display, "Flappy Bird");

    //associa display e a fila ao statico do estado
    State::setGlobals(display, event_queue);

    //iniciando o timer
    al_start_timer(timer_FPS);
}



void deinit(){
    //destruir fontes
    // al_destroy_font(font_debug);
    // al_destroy_font();

    //destruir audio

    //


    al_stop_timer(timer_FPS);
    al_destroy_timer(timer_FPS);
    al_destroy_event_queue(event_queue);
	al_destroy_display(display);
}