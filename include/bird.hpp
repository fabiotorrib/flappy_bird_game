/**
 * @file bird.hpp
 * @brief Declaracao da classe Bird (personagem controlavel).
 * @details Define logica de movimento, animacao e colisao do passaro.
 *          Comentarios seguem padrao Doxygen e sem acentos.
 */
#pragma once

#include <allegro5/allegro_primitives.h>
#include "defines.hpp"
#include "game_object.hpp"

/**
 * @class Bird
 * @brief Personagem controlável: gerencia movimento, animação de asas, pulo e detecção de colisões.
 */
class Bird : public GameObject {
 private:
  float gravity;                 //!< aceleracao gravitacional
  float jumpForce;               //!< impulso vertical ao pular
  float vy = 0;                  //!< velocidade vertical
  float rotation = 0;            //!< angulo de rotacao a desenhar
  float valueB = 0;              //!< indice da animacao
  float contB = TIME_GIF_BIRD;   //!< limite de frames por ciclo
  float frames = 0;              //!< contador de frames
  ALLEGRO_BITMAP* frame1;        //!< sprite asa para cima
  ALLEGRO_BITMAP* frame2;        //!< sprite asa meio
  ALLEGRO_BITMAP* frame3;        //!< sprite asa para baixo
  bool breakanimation = false;   //!< pausa animacao (quando colide)

 public:
  /**
   * @brief Construtor.
   * @param img   primeiro frame
   * @param x     posicao inicial x
   * @param y     posicao inicial y
   * @param img2  segundo frame
   * @param img3  terceiro frame
   */
  Bird(ALLEGRO_BITMAP* img, float x, float y, ALLEGRO_BITMAP* img2,
       ALLEGRO_BITMAP* img3)
      : GameObject(img, x, y, al_get_bitmap_width(img),
                   al_get_bitmap_height(img)),
        gravity(GRAVITY),
        jumpForce(JUMP_FORCE),
        frame1(img),
        frame2(img2),
        frame3(img3) {
  }

  /** @brief Destrutor padrao. */
  ~Bird() = default;

  /** @brief Atualiza fisica e posicao. */
  void update();

  /** @brief Desenha sprite atual com rotacao. */
  void draw() override;

  /** @brief Aplica impulso de pulo. */
  void jump();

  /**
   * @brief Gera animacao de bater de asas.
   * @param type 1 = intro; 2 = jogo ativo
   */
  void loop_animation(int type);

  /**
   * @brief Verifica colisao com outro GameObject.
   * @param other objeto alvo
   * @return true se colisao detectada
   */
  bool check_bird_collision(const GameObject& other) const;

  /** @brief Libera bitmap principal (quando necessario). */
  void destroy_bitmaps();

  /** @brief Atualiza coordenada by (usada na HUD ou limites). */
  void set_by();

  /** @brief Habilita/desabilita animacao apos colisao. */
  void set_break(bool value);

  /** @brief Reseta posicao inicial e velocidade. */
  void reset_xy();
};
