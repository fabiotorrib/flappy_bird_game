#include <algorithm>  // Para std::sort, se precisarmos
#include <vector>
#include "doctest/doctest.h"
#include "player.hpp"

// Incluímos o .cpp para ter acesso às funções auxiliares, se houver,
// ou podemos compilar o player.o junto. Vamos pela compilação.

TEST_CASE("Testando a Classe Player") {
  Player p1("JOGADOR_A");

  SUBCASE("Construtor e Getters") {
    CHECK(p1.GetName() == "JOGADOR_A");
    CHECK(p1.GetScore() == 0);  // Pontuação inicial deve ser 0
  }

  SUBCASE("Setter de Pontuação") {
    p1.SetScore(100);
    CHECK(p1.GetScore() == 100);

    p1.SetScore(50);
    CHECK(p1.GetScore() == 50);  // Deve atualizar para qualquer valor
  }

  SUBCASE("Sobrecarga do Operador < para Ordenação") {
    Player p_high("AAA", 999);
    Player p_mid("BBB", 500);
    Player p_low("CCC", 10);

    // A lógica de ordenação é decrescente (maior pontuação primeiro)
    // Então "p_high < p_mid" deve ser verdadeiro
    CHECK(p_high < p_mid);
    CHECK(p_mid < p_low);
    CHECK_FALSE(p_low < p_high);
  }

  SUBCASE("Ordenação do Leaderboard (SortLeaderboard)") {
    Player p1("JOGADOR_A", 100);
    Player p2("JOGADOR_B", 500);
    Player p3("JOGADOR_C", 50);

    std::vector<Player> ranking = {p1, p2, p3};

    // Antes de ordenar, a ordem é 100, 500, 50
    CHECK(ranking[0].GetScore() == 100);

    Player::SortLeaderboard(ranking);

    // Depois de ordenar, a ordem deve ser 500, 100, 50
    CHECK(ranking[0].GetName() == "JOGADOR_B");
    CHECK(ranking[0].GetScore() == 500);

    CHECK(ranking[1].GetName() == "JOGADOR_A");
    CHECK(ranking[1].GetScore() == 100);

    CHECK(ranking[2].GetName() == "JOGADOR_C");
    CHECK(ranking[2].GetScore() == 50);
  }
}