#pragma once
/**
 * @file load_game.hpp
 * @brief Definição da classe LoadName, que representa o estado de inserção de nome.
 * @details Este cabeçalho declara a interface para a tela onde o jogador
 * digita seu nome para criar um novo jogo ou carregar um jogo existente.
 */

/** Bibliotecas necessárias */
#include <memory>
#include "../defines.hpp"
#include "../init.hpp"
#include "../state.hpp"
#include "../../include/assets.hpp"

// Enumeração para representar os possíveis resultados e erros da tela de inserção de nome. 
enum insertNameSituations
{
    noName,
    existName,
    noexistName,
    noError,
    successInsert
};

class LoadName : public State {
 public:
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
  void enter() override;
  LoadName();
  std::string playerNameString = "";
  int buttonPositionSelected = 2;
  int errorSituation = noError;

  /// Vetor que armazena os botões do menu e seus estados de seleção.
  std::vector<Button> menuButtons = {
      {"Back", 0}, {"Insert", 0}, {"NameCamp", 1}};
  
 private:
    /// Ponteiros inteligentes para os recursos visuais (imagens e fontes) da tela.
    std::unique_ptr<Image> buttonBackSelect;
    std::unique_ptr<Image> buttonBackDeselect;
    std::unique_ptr<Image> buttonInsertSelect;
    std::unique_ptr<Image> buttonInsertDeselect;
    std::unique_ptr<Image> nameCampSelect;
    std::unique_ptr<Image> nameCampDeselect;
    std::unique_ptr<TextFont> nameFont;
    std::unique_ptr<TextFont> errorFont;   

};