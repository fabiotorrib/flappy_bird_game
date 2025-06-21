#pragma once
/**
 * @file settings_menu.hpp
 * @brief Definição da classe SettingsMenu, que representa o estado do menu de configurações.
 * @details Este cabeçalho declara a interface da classe SettingsMenu, responsável por
 * permitir ao jogador ajustar opções como música e clima.
 */

/** Bibliotecas necessárias */
#include "../defines.hpp"
#include "../init.hpp"
#include "../state.hpp"
#include "../assets.hpp"
#include <memory>

class SettingsMenu : public State {
 public:
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
  void enter() override;
  int buttonPositionSelected = 0;
  SettingsMenu();
  std::string weatherSelected = "noOne";
  bool musicState = true;
  /// Vetor que armazena os botões do menu e seus estados de seleção.
  std::vector<Button> menuButtons = {
      {"Music", 1}, {"Day", 0}, {"Snow", 0}, {"Rain", 0},{"Back", 0}};

  private:
    /// Ponteiros inteligentes para todos os recursos visuais (imagens e fontes) do menu.
    std::unique_ptr<Image> campSettingsMusic;
    std::unique_ptr<Image> campSettingsNoMusic;
    std::unique_ptr<Image> buttonMusicSelect;
    std::unique_ptr<Image> buttonMusicDaySelect;
    std::unique_ptr<Image> buttonMusicRainSelect;
    std::unique_ptr<Image> buttonMusicSnowSelect;
    std::unique_ptr<Image> buttonNoMusicDaySelect;
    std::unique_ptr<Image> buttonNoMusicRainSelect;
    std::unique_ptr<Image> buttonNoMusicSnowSelect;
    std::unique_ptr<Image> buttonBackSelect;
    std::unique_ptr<Image> buttonBackDeselect;
    std::unique_ptr<TextFont> font;
};