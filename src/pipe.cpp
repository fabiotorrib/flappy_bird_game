#include "pipe.hpp"

void Pipe::update() {
  x += vx;
}

// para quem implementar a geracao dos pipes esse metodo pode ser usado para
// deletar pipes fora da tela
bool Pipe::is_off_screen() const {
  return x + width < 0;
}

// checa se o bird passou por essa instancia
bool Pipe::check_score(float bird_x) {
  if (!scored && bird_x > x + width) {
    scored = true;
    return true;
  }
  return false;
}
