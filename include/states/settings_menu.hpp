#pragma once
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
  std::vector<Button> menuButtons = {
      {"Music", 1}, {"Day", 0}, {"Snow", 0}, {"Rain", 0},{"Back", 0}};

  private:
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