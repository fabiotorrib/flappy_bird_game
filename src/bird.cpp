#include "bird.hpp"

void Bird::update() {
  y += vy;
  vy += GRAVITY;

  // Atualiza rotação baseada na velocidade vertical
  rotation = vy * ROTATION;

  // Limita a rotação para não girar demais
  if (rotation > 1.5) rotation = 1.5;
  if (rotation < -1.5) rotation = -1.5;
}

float Bird::get_rotation() const {
  return rotation;
}
