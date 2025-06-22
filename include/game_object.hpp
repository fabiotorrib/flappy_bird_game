#pragma once

#include "init.hpp"

/**
 * @file game_object.hpp
 * @brief Classe base abstrata para todos os objetos renderizáveis.
 *
 * Define posição, dimensões e interface para atualização/desenho.
 * Todas as entidades que podem colidir ou ser renderizadas devem herdar
 * desta classe e implementar os métodos puros `update()` e `draw()`.
 */

class GameObject {
 protected:
  ALLEGRO_BITMAP* obj_sprite;
  float x, y;
  float by;
  float width, height;
  float y_final, x_final;

 public:
  /**
   * @class GameObject
   * @brief Objeto genérico do jogo contendo posição, sprite e hitbox.
   *
   * Fornece utilidades de colisão com retângulos e getters padronizados. As
   * coordenadas `(x, y)` representam o canto superior-esquerdo do sprite.
   */
  GameObject(ALLEGRO_BITMAP* img, float x, float y, float width, float height)
      : obj_sprite(img), x(x), y(y), width(width), height(height) {
  }

  virtual void update() = 0;
  virtual void draw() = 0;
  virtual bool check_bird_collision(const GameObject& other) const;
  bool check_collision_with_boundaries() const;
  void set_x(float new_x);
  void set_y(float new_y);
  float get_x() const;
  float get_y() const;
  float get_width() const {
    return width;
  }  // <-- Getter para width
  float get_height() const {
    return height;
  }  // <-- Getter para height

  void set_finals();
  float get_x_final() const;

  virtual ~GameObject() {
  }
};
