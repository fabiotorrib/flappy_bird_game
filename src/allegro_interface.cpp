/**
 * @file allegro_interface.cpp
 * @brief Implementação do controlador principal que integra Allegro às lógicas de estado do jogo.
 *
 * Este arquivo contém a implementação do `AllegroController`, responsável por
 * inicializar o primeiro estado, executar o loop de eventos da biblioteca
 * Allegro e orquestrar transições de estado, atualizações e renderizações.
 */
#include "../include/allegro_interface.hpp"
#include "../include/init.hpp"
#include "../include/state.hpp"  // Para o estado inicial MainMenu
#include "../include/states/main_menu.hpp"
#include "../include/states/play.hpp"

AllegroController::AllegroController(float screen_w, float screen_h)
    : screen_width(screen_w), screen_height(screen_h) {
}

/**
 * @brief Destrói o controlador Allegro liberando recursos.
 */
AllegroController::~AllegroController() {
}

/**
 * @brief Executa o loop principal do jogo.
 *
 * O método é dividido em quatro fases recorrentes:
 *   1. **Input** – aguarda um @c ALLEGRO_EVENT na fila e encaminha-o ao
 *      estado ativo para tratamento de entrada.
 *   2. **Update** – em eventos de timer, avança a lógica do jogo e dos
 *      objetos via @ref Motion.
 *   3. **Render** – redesenha a cena quando necessário e a fila de eventos
 *      está vazia.
 *   4. **State Transition** – se o estado ativo retornar um ponteiro
 *      diferente, realiza a troca, destruindo o estado anterior e chamando
 *      @c enter() no novo estado.
 *
 * O loop continua até que @c current_state se torne @c nullptr (por exemplo,
 * quando o usuário fecha a janela).
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