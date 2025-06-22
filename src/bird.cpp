/**
 * @file bird.cpp
 * @brief Implementação da classe Bird (animação, física e colisões).
 */

#include "../include/bird.hpp"

void Bird::update() {
  /**
   * @brief Atualiza física e posição do pássaro.
   *
   * Move horizontalmente durante a animação de entrada até alcançar
   * `X_INIT`. Depois aplica gravidade e velocidade vertical `vy`.
   */
  this->set_by();
  this->set_finals();
  if (x < X_INIT) {
    x += BIRD_VEL;
  } else {
    if (y_final <= SCREEN_H - 101) {
      y += vy;
      vy += gravity;
    }
  }
}

void Bird::draw() {
  /**
   * @brief Desenha o pássaro com a animação ou rotação correspondente.
   *
   * Seleciona entre a animação de entrada ou de voo conforme o estado do
   * jogo e controla a rotação baseada em `vy`.
   */
  if (x < X_INIT) {
    loop_animation(1);
  } else if (breakanimation) {
    al_draw_rotated_bitmap(frame1, width / 2, height / 2, x + width / 2,
                           y + height / 2, rotation, 0);
  } else {
    rotation = vy * ROTATION;
    if (rotation > MAX_ROTATION_DOWN) {
      // Se a rotação para baixo for maior que o permitido (30 graus),
      // trava em 30 graus.
      rotation = MAX_ROTATION_DOWN;
    } else if (rotation < MAX_ROTATION_UP) {
      // Se a rotação para cima for maior que o permitido (-30 graus),
      // trava em -30 graus.
      rotation = MAX_ROTATION_UP;
    }
    if (obj_sprite != NULL) {
      loop_animation(2);
    }
  }
}

void Bird::loop_animation(int type) {
  /**
   * @brief Muda os frames de sprite para simular bater de asas.
   * @param type 1 = animação de intro (pássaro voando da esquerda);
   *             2 = animação durante o jogo.
   */
  if (type == 1) {
    // Cicla os frames de 1 em 1 a cada repetição para atualizar na tela
    frames = frames + 1;

    // Mantem o Bird com asa para cima durante 8 frames
    // Troca o value quando for igual a 8 para mudar para proxima imagem
    if ((frames <= contB) && (valueB == 0)) {
      al_draw_bitmap(frame1, x, y, 0);

      if (frames == contB) {
        contB = contB + 8;
        valueB++;
      }
    }

    // Troca a imagem para o Bird com asa no meio durante 8 frames
    if ((frames <= contB) && (valueB == 1)) {
      al_draw_bitmap(frame2, x, y + 2, 0);

      if (frames == contB) {
        contB = contB + TIME_GIF_BIRD;
        valueB++;
      }
    }

    // Troca a imagem para o Bird com asa para baixo durante 8 frames
    if ((frames <= contB) && (valueB == 2)) {
      al_draw_bitmap(frame3, x, y + 4, 0);

      if (frames == contB) {
        contB = contB + TIME_GIF_BIRD;
        valueB++;
      }
    }

    // Zera o value pra reiniciar o ciclo
    // Volta a imagem para o Bird com asa no meio para reiniciar o ciclo
    if ((frames <= contB) && (valueB == 3)) {
      al_draw_bitmap(frame2, x, y + 2, 0);

      if (frames == contB) {
        contB = contB + TIME_GIF_BIRD;
        valueB = 0;
      }
    }
  } else if (type == 2) {
    // --- INÍCIO DA MODIFICAÇÃO ---

    // A lógica de animação de bater de asas agora fica fora do 'if (vy < 0)'
    // para que sempre aconteça.

    frames = frames + 1;

    if ((frames <= contB) && (valueB == 0)) {
      al_draw_rotated_bitmap(frame1, width / 2, height / 2, x + width / 2,
                             y + height / 2, rotation, 0);
      if (frames == contB) {
        contB = contB + 8;
        valueB++;
      }
    } else if ((frames <= contB) && (valueB == 1)) {
      al_draw_rotated_bitmap(frame2, width / 2, height / 2, x + width / 2,
                             y + height / 2 + 2, rotation, 0);
      if (frames == contB) {
        contB = contB + TIME_GIF_BIRD;
        valueB++;
      }
    } else if ((frames <= contB) && (valueB == 2)) {
      al_draw_rotated_bitmap(frame3, width / 2, height / 2, x + width / 2,
                             y + height / 2 + 4, rotation, 0);
      if (frames == contB) {
        contB = contB + TIME_GIF_BIRD;
        valueB++;
      }
    } else if ((frames <= contB) && (valueB == 3)) {
      al_draw_rotated_bitmap(frame2, width / 2, height / 2, x + width / 2,
                             y + height / 2 + 2, rotation, 0);
      if (frames == contB) {
        contB = contB + TIME_GIF_BIRD;
        valueB = 0;
      }
    }
  }
}

void Bird::jump() {
  /**
   * @brief Aplica impulso vertical quando o jogador pressiona pular.
   */
  if (x >= X_INIT) {
    vy = jumpForce;
  }
}

void Bird::destroy_bitmaps() {
  /**
   * @brief Destrói o bitmap principal para liberar memória.
   */
  if (obj_sprite) {
    al_destroy_bitmap(obj_sprite);
    obj_sprite = nullptr;
  }
}

void Bird::set_by() {
  /**
   * @brief Atualiza a coordenada inferior `by` com base na altura.
   */
  by = y + height * TETO_BIRD;
}

void Bird::set_break(bool value) {
  /**
   * @brief Ativa/desativa a animação após colisão.
   * @param value `true` para pausar a animação.
   */
  breakanimation = value;
}

void Bird::reset_xy() {
  /**
   * @brief Reseta posição e velocidade do pássaro para valores iniciais.
   */
  x = -100;
  y = 200;
  vy = 0;
}
bool Bird::check_bird_collision(const GameObject& other) const {
  /**
   * @brief Verifica colisão com outro objeto considerando uma hitbox reduzida.
   * @param other Objeto alvo.
   * @return `true` se as hitboxes se sobrepõem.
   */
  const float HORIZONTAL_INSET = 8.0f;       // Diminui X pixels de cada lado
  const float VERTICAL_INSET_TOP = 10.0f;    // Diminui X pixels do topo
  const float VERTICAL_INSET_BOTTOM = 6.0f;  // Diminui X pixels de baixo

  // Calcula as coordenadas da hitbox menor do pássaro
  float bird_box_x1 = this->x + HORIZONTAL_INSET;
  float bird_box_y1 = this->y + VERTICAL_INSET_TOP;
  float bird_box_x2 = (this->x + this->width) - HORIZONTAL_INSET;
  float bird_box_y2 = (this->y + this->height) - VERTICAL_INSET_BOTTOM;

  // Pega as coordenadas da hitbox do outro objeto (o cano)
  float other_box_x1 = other.get_x();
  float other_box_y1 = other.get_y();
  float other_box_x2 = other.get_x() + other.get_width();
  float other_box_y2 = other.get_y() + other.get_height();

  if (bird_box_x1 < other_box_x2 && bird_box_x2 > other_box_x1 &&
      bird_box_y1 < other_box_y2 && bird_box_y2 > other_box_y1) {
    return true;  // Há colisão
  }

  return false;  // Não há colisão
}
