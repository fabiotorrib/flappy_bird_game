#include "../include/pipe.hpp"

//classe Pipe
void Pipe::update(){
    x-=vx;
    set_finals();
}

void Pipe::draw() {
    al_draw_bitmap(obj_sprite,x,y,0);
}

// para quem implementar a geracao dos pipes esse metodo pode ser usado para
// deletar pipes fora da tela
bool Pipe::is_off_screen() const {
    return x_final < 0;
}

// checa se o bird passou por essa instancia
bool Pipe::check_score(float bird_x) {
    if (!scored && bird_x > x_final) {
        scored = true;
        return true;
    }
    return false;
}
void Pipe::set_vx(float vel){
    vx = vel;
}


//classe PipeList
    void PipeList::draw() {
        for (PipePair& pair : Pipes) {
            pair.top.draw();
            pair.bottom.draw();
        }
    }

    void PipeList::set_vx(float vel){
        for (PipePair& pair : Pipes) {
            pair.top.set_vx(vel);
            pair.bottom.set_vx(vel);
        }
    }

    void PipeList::update() {
        for (PipePair& pair : Pipes) {
            pair.top.update();
            pair.bottom.update();
        }
    }

    void PipeList::add_pipe_pair() {
        if (!Pipes.empty() && start){
            if(SCREEN_W - Pipes.back().bottom.get_x_final() >= GAP_X){
            //sorteia entre as duas imagens do pipe e a altura do pipe
                std::uniform_int_distribution<int> dist2(GAP_SIZE+20,SCREEN_H-101-20);
                int y1 = dist2(gen);

                Pipes.emplace_back(pipe1,SCREEN_W,y1);
            }
        }
        if (start && Pipes.empty()){
            Pipes.emplace_back(pipe1,SCREEN_W,360);
        }
    }

    void PipeList::delete_pipe_pair() {
        if (!Pipes.empty()){
            if (Pipes.begin()->bottom.is_off_screen()){
                Pipes.erase(Pipes.begin());
            }
        }
    }

    bool PipeList::check_collision(GameObject& bird){
        for (PipePair& pair : Pipes){
            if (bird.check_bird_collision(pair.bottom) || bird.check_bird_collision(pair.top)){
                return true;
            }
        }
        return false;
    }

    bool PipeList::check_score(float bird_x) {
        for (PipePair& pair : Pipes) {
            if (pair.bottom.check_score(bird_x)) {
                //colocar audio de pontuação aqui
                points++;
                return true;
            }
        }
        return false;
    }

    bool PipeList::set_start(){
        if (!start){
            start = true;
            return true;
        }
        return false;
    }

    int PipeList::get_points(){
        return points;
    }

    void PipeList::reset(){
        Pipes.clear();
        points = 0;
        start = false;
    }