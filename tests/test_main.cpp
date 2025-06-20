// tests/test_main.cpp

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest/doctest.h"
#include "init.hpp"

int main(int argc, char** argv) {
  // Inicializa a Allegro e todos os sistemas do jogo.
  // Eu preciso disso pra rodar instanciar variaveis do tipo bird,pipe,...
  init();

  // Configuração padrão do doctest para rodar os testes.
  doctest::Context context;
  context.applyCommandLine(argc, argv);

  // Roda os testes e guarda o resultado.
  int res = context.run();

  // O doctest pode pedir para sair mais cedo em alguns casos (ex: --help).
  // Garantimos que deinit() seja chamado mesmo nesses casos.
  if (context.shouldExit()) {
    deinit();  // Limpa os recursos da Allegro
    return res;
  }

  // Finaliza a Allegro e limpa todos os recursos.
  deinit();

  return res;
}