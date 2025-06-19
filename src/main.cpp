#include "../include/allegro_interface.hpp"
#include "../include/init.hpp"

// Adicionamos o iostream para podermos usar std::cerr
#include <iostream>
#include <stdexcept>  // Para std::runtime_error

int main() {
  try {
    // Bloco principal do seu jogo
    init();

    AllegroController game_controller(SCREEN_W, SCREEN_H);
    game_controller.run();

    deinit();

  } catch (const std::bad_alloc& e) {
    std::cerr << "\n!!! ERRO FATAL !!!\n" << std::endl;
    std::cerr << "O jogo será encerrado." << std::endl;
    exit(1);
  }
  return 0;
}