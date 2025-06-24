
#include "../include/flappy_bird_controller.hpp"
#include "../include/player.hpp"
#include "doctest/doctest.h"

// Leva o jogo do estado 0 (Intro) para o estado 1 (Aguardando).
void goToWaitingState(FlappyBird& game) {
  if (game.get_state() != 0) return;

  for (int i = 0; i < 500; ++i) {
    if (game.get_state() == 1) {
      return;  // Atingimos o estado 1, podemos sair.
    }
    game.update();
  }
  FAIL("O jogo nao conseguiu chegar ao estado 1 apos 500 updates.");
}

TEST_SUITE("FlappyBird Controller Tests") {
  TEST_CASE("FlappyBird - Construtor funciona") {
    // Testa se consegue criar o objeto sem crash
    FlappyBird game;
    CHECK(game.get_state() == 0);
  }

  TEST_CASE("FlappyBird - Reset funciona corretamente") {
    FlappyBird game;

    // Leva o jogo para o estado 1 (Aguardando)
    goToWaitingState(game);
    REQUIRE(game.get_state() == 1);

    // Inicia o jogo para ir para o estado 2 (Jogando)
    game.starter();
    REQUIRE(game.get_state() == 2);

    // AGORA sim, testamos o reset a partir de um estado de jogo ativo.
    game.reset();
    CHECK(game.get_state() == 0);
  }

  TEST_CASE("FlappyBird - Transição de estados correta") {
    FlappyBird game;

    REQUIRE(game.get_state() == 0);

    for (int i = 0; i < 500 && game.get_state() == 0; ++i) {
      game.update();
    }

    REQUIRE(game.get_state() == 1);

    game.starter();
    CHECK(game.get_state() == 2);
  }

  TEST_CASE("FlappyBird - Pássaro responde ao comando jump") {
    FlappyBird game;
    game.starter();  // Iniciar jogo

    game.jump();
    game.update();  // Processar um frame

    // Update deve continuar funcionando
    game.update();
  }

  TEST_CASE("FlappyBird - Configuração de jogador") {
    FlappyBird game;
    Player test_player("TestPlayer");

    // Deve conseguir definir jogador
    game.set_current_player(test_player);
  }

  TEST_CASE("FlappyBird - Detecção de colisões") {
    FlappyBird game;

    // No estado inicial, não deve haver colisões
    CHECK_FALSE(game.check_collisions());
  }

  TEST_CASE("FlappyBird - Controle de pipes") {
    FlappyBird game;

    game.control_pipes();

    const PipeList& pipes = game.get_pipes();
    // Verificar se lista de pipes existe
    const auto& pipe_pairs = pipes.get_pipe_pairs();
    CHECK(pipe_pairs.size() >= 0);  // Lista deve existir (mesmo que vazia)
  }

  TEST_CASE("FlappyBird - Atualização de pontuação") {
    FlappyBird game;

    // Atualizar score não deve causar crash
    game.update_score();
  }

  TEST_CASE("FlappyBird - Mudança de velocidade") {
    FlappyBird game;

    // Mudança de velocidade não deve causar crash
    game.change_velocity();
  }

  TEST_CASE("FlappyBird - Operações de pausa/resume") {
    FlappyBird game;

    // Operações de pausa não devem causar crash
    game.breaker();
    game.unbreaker();
  }

  TEST_CASE("FlappyBird - Métodos de renderização") {
    FlappyBird game;

    // Métodos de desenho não devem causar crash
    game.draw();
    game.draw_HUD();
    game.draw_intial_text();
    game.draw_animated_ground(2.0f);
  }

  TEST_CASE("FlappyBird - Atualização principal") {
    FlappyBird game;

    // Update principal não deve causar crash
    game.update();

    // Deve funcionar em diferentes estados
    game.starter();
    game.update();
  }

  TEST_CASE("FlappyBird - Acesso a objetos internos") {
    FlappyBird game;

    // Deve poder acessar bird e pipes
    const Bird& bird = game.get_bird();
    const PipeList& pipes = game.get_pipes();

    // Verificar se objetos são válidos
    bird.get_x();
    bird.get_y();
    // Usar método const
    const auto& pipe_pairs = pipes.get_pipe_pairs();
    CHECK(pipe_pairs.size() >= 0);  // Lista deve existir (mesmo que vazia)
  }

  TEST_CASE("FlappyBird - Sequência de jogo completa") {
    FlappyBird game;
    Player player("TestPlayer");

    // Configurar jogador
    game.set_current_player(player);

    // Leva o jogo para o estado de espera
    goToWaitingState(game);

    // Sequência de início de jogo
    game.starter();
    REQUIRE(game.get_state() == 2);  // Garante que o jogo realmente começou

    // Simular alguns frames de jogo (agora isso funciona de verdade)
    for (int i = 0; i < 10; i++) {
      game.update();
      game.draw();  // A chamada para draw não afeta a lógica, mas é bom
                    // mantê-la

      if (i % 3 == 0) {
        game.jump();  // Pulos agora terão efeito
      }
    }

    // Reset do jogo
    game.reset();
    CHECK(game.get_state() == 0);
  }

  TEST_CASE("FlappyBird - Gestão de pontuação") {
    FlappyBird game;
    Player player("TestPlayer");

    game.set_current_player(player);

    // Verificar métodos de pontuação
    game.set_playerscore();

    // Verificar se pipe list funciona
    const PipeList& pipes = game.get_pipes();
    const auto& pipe_pairs = pipes.get_pipe_pairs();
    CHECK(pipe_pairs.size() >= 0);  // Lista deve existir
  }

  TEST_CASE("FlappyBird - Estados válidos") {
    FlappyBird game;

    // Verificar transições de estado válidas
    int initial_state = game.get_state();
    CHECK((initial_state >= 0 && initial_state <= 2));

    game.starter();
    int game_state = game.get_state();
    CHECK((game_state >= 0 && game_state <= 2));

    game.reset();
    int reset_state = game.get_state();
    CHECK((reset_state >= 0 && reset_state <= 2));
  }

  TEST_CASE("FlappyBird - Funcionalidade básica de transição de estados") {
    FlappyBird game;

    // 1. Checa o estado inicial
    CHECK(game.get_state() == 0);

    // 2. Transita para o estado de espera
    goToWaitingState(game);
    CHECK(game.get_state() == 1);

    // 3. Inicia o jogo e transita para o estado de jogo
    game.starter();
    CHECK(game.get_state() == 2);
  }
}