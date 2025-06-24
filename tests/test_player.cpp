/**
 * @file test_player.cpp
 * @brief Testes unitários para a classe Player usando Doctest.
 */

#include "doctest/doctest.h"

#include <cstdio>  // Para std::remove
#include <fstream>
#include <string>
#include <vector>
#include "../include/player.hpp"

// Variável global para o nome do arquivo de teste
const std::string test_filename = "test_leaderboard.txt";

TEST_SUITE("Testes da Classe Player") {
  TEST_CASE("Construtor e Getters") {
    SUBCASE("Construtor com nome e pontuação padrão") {
      Player p("Alice");
      CHECK(p.GetName() == "Alice");
      CHECK(p.GetScore() == 0);
    }

    SUBCASE("Construtor com nome e pontuação especificada") {
      Player p("Bob", 150);
      CHECK(p.GetName() == "Bob");
      CHECK(p.GetScore() == 150);
    }
  }

  TEST_CASE("Setter de Pontuação") {
    Player p("Carol", 100);
    p.SetScore(200);
    CHECK(p.GetScore() == 200);
  }

  TEST_CASE("Operador de Comparação (<) para Ordenação Decrescente") {
    Player p_high_score("PlayerA", 500);
    Player p_low_score("PlayerB", 100);

    CHECK(p_high_score < p_low_score);
    CHECK_FALSE(p_low_score < p_high_score);
  }

  TEST_CASE("Verificação de Nome no Ranking (CheckingName)") {
    std::vector<Player> ranking;
    ranking.push_back(Player("David", 10));
    ranking.push_back(Player("Eve", 20));

    std::string name_exists = "David";
    std::string name_missing = "Frank";

    CHECK(Player::CheckingName(ranking, name_exists) == true);
    CHECK(Player::CheckingName(ranking, name_missing) == false);
  }

  TEST_CASE("Ordenação do Ranking (SortLeaderboard)") {
    std::vector<Player> ranking;
    ranking.push_back(Player("Charlie", 100));
    ranking.push_back(Player("Alice", 300));
    ranking.push_back(Player("Bob", 200));

    Player::SortLeaderboard(ranking);

    REQUIRE(ranking.size() == 3);
    CHECK(ranking[0].GetName() == "Alice");
    CHECK(ranking[0].GetScore() == 300);
    CHECK(ranking[1].GetName() == "Bob");
    CHECK(ranking[1].GetScore() == 200);
    CHECK(ranking[2].GetName() == "Charlie");
    CHECK(ranking[2].GetScore() == 100);
  }

  TEST_CASE("Leitura e Escrita de Arquivo de Ranking") {
    // Garante que o arquivo de teste não exista antes de começar
    std::remove(test_filename.c_str());

    std::vector<Player> original_ranking;
    original_ranking.push_back(Player("Gus", 88));
    original_ranking.push_back(Player("Heidi", 99));

    Player::SaveLeaderboard(test_filename, original_ranking);

    std::vector<Player> loaded_ranking = Player::ReadLeaderboard(test_filename);

    REQUIRE(loaded_ranking.size() == 2);
    CHECK(loaded_ranking[0].GetName() == "Gus");
    CHECK(loaded_ranking[0].GetScore() == 88);
    CHECK(loaded_ranking[1].GetName() == "Heidi");
    CHECK(loaded_ranking[1].GetScore() == 99);

    // Limpeza: remove o arquivo de teste
    std::remove(test_filename.c_str());
  }

  TEST_CASE("Salvar Ranking (Adicionar/Atualizar Jogador)") {
    // Garante que o arquivo de teste não exista antes de começar
    std::remove(test_filename.c_str());

    // Setup inicial: cria um ranking com um jogador
    std::vector<Player> ranking;
    ranking.push_back(Player("Ivan", 1000));
    Player::SaveLeaderboard(test_filename, ranking);

    SUBCASE("Adicionar um novo jogador") {
      Player new_player("Judy", 1500);
      Player::SaveLeaderboard(test_filename, ranking, new_player);

      std::vector<Player> updated_ranking =
          Player::ReadLeaderboard(test_filename);

      REQUIRE(updated_ranking.size() == 2);
      CHECK(updated_ranking[0].GetName() == "Ivan");
      CHECK(updated_ranking[1].GetName() == "Judy");
    }

    SUBCASE("Atualizar pontuação de jogador existente (com score maior)") {
      Player updated_player("Ivan", 1200);  // Pontuação maior que 1000
      Player::SaveLeaderboard(test_filename, ranking, updated_player);

      std::vector<Player> updated_ranking =
          Player::ReadLeaderboard(test_filename);

      REQUIRE(updated_ranking.size() == 1);
      CHECK(updated_ranking[0].GetName() == "Ivan");
      CHECK(updated_ranking[0].GetScore() == 1200);
    }

    SUBCASE(
        "Tentar atualizar pontuação de jogador existente (com score menor)") {
      Player updated_player("Ivan", 800);  // Pontuação menor que 1000
      Player::SaveLeaderboard(test_filename, ranking, updated_player);

      std::vector<Player> updated_ranking =
          Player::ReadLeaderboard(test_filename);

      // A pontuação não deve ter sido alterada
      REQUIRE(updated_ranking.size() == 1);
      CHECK(updated_ranking[0].GetName() == "Ivan");
      CHECK(updated_ranking[0].GetScore() == 1000);
    }

    // Limpeza final
    std::remove(test_filename.c_str());
  }

  // O teste para ShowLeaderboard é omitido, pois envolve renderização gráfica
  // (Allegro), que não é adequada para testes unitários automatizados. Tais
  // funcionalidades são geralmente verificadas com testes visuais ou de
  // integração.
}