#include "../include/bird.hpp"

void Bird::update() {
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
  if (x < X_INIT) {
    loop_animation(1);
  } else if (breakanimation) {
    al_draw_rotated_bitmap(bird1, width / 2, height / 2, x + width / 2,
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
  if (type == 1) {
    // Cicla os frames de 1 em 1 a cada repetição para atualizar na tela
    frames = frames + 1;

    // Mantem o Bird com asa para cima durante 8 frames
    // Troca o value quando for igual a 8 para mudar para proxima imagem
    if ((frames <= contB) && (valueB == 0)) {
      al_draw_bitmap(bird1, x, y, 0);

      if (frames == contB) {
        contB = contB + 8;
        valueB++;
      }
    }

    // Troca a imagem para o Bird com asa no meio durante 8 frames
    if ((frames <= contB) && (valueB == 1)) {
      al_draw_bitmap(bird2, x, y + 2, 0);

      if (frames == contB) {
        contB = contB + TIME_GIF_BIRD;
        valueB++;
      }
    }

    // Troca a imagem para o Bird com asa para baixo durante 8 frames
    if ((frames <= contB) && (valueB == 2)) {
      al_draw_bitmap(bird3, x, y + 4, 0);

      if (frames == contB) {
        contB = contB + TIME_GIF_BIRD;
        valueB++;
      }
    }

    // Zera o value pra reiniciar o ciclo
    // Volta a imagem para o Bird com asa no meio para reiniciar o ciclo
    if ((frames <= contB) && (valueB == 3)) {
      al_draw_bitmap(bird2, x, y + 2, 0);

      if (frames == contB) {
        contB = contB + TIME_GIF_BIRD;
        valueB = 0;
      }
    }
  } else if (type == 2) {
    if (vy < 0) {
      frames = frames + 1;

      if ((frames <= contB) && (valueB == 0)) {
        al_draw_rotated_bitmap(bird1, width / 2, height / 2, x + width / 2,
                               y + height / 2, rotation, 0);

        if (frames == contB) {
          contB = contB + 8;
          valueB++;
        }
      }
      if ((frames <= contB) && (valueB == 1)) {
        al_draw_rotated_bitmap(bird2, width / 2, height / 2, x + width / 2,
                               y + height / 2 + 2, rotation, 0);

        if (frames == contB) {
          contB = contB + TIME_GIF_BIRD;
          valueB++;
        }
      }
      if ((frames <= contB) && (valueB == 2)) {
        al_draw_rotated_bitmap(bird3, width / 2, height / 2, x + width / 2,
                               y + height / 2 + 4, rotation, 0);
        if (frames == contB) {
          contB = contB + TIME_GIF_BIRD;
          valueB++;
        }
      }
      if ((frames <= contB) && (valueB == 3)) {
        al_draw_rotated_bitmap(bird2, width / 2, height / 2, x + width / 2,
                               y + height / 2 + 2, rotation, 0);
        if (frames == contB) {
          contB = contB + TIME_GIF_BIRD;
          valueB = 0;
        }
      }
    } else {
      al_draw_rotated_bitmap(bird1, width / 2, height / 2, x + width / 2,
                             y + height / 2, rotation, 0);
    }
  }
}

void Bird::jump() {
  if (x >= X_INIT) {
    vy = jumpForce;
  }
}

void Bird::destroy_bitmaps() {
  if (obj_sprite) {
    al_destroy_bitmap(obj_sprite);
    obj_sprite = nullptr;
  }
}

void Bird::set_by() {
  by = y + height * TETO_BIRD;
}

void Bird::set_break(bool value) {
  breakanimation = value;
}

void Bird::reset_xy() {
  x = -100;
  y = 200;
  vy = 0;
}