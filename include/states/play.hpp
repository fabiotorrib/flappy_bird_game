/**
 * @file play.hpp
 * @brief Declaracao da classe Play, responsavel pelo estado de jogo ativo.
 * @details Este cabecalho define a classe Play, que orquestra a jogatina,
 *          incluindo controle de entrada, atualizacao de logica e renderizacao.
 */

#pragma once
#include "../flappy_bird_controller.hpp"
#include "../state.hpp"

/**
 * @class Play
 * @brief Estado principal de jogo: controla loop ativo, pontuação e game over.
 */

class Play : public State {
 private:
  std::unique_ptr<FlappyBird> flappy;
  ScreenState status;
  std::unique_ptr<Image> logoGameOver;
  std::unique_ptr<Image> buttonTryagainSelect;
  std::unique_ptr<Image> buttonTryagainDeselect;
  std::unique_ptr<Image> buttonExitSelect;
  std::unique_ptr<Image> buttonExitDeselect;
  std::unique_ptr<Image> buttonPause;
  std::unique_ptr<TextFont> font;
  int buttonPositionSelected = 0;
  std::vector<Button> menuButtons = {
      {"TryAgain", 1}, {"Exit", 0}};

 public:
  // Declaração do método enter
  void enter() override;

  // Supondo a nova arquitetura
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
  Play();
};