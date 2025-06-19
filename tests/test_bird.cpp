#include "bird.hpp"
#include "defines.hpp"
#include "doctest/doctest.h"

TEST_CASE("Testando a Classe Bird") {
  // Criamos um bitmap falso para o construtor, já que o Allegro está
  // inicializado
  ALLEGRO_BITMAP* fake_bmp = al_create_bitmap(10, 10);
  Bird bird(fake_bmp, -100, 200, fake_bmp, fake_bmp);

  SUBCASE("Movimento inicial antes de X_INIT") {
    bird.update();
    CHECK(bird.get_x() == -100 + BIRD_VEL);
    CHECK(bird.get_y() == 200);  // Não deve cair ainda
  }

  SUBCASE("Aplicação da gravidade após X_INIT") {
    bird.set_x(X_INIT + 1);  // Força a posição para depois do início do jogo

    // No primeiro frame após X_INIT, vy ainda é 0, então y não muda.
    bird.update();
    CHECK(bird.get_y() == doctest::Approx(200.0));

    // No segundo frame, vy já foi incrementado pela gravidade
    bird.update();
    CHECK(bird.get_y() == doctest::Approx(200.0 + GRAVITY));
  }

  SUBCASE("Ação de Pular (jump)") {
    bird.set_x(X_INIT + 1);  // O pulo só funciona após X_INIT

    float y_before_jump = bird.get_y();
    bird.jump();    // Aplica a força do pulo
    bird.update();  // Aplica o movimento

    // A nova posição Y deve ser a antiga + a força do pulo
    CHECK(bird.get_y() == doctest::Approx(y_before_jump + JUMP_FORCE));
  }

  SUBCASE("Reset de Posição") {
    bird.set_x(500);
    bird.set_y(500);
    bird.reset_xy();
    CHECK(bird.get_x() == -100);
    CHECK(bird.get_y() == 200);
  }

  al_destroy_bitmap(fake_bmp);
}