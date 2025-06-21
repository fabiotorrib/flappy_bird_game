/**
 * @file leaderboard_menu.cpp
 * @brief Implementação da classe LeaderboardMenu, responsável por exibir a tela de ranking.
 * @details Este módulo carrega, ordena e exibe a pontuação dos jogadores,
 * além de gerenciar a interação do usuário nesta tela.
 */

/** Bibliotecas necessárias */
#include <memory>
#include "../include/states/leaderboard_menu.hpp"
#include "../include/init.hpp"
#include "../include/states/main_menu.hpp"

/**
 * @brief Construtor da classe LeaderboardMenu.
 * @details Carrega os recursos visuais necessários para a tela de ranking,
 * como a imagem de fundo e a fonte do texto.
 */
LeaderboardMenu::LeaderboardMenu(){
  font = std::make_unique<TextFont>("assets/TextFont.ttf", 46);
  campLeaderboard = std::make_unique<Image>("assets/campLeaderboard.png", 40, 100);
}

/**
 * @brief Gerencia a entrada do usuário (teclado).
 * @param ev O evento da Allegro a ser processado.
 * @return Retorna um ponteiro para o próximo estado. Retorna 'this' para continuar
 * no estado atual, 'nullptr' para fechar, ou um novo estado para transição.
 */
State* LeaderboardMenu::handle_input(const ALLEGRO_EVENT& ev) {
  // Permite fechar a janela do jogo.
  if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

   // Permite que o usuário retorne ao menu principal pressionando a tecla ESC.
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
    return new MainMenu();
  }

  return this; // Permanece neste estado.
}

/**
 * @brief Executado uma vez ao entrar no estado do Leaderboard.
 * @details Carrega os dados do placar a partir de um arquivo e os ordena
 * para exibição. Isso garante que a leitura e ordenação ocorram apenas
 * uma vez por visualização.
 */
void LeaderboardMenu::enter() {
  ranking = Player::ReadLeaderboard("Leaderboard.txt");
  Player::SortLeaderboard(ranking);
}

/**
 * @brief Atualiza a lógica do estado do movimento/animação do fundo.
 * @param motion Referência ao objeto de controle de animação do fundo.
 * @return Retorna 'this' para indicar a permanência no estado atual.
 */
State* LeaderboardMenu::update(Motion& motion) {
  motion.update();
  return this;
}

/**
 * @brief Desenha todos os elementos visuais do estado na tela.
 * @param motion Referência ao objeto de controle para desenhar o fundo animado.
 * @details Renderiza a imagem de fundo e, em seguida, itera sobre o ranking
 * para desenhar o nome e a pontuação de cada jogador em suas respectivas posições.
 */
void LeaderboardMenu::draw(Motion& motion) {
  motion.draw();
  campLeaderboard->Draw();

  
  int x_name_col = 270;        // Posição inicial para "Rank. Nome"
  float x_score_col = 888.14;  // Posição para a Pontuação (alinhada à direita)
  int y_inicial = 288;
  int vertical_distance = 45;

  // Itera sobre o vetor de ranking para exibir os jogadores.
  // O loop exibe no máximo as 7 primeiras posições.
  for (size_t i = 0; i < ranking.size() && i < 7; ++i) {
    int y_pos = y_inicial + i * vertical_distance;

    std::string name_and_rank_text = std::to_string(i + 1) + ". " + ranking[i].GetName();

    font->setColor(255, 255, 255);    
    font->writeText (name_and_rank_text.c_str(), ALLEGRO_ALIGN_LEFT, x_name_col, y_pos);
    std::string score_como_texto = std::to_string(ranking[i].GetScore());
    font->setColor(255, 255, 255);
    font->writeText(score_como_texto.c_str(), ALLEGRO_ALIGN_RIGHT, x_score_col, y_pos);
  }
    // Exibe uma instrução para o usuário retornar ao menu.
    font->setColor(0, 0, 0);
    font->writeText("Press Esc to back to main menu." , ALLEGRO_ALIGN_CENTER, 640, 60);
}
