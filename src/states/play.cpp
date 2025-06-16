#include "../../include/states/play.hpp"
#include "../../include/states/states.hpp"
#include <allegro5/allegro_primitives.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>

//#include <iostream>

void Play::init_objects(){
    flappy = std::make_unique<FlappyBird>();

}
ScreenState Play::loop(const ALLEGRO_EVENT& ev)
{
    //aqui sao implementados os eventos de teclado e mouse
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return ScreenState::EXIT;
    //exemplo aqui embaixo
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
            if (flappy->get_state() == 0){
                flappy->starter();
            } else {
                flappy->jump();
            }
        }
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
            flappy->breaker();
            status = PAUSE;
    }
    if(ev.type == ALLEGRO_EVENT_TIMER){
        flappy->set_current_player(player);

        flappy->draw();
        flappy->control_pipes();
        flappy->update();
        flappy->update_score();
        flappy->change_velocity();
        flappy->set_playerscore();
        if (flappy->check_collisions()){
            status = GAME_OVER;
            flappy->saveCurrentPlayerScore();
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
    }

    return ScreenState::PLAY;
}
