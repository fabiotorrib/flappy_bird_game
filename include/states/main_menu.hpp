#pragma once
/**
 * @file main_menu.hpp
 * @brief Definição da classe MainMenu, o estado que representa o menu principal do jogo.
 * @details Este cabeçalho declara a interface da classe MainMenu, que serve como
 * o ponto central de navegação para todas as outras telas do jogo.
 */

/** Bibliotecas necessárias */
#include "../assets.hpp"
#include "../defines.hpp"
#include "../init.hpp"
#include "../motion.hpp"
#include "../state.hpp"

// Esta variável é usada para comunicar ao estado 'LoadName' se ele deve
// operar no modo "NewGame" ou "LoadGame".
extern std::string inputNameScreen;

class MainMenu : public State {
 public:
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
  void enter() override;
  MainMenu();
  int buttonPositionSelected = 0;
  /// @brief Vetor que armazena os botões do menu e seus estados de seleção.
  std::vector<Button> menuButtons = {{"NewGame", 1},     {"LoadGame", 0},
                                     {"Settings", 0},    {"Difficulty", 0},
                                     {"Leaderboard", 0}, {"Exit", 0}};

 private:
    /// @brief Ponteiros inteligentes para todos os recursos visuais (imagens) do menu.
    std::unique_ptr<Image> logoNormal;
    std::unique_ptr<Image> buttonNewGameSelect;
    std::unique_ptr<Image> buttonNewGameDeselect;
    std::unique_ptr<Image> buttonLoadGameSelect;
    std::unique_ptr<Image> buttonLoadGameDeselect;
    std::unique_ptr<Image> buttonSettingsSelect;
    std::unique_ptr<Image> buttonSettingsDeselect;
    std::unique_ptr<Image> buttonDifficultySelect;
    std::unique_ptr<Image> buttonDifficultyDeselect;
    std::unique_ptr<Image> buttonLeaderboardSelect;
    std::unique_ptr<Image> buttonLeaderboardDeselect;
    std::unique_ptr<Image> buttonExitSelect;
    std::unique_ptr<Image> buttonExitDeselect;
};
