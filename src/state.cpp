#include "../include/state.hpp"

//inicializando as variaveis estaticas
ALLEGRO_DISPLAY*     State::display = nullptr;
ALLEGRO_EVENT_QUEUE* State::queue   = nullptr;
ALLEGRO_EVENT        State::ev;
void State::setGlobals(ALLEGRO_DISPLAY* d, ALLEGRO_EVENT_QUEUE* q) {
    display = d;
    queue   = q;
}
