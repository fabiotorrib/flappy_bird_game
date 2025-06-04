#include "../../include/states/play.hpp"
#include <allegro5/allegro_primitives.h>   // se precisar desenhar algo

ScreenState Play::loop()
{
    //aqui sao implementados os eventos de teclado e mouse
    while (al_get_next_event(queue, &ev)) {
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return ScreenState::EXIT;
        //exemplo aqui embaixo
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
            ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) return ScreenState::MAIN_MENU;
    }
    //aqui sao implementados as partes visuais
    al_clear_to_color(al_map_rgb(0,0,0));

    //esse eh o update
    al_flip_display();
    return ScreenState::PLAY;
}

void Play::reset(){}