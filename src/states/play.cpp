#include "../../include/states/play.hpp"
#include "../../include/states/states.hpp"
#include <allegro5/allegro_primitives.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>

//#include <iostream>

void Play::init_objects(){
    flappy = std::make_unique<FlappyBird>();

}
ScreenState Play::loop()
{
    //aqui sao implementados os eventos de teclado e mouse
    while (al_get_next_event(queue, &ev)) {
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return ScreenState::EXIT;
        //exemplo aqui embaixo
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
            ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
                if (flappy->get_state() == 0){
                    flappy->starter();
                } else {
                    flappy->jump();
                }
                if (status == GAME_OVER){
                    flappy->reset();
                    status = PLAY;
                }
            }
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN &&
            ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                flappy->breaker();
                status = PAUSE;
        }
    }




    flappy->draw();
    flappy->control_pipes();
    flappy->update();
    flappy->update_score();
    flappy->change_velocity();
    if (flappy->check_collisions()){
        status = GAME_OVER;
        //rotina de salvamento
        //
    }

    if (status == PAUSE){
        //Desenhe aqui a tela de pause
        //para liberar o jogo basta mudar o status para PLAY e puxar a função flappy->unbreak();
        //de um tempo até soltar o unbreak

    }
    if (status == GAME_OVER){
        //desenhe aqui a tela do game over
        //se tiver botao de retry, muda o status para PLAY e chama flappy->reset();
        //se for trocar de state(voltar para o menu) tbm de um reset 
    }


    //esse eh o update
    al_flip_display();
    return ScreenState::PLAY;
}
