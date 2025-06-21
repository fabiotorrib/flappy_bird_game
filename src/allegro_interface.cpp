#include "../include/allegro_interface.hpp"
#include "../include/init.hpp"
#include "../include/state.hpp"  // Para o estado inicial MainMenu
#include "../include/states/main_menu.hpp"
#include "../include/states/play.hpp"

AllegroController::AllegroController(float screen_w, float screen_h)
    : screen_width(screen_w), screen_height(screen_h) {
}

AllegroController::~AllegroController() {
}

/**
 O loop é responsável por:
 * 1. Esperar por eventos do Allegro (teclado, timer, etc.).
 * 2. Despachar os eventos para o estado atual para tratamento de input.
 * 3. Acionar as atualizações de lógica e desenho em um ritmo constante (via
 * ALLEGRO_EVENT_TIMER).
 * 4. Orquestrar as transições entre os diferentes estados do jogo.
 * A lógica de transição é baseada em ponteiros. O estado atual retorna
 * um ponteiro para si mesmo para continuar, um ponteiro para um novo estado
 * (alocado com 'new') para transicionar, ou 'nullptr' para encerrar o jogo.
 */
void AllegroController::run() {
  /// Inicializa os componentes que o controller gerencia.
  motion = std::make_unique<Motion>();
  current_state = std::make_unique<MainMenu>();

  /// Chama o método de inicialização do primeiro estado.
  current_state->enter();

  bool redraw = true;
  ALLEGRO_EVENT ev;
  al_start_timer(timer_FPS);

  // O loop principal continua enquanto houver um estado ativo.
  while (current_state != nullptr) {
    /// Espera por um novo evento na fila. O programa fica bloqueado aqui
    /// até que algo aconteça, economizando CPU.
    al_wait_for_event(event_queue, &ev);

    /// --- Fase 1: Processar Entradas (Input) ---
    /// Delega o tratamento do evento para o estado ativo atual.
    State* next_state = current_state->handle_input(ev);

    /// --- Fase 2: Atualizar a Lógica (Update) ---
    /// A lógica do jogo avança em resposta a um evento do timer.
    if (ev.type == ALLEGRO_EVENT_TIMER) {
      // Só chama o update se o handle_input não já tiver sinalizado uma troca
      // de estado.
      if (next_state == current_state.get()) {
        // O polimorfismo decide qual update() rodar, passando o objeto motion.
        next_state = current_state->update(*motion);
      }
      redraw = true;  // Sinaliza que a tela precisa ser redesenhada.
    }

    /// --- Tratamento de Eventos Globais ---
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      // Define o ponteiro como nulo para sinalizar o fim do loop.
      current_state = nullptr;
      // O continue pula para a próxima iteração, onde a condição do while
      // falhará.
      continue;
    }

    /// --- Fase 3: Desenhar os Gráficos (Render) ---
    /// Só redesenha se necessário e se não houver mais eventos na fila.
    if (redraw && al_is_event_queue_empty(event_queue)) {
      redraw = false;
      al_clear_to_color(al_map_rgb(0, 0, 0));

      // O polimorfismo decide qual método 'draw' rodar.
      current_state->draw(*motion);

      al_flip_display();
    }

    /// --- Fase 4: Transição de Estado ---
    /// Se handle_input ou update retornaram um novo estado, fazemos a
    /// transição.
    if (next_state != current_state.get()) {
      // .reset() deleta o estado antigo e assume a posse do novo.
      current_state.reset(next_state);

      // Se o novo estado não for nulo, chama seu método de inicialização.
      if (current_state) {
        current_state->enter();
      }
    }
  }
}