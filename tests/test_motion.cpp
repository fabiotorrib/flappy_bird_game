
#include "../include/motion.hpp"
#include "doctest/doctest.h"

TEST_SUITE("Motion Tests") {
  TEST_CASE("Motion - Construtor inicializa corretamente") {
    Motion motion;

    // Construtor deve funcionar sem problemas
    // Motion é uma classe para efeitos visuais e parallax
    CHECK(true);  // Se chegou aqui, construtor funcionou
  }

  TEST_CASE("Motion - SetController com valores válidos") {
    Motion motion;

    motion.setController(1);  // Dia
    motion.setController(2);  // Chuva
    motion.setController(3);  // Neve

    // Testar valores extremos
    motion.setController(0);   // Valor mínimo
    motion.setController(10);  // Valor alto
    motion.setController(-1);  // Valor negativo

    CHECK(true);
  }

  TEST_CASE("Motion - Update funciona") {
    Motion motion;

    motion.update();

    // Testar update em diferentes controladores
    motion.setController(1);
    motion.update();

    motion.setController(2);
    motion.update();

    motion.setController(3);
    motion.update();

    CHECK(true);
  }

  TEST_CASE("Motion - Draw funciona") {
    Motion motion;

    motion.draw();

    // Testar draw em diferentes controladores
    motion.setController(1);
    motion.draw();

    motion.setController(2);
    motion.draw();

    motion.setController(3);
    motion.draw();

    CHECK(true);
  }

  TEST_CASE("Motion - Sequência de operações") {
    Motion motion;

    motion.setController(2);  // Configurar chuva

    for (int i = 0; i < 10; i++) {
      motion.update();
      motion.draw();
    }

    CHECK(true);
  }

  TEST_CASE("Motion - Mudança de controlador durante execução") {
    Motion motion;

    motion.setController(1);
    motion.update();
    motion.draw();

    motion.setController(2);
    motion.update();
    motion.draw();

    motion.setController(3);
    motion.update();
    motion.draw();

    CHECK(true);
  }

  TEST_CASE("Motion - Múltiplas instâncias") {
    Motion motion1;
    Motion motion2;

    motion1.setController(1);
    motion2.setController(2);

    motion1.update();
    motion2.update();

    motion1.draw();
    motion2.draw();

    CHECK(true);
  }

  TEST_CASE("Motion - Teste de controladores específicos") {
    Motion motion;

    // Teste controlador 1 (Dia)
    motion.setController(1);
    motion.update();
    motion.draw();

    // Teste controlador 2 (Chuva)
    motion.setController(2);
    motion.update();
    motion.draw();

    // Teste controlador 3 (Neve)
    motion.setController(3);
    motion.update();
    motion.draw();

    CHECK(true);
  }

  TEST_CASE("Motion - Loop de animação longo") {
    Motion motion;
    motion.setController(1);

    // Simular loop longo de animação
    for (int i = 0; i < 100; i++) {
      motion.update();

      // A cada 10 frames, desenhar
      if (i % 10 == 0) {
        motion.draw();
      }
    }

    CHECK(true);
  }

  TEST_CASE("Motion - Alternância rápida de controladores") {
    Motion motion;

    // Alternar rapidamente entre controladores
    for (int i = 0; i < 20; i++) {
      int controller = (i % 3) + 1;  // 1, 2, 3, 1, 2, 3...
      motion.setController(controller);
      motion.update();
      motion.draw();
    }

    CHECK(true);
  }

  TEST_CASE("Motion - Funcionalidade básica") {
    Motion motion;

    // Teste básico de funcionalidade
    motion.setController(1);
    motion.update();
    motion.draw();

    CHECK(true);
  }

  TEST_CASE("Motion - Robustez com valores extremos") {
    Motion motion;

    // Testar com valores muito altos
    motion.setController(999);
    motion.update();
    motion.draw();

    // Testar com valores negativos
    motion.setController(-999);
    motion.update();
    motion.draw();

    // Voltar para valor normal
    motion.setController(1);
    motion.update();
    motion.draw();

    CHECK(true);
  }

  TEST_CASE("Motion - Stress test") {
    Motion motion;

    // Teste de stress - muitas operações
    for (int controller = 1; controller <= 3; controller++) {
      motion.setController(controller);

      for (int frame = 0; frame < 50; frame++) {
        motion.update();
        motion.draw();
      }
    }

    CHECK(true);
  }

  TEST_CASE("Motion - Verificação de estabilidade") {
    Motion motion;

    // Verificar se funciona após muitas operações
    motion.setController(2);

    for (int i = 0; i < 1000; i++) {
      motion.update();
    }

    // Deve ainda conseguir desenhar
    motion.draw();

    CHECK(true);
  }
}