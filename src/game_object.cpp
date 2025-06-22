/**
 * @file game_object.cpp
 * @brief Métodos utilitários da classe base GameObject.
 */

#include "../include/game_object.hpp"

/**
 * @brief Verifica colisão entre este objeto e outro.
 * @param other Objeto alvo para teste de colisão.
 * @return true se as áreas retangulares se sobrepõem.
 */
bool GameObject::check_bird_collision(const GameObject& other) const {
  // Verifica se a coordenada horizontal do meio do objeto está dentro da
  // largura do 'other' (cano).
  bool is_inside_other_horizontal =
      ((x_final >= other.x) && (x_final <= other.x_final)) ||
      ((x >= other.x) && (x <= other.x_final));

  bool is_inside_other_vertical =
      ((y_final >= other.y) && (y_final <= other.y_final)) ||
      ((by >= other.y) && (by <= other.y_final));

  if (is_inside_other_horizontal && is_inside_other_vertical) {
    return true;  // Há colisão
  }
  return false;  // Não há colisão
}

/**
 * @brief Detecta colisão do objeto com o teto ou chão da tela.
 * @return true se colidir.
 */
bool GameObject::check_collision_with_boundaries() const {
  // Verifica colisão com o teto: se a posição Y do topo do objeto é menor ou
  // igual a 0.
  if (x >= X_INIT) {
    if (by <= 0) {
      return true;
    }
    // Verifica colisão com o chão: se a posição Y da base do objeto é maior ou
    // igual à altura da tela.
    if (y_final >= SCREEN_H - 101) {  // 101 eh altura do chao
      return true;
    }
    return false;  // nao há colisão
  }
  return false;
}

/** @brief Define coordenada X. */
void GameObject::set_x(float new_x) {
  x = new_x;
}

/** @brief Define coordenada Y. */
void GameObject::set_y(float new_y) {
  y = new_y;
}

/** @brief Obtém coordenada X. */
float GameObject::get_x() const {
  return x;
}

/** @brief Obtém coordenada Y. */
float GameObject::get_y() const {
  return y;
}

/**
 * @brief Atualiza limites inferiores (x_final, y_final) para colisão.
 */
void GameObject::set_finals() {
  y_final = y + height;
  x_final = x + width;
}

/** @brief Retorna coordenada X final (direita). */
float GameObject::get_x_final() const {
  return x_final;
}