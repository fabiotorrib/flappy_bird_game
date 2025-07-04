#include "bird.hpp"  // Para checar colisão
#include "defines.hpp"
#include "doctest/doctest.h"
#include "pipe.hpp"

TEST_CASE("Testando a Classe Pipe e PipeList") {
  ALLEGRO_BITMAP* fake_bmp = al_create_bitmap(50, 300);
  ALLEGRO_BITMAP* fake_bird_bmp = al_create_bitmap(10, 10);

  SUBCASE("Pipe - Movimento e Status") {
    Pipe pipe(fake_bmp, SCREEN_W, 400);
    CHECK(pipe.get_x() == SCREEN_W);

    pipe.update();
    CHECK(pipe.get_x() == SCREEN_W - PIPE_SPEED);

    CHECK_FALSE(pipe.is_off_screen());
    pipe.set_x(-100);  // Força a saída da tela
    pipe.set_finals();
    CHECK(pipe.is_off_screen() == true);
  }

  SUBCASE("PipeList - Pontuação") {
    PipeList list(fake_bmp);
    list.reset();
    list.set_start();
    list.add_pipe_pair();  // Adiciona um cano na posição x = SCREEN_W

    // Verifica se o cano foi realmente adicionado
    REQUIRE(list.get_pipe_pairs().empty() == false);

    // Pega o cano que acabamos de criar para inspecioná-lo
    const auto& pipe_pair = list.get_pipe_pairs().front();
    const auto& bottom_pipe = pipe_pair.bottom;

    // Pega a coordenada REAL da borda direita do cano
    float pipe_x_final = bottom_pipe.get_x_final();

    // Logo após criar o cano, o pássaro não passou por ele
    bool scored_too_early = list.check_score(X_INIT + 1);
    CHECK_FALSE(scored_too_early);
    CHECK(list.get_points() == 0);

    bool scored_correctly = list.check_score(pipe_x_final + 1.0f);

    CHECK(scored_correctly == true);
    CHECK(list.get_points() == 1);
  }

  SUBCASE("PipeList - Colisão") {
    PipeList list(fake_bmp);
    list.reset();
    list.set_start();
    list.add_pipe_pair();  // Adiciona cano em x=1280, y=360, w=50, h=300

    // Pássaro colidindo com o cano de baixo
    // O cano de baixo vai de y=360 a y=660.
    // O pássaro está em x=1280, y=361.
    Bird bottom_crash_bird(fake_bird_bmp, SCREEN_W, 361, fake_bird_bmp,
                           fake_bird_bmp);

    // Inicializamos as fronteiras de colisão do pássaro antes de usar.
    bottom_crash_bird.set_finals();
    bottom_crash_bird.set_by();

    CHECK(list.check_collision(bottom_crash_bird) == true);

    // Pássaro em posição segura
    Bird safe_bird(fake_bird_bmp, X_INIT + 1, 300, fake_bird_bmp,
                   fake_bird_bmp);
    safe_bird.set_finals();
    safe_bird.set_by();
    CHECK_FALSE(list.check_collision(safe_bird));
  }

  al_destroy_bitmap(fake_bmp);
  al_destroy_bitmap(fake_bird_bmp);
}