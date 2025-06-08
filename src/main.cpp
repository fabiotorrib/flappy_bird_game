// Em src/main.cpp

#include "allegro_interface.hpp"

int main() {
  AllegroController allegro(SCREEN_W, SCREEN_H);

  // PASSO 1: INICIALIZAR O ALLEGRO
  if (!allegro.initialize()) {
    // Se a inicialização falhar, não continue.
    return -1;
  }

  // PASSO 2: RODAR O JOGO
  allegro.run();

  // PASSO 3: LIMPAR A MEMÓRIA (já é feito no destrutor, mas é bom saber)
  // allegro.cleanup(); // O destrutor ~AllegroController já chama deinit()

  return 0;
}