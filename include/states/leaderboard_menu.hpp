#pragma once
/**
 * @file leaderboard_menu.hpp
 * @brief Definição da classe LeaderboardMenu, que representa o estado da tela de ranking.
 * @details Este cabeçalho declara a interface da classe LeaderboardMenu,
 * responsável por carregar e exibir a lista de melhores pontuações do jogo.
 */

/** Bibliotecas necessárias */
#include "../defines.hpp"
#include "../init.hpp"
#include "../state.hpp"
#include "../assets.hpp"

/**
 * @class LeaderboardMenu
 * @brief Gerencia a lógica e a renderização da tela de ranking (placar de líderes).
 * @details Esta classe herda de 'State' e implementa o comportamento para ler
 * os dados de pontuação de um arquivo, ordená-los e exibi-los ao jogador em formato de tabela.
 */
class LeaderboardMenu : public State {
 public:
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
  void enter() override;
  LeaderboardMenu();

 private:
 /// @brief Ponteiros inteligentes para os recursos visuais (imagens e fontes) do menu.
  std::unique_ptr<TextFont> font;
  std::unique_ptr<Image> campLeaderboard; 
};