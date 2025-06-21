#pragma once
/**
 * @file difficulty_menu.hpp
 * @brief Definição da classe DifficultyMenu, que representa o estado do menu de seleção de dificuldade.
 */

/** Bibliotecas necessárias */
#include <memory>
#include "../defines.hpp"
#include "../init.hpp"
#include "../state.hpp"
#include "../assets.hpp"

/**
 * @class DifficultyMenu
 * @brief Gerencia a lógica e a renderização da tela de seleção de dificuldade.
 * @details Herda da classe base 'State' e implementa o comportamento específico
 * para permitir que o usuário escolha e salve um nível de dificuldade para o jogo.
 */
class DifficultyMenu : public State {
 public:
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
  void enter() override;
  int buttonPositionSelected = 1;
  DifficultyMenu();
  std::string difficultySelected = "noOne";

  /// @brief Vetor que armazena os botões do menu e seus estados de seleção.
  std::vector<Button> menuButtons = {
      {"Easy", 0}, {"Normal", 1}, {"Hard", 0}, {"Save", 0}};

  private:
    /// @brief Ponteiros inteligentes para os recursos visuais (imagens e fontes) do menu.
    std::unique_ptr<Image> buttonDifficultyEasy;
    std::unique_ptr<Image> buttonDifficultyNormal;
    std::unique_ptr<Image> buttonDifficultyHard;
    std::unique_ptr<Image> buttonSaveSelect;
    std::unique_ptr<Image> buttonSaveDeselect;
    std::unique_ptr<TextFont> font;
};