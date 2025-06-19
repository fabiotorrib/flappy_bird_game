#pragma once
#include "../assets.hpp"
#include "../defines.hpp"
#include "../init.hpp"
#include "../motion.hpp"
#include "../state.hpp"

extern std::string inputNameScreen;

class MainMenu : public State {
 public:
  State* handle_input(const ALLEGRO_EVENT& ev) override;
  State* update(Motion& motion) override;
  void draw(Motion& motion) override;
  void enter() override;
  MainMenu();
  int buttonPositionSelected = 0;
  std::vector<Button> menuButtons = {{"NewGame", 1},     {"LoadGame", 0},
                                     {"Settings", 0},    {"Difficulty", 0},
                                     {"Leaderboard", 0}, {"Exit", 0}};

 private:
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
