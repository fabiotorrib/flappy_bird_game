#include "../include/game_object.hpp"

bool GameObject::check_bird_collision(const GameObject& other) const {
    // Verifica se a coordenada horizontal do meio do objeto está dentro da largura do 'other'
    // (cano).
    bool is_inside_other_horizontal =
        (x + width / 2.0f >= other.x) && (x + width / 2.0f <= other.x + other.width);

    // Verifica se a coordenada vertical do meio do objeto colide com a parte superior ou inferior
    // do 'other'. A colisão ocorre se o objeto estiver acima da abertura do cano (other.y) OU se o
    // objeto estiver abaixo da abertura do cano (other.y + GAP_SIZE).
    if (is_inside_other_horizontal &&
        ((y - height / 2.0f <= other.y) || (y + height / 2.0f >= other.y + GAP_SIZE))) {
        return true;  // Há colisão
    }
    return false;  // Não há colisão
}

// Verifica se o objeto colide com os limites superior (teto) ou inferior (chão) da tela.
bool GameObject::check_collision_with_boundaries() const {
    // Verifica colisão com o teto: se a posição Y do topo do objeto é menor ou igual a 0.
    if (y <= 0) {
        return true;
    }
    // Verifica colisão com o chão: se a posição Y da base do objeto é maior ou igual à altura da
    // tela.
    if (y + height >= SCREEN_H) {  // Assumindo que SCREEN_H é a altura da tela
        return true;
    }
    return false;  // Não há colisão com os limites
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
