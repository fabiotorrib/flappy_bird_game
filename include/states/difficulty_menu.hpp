#pragma once
#include "../defines.hpp"
#include "../init.hpp"
#include "../state.hpp"
#include "../assets.hpp"
#include <memory>

class DifficultyMenu : public State {
 public:
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
  void enter() override;
  int buttonPositionSelected = 1;
  DifficultyMenu();
  std::string difficultySelected = "noOne";
  std::vector<Button> menuButtons = {
      {"Easy", 0}, {"Normal", 1}, {"Hard", 0}, {"Save", 0}};

  private:
    std::unique_ptr<Image> buttonDifficultyEasy;
    std::unique_ptr<Image> buttonDifficultyNormal;
    std::unique_ptr<Image> buttonDifficultyHard;
    std::unique_ptr<Image> buttonSaveSelect;
    std::unique_ptr<Image> buttonSaveDeselect;
    std::unique_ptr<TextFont> font;
};