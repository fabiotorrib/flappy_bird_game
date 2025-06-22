/**
 * @file state.cpp
 * @brief Implementação base de State para máquina de estados do jogo.
 */

#include "../include/state.hpp"

//inicializando as variaveis estaticas
ALLEGRO_DISPLAY*     State::display = nullptr;
ALLEGRO_EVENT_QUEUE* State::queue   = nullptr;
ALLEGRO_EVENT        State::ev;

/**
 * @brief Configura ponteiros globais de display e fila de eventos.
 */
void State::setGlobals(ALLEGRO_DISPLAY* d, ALLEGRO_EVENT_QUEUE* q) {
    display = d;
    queue   = q;
}
