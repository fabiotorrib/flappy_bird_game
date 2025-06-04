#include "../../include/states/main_menu.hpp"
#include <allegro5/allegro_primitives.h>   // usado nesse exemplo aqui
#include "../../include/states/states.hpp" //necessario para modificar o objeto play (ou qualquer outro)

ScreenState MainMenu::loop()
{
    //aqui sao implementados os eventos de teclado e mouse
    while (al_get_next_event(queue, &ev)) {
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return ScreenState::EXIT;
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
            ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
                //reseta antes de começar a partida
                play.reset();
                return ScreenState::PLAY;
            }
    }
    //aqui sao implementados as partes visuais
    al_clear_to_color(al_map_rgb(255,255,0));

    //esse eh o update
    al_flip_display();
    return ScreenState::MAIN_MENU;
}
