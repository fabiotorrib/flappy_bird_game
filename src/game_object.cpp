#include "../include/game_object.hpp"

bool GameObject::check_bird_collision(const GameObject& other) const {
    // Verifica se a coordenada horizontal do meio do objeto está dentro da largura do 'other'
    // (cano).
    bool is_inside_other_horizontal =
        ((x_final >= other.x) && (x_final <= other.x_final)) || ((x >= other.x) && (x <= other.x_final));

    bool is_inside_other_vertical =
        ((y_final >= other.y) && (y_final <= other.y_final)) || ((by >= other.y) && (by <= other.y_final));

    if (is_inside_other_horizontal && is_inside_other_vertical){
        return true;  // Há colisão
    }
    return false;  // Não há colisão
}

// Verifica se o objeto colide com os limites superior (teto) ou inferior (chão) da tela.
bool GameObject::check_collision_with_boundaries() const {
    // Verifica colisão com o teto: se a posição Y do topo do objeto é menor ou igual a 0.
    if(x >= X_INIT){
        if (by <= 0) {
            return true;
        }
        // Verifica colisão com o chão: se a posição Y da base do objeto é maior ou igual à altura da
        // tela.
        if (y_final >= SCREEN_H- 101) {  // 101 eh altura do chao
            return true;
        }
        return false; //nao há colisão
        }
    return false;
}

void GameObject::set_x(float new_x) {
  x = new_x;
}

void GameObject::set_y(float new_y) {
  y = new_y;
}

float GameObject::get_x() {
    return x;
}

float GameObject::get_y() {
    return y;
}

void GameObject::set_finals(){
    y_final = y+height;
    x_final = x+width;
}

float GameObject::get_x_final(){
    return x_final;
}