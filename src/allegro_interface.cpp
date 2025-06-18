#include "../include/allegro_interface.hpp"
#include "../include/init.hpp"
#include "../include/states/main_menu.hpp"
#include "../include/states/play.hpp"  // Necessário para o dynamic_cast

AllegroController::AllegroController(float screen_w, float screen_h)
    : screen_width(screen_w), screen_height(screen_h) {
}

AllegroController::~AllegroController() {
}

void AllegroController::run() {
  motion = std::make_unique<Motion>();
  current_state = std::make_unique<MainMenu>();
  current_state->enter();  // Prepara o estado inicial

  bool redraw = true;
  ALLEGRO_EVENT ev;
  al_start_timer(timer_FPS);

  while (current_state != nullptr) {
    al_wait_for_event(event_queue, &ev);

    // O controller não sabe qual estado é. Ele só chama o método.
    // O polimorfismo decide se vai rodar o handle_input do MainMenu ou do Play.
    State* next_state = current_state->handle_input(ev);

    if (ev.type == ALLEGRO_EVENT_TIMER) {
      // Se o input não pediu uma transição, chamamos o update.
      // O polimorfismo decide qual update() rodar.
      if (next_state == current_state.get()) {
        next_state = current_state->update(*motion);
      }
      redraw = true;
    }

    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      next_state = nullptr;
    }

    if (redraw && al_is_event_queue_empty(event_queue)) {
      redraw = false;
      al_clear_to_color(al_map_rgb(0, 0, 0));

      // O polimorfismo decide qual render() rodar.
      current_state->draw(*motion);

      al_flip_display();
    }

    // Se handle_input ou update retornaram um novo estado, fazemos a transição.
    if (next_state != current_state.get()) {
      current_state.reset(next_state);
      if (current_state) {
        current_state->enter();  // Inicializa o novo estado
      }
    }
  }
}