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

  } catch (const std::runtime_error& e) {
    // --- MUDANÇA AQUI ---
    // Em vez da caixa de diálogo nativa, imprimimos o erro no console.
    // std::cerr é o fluxo padrão para saídas de erro.
    std::cerr << "\n!!! ERRO FATAL !!!\n" << std::endl;
    std::cerr << "Exceção capturada: " << e.what() << std::endl;
    std::cerr << "O jogo será encerrado." << std::endl;

    // Retornamos um código de erro para o sistema operacional.
    return -1;
  }
}