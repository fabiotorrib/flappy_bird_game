#include "allegro_interface.hpp"
#include "libs.hpp"
#include "states/main_menu.hpp"
#include "states/play.hpp"

AllegroController::AllegroController(float screen_w, float screen_h)
    : screen_width(screen_w), screen_height(screen_h) {
}
AllegroController::~AllegroController() {
  deinit();
}

bool AllegroController::initialize() {
  init();
  return true;
}

void AllegroController::cleanup() {
  deinit();
}

void AllegroController::run() {
  // Começa com o estado do Menu Principal
  std::unique_ptr<State> currentState = std::make_unique<MainMenu>();

  // O loop principal do jogo
  while (currentState != nullptr) {
    // Chama o loop do estado atual e recebe o ponteiro para o próximo estado
    State* nextStateRaw = currentState->loop(&game);

    // Se o estado atual retornou um ponteiro para si mesmo, não faça nada.
    // Se retornou um novo estado, atualize o unique_ptr.
    if (nextStateRaw != currentState.get()) {
      currentState.reset(
          nextStateRaw);  // Transfere o controle para o novo estado
    }
  }
}