#include "../include/init.hpp"


ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_EVENT ev;
ALLEGRO_TIMER* timer_FPS;
ALLEGRO_BITMAP* icon;
ALLEGRO_KEYBOARD_STATE keystate;
ALLEGRO_MOUSE_STATE mousestate;


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
    al_init_acodec_addon();

    //iniciando fonte
    al_init_ttf_addon();
    al_init_font_addon();

    //iniciando display
    display = al_create_display(SCREEN_W, SCREEN_H);
    event_queue = al_create_event_queue();
    timer_FPS = al_create_timer(1.0 / FPS);

    //titulo da janela
    al_set_window_title(display, "Flappy Bird");

}



void deinit(){
    //destruir fontes
    // al_destroy_font(font_debug);
    // al_destroy_font();

    //destruir audio

    //



    al_destroy_timer(timer_FPS);
    al_destroy_event_queue(event_queue);
	al_destroy_display(display);
}