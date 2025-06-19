#include "../include/states/settings_menu.hpp"
#include "../include/init.hpp"
#include "../include/states/main_menu.hpp"
#include <memory>

SettingsMenu::SettingsMenu(){
    campSettingsMusic = std::make_unique<Image>("assets/CampSettings.png", 40, 70);
    campSettingsNoMusic = std::make_unique<Image>("assets/CampSettingsWithoutMusic.png", 40, 70);
    buttonMusicSelect = std::make_unique<Image>("assets/ContourSelect.png", 40, 70);
    buttonMusicDaySelect = std::make_unique<Image>("assets/buttonMusicDaySelect.png", 40, 70);
    buttonMusicRainSelect = std::make_unique<Image>("assets/buttonMusicRainSelect.png", 40, 70);
    buttonMusicSnowSelect = std::make_unique<Image>("assets/buttonMusicSnowSelect.png", 40, 70);
    buttonNoMusicDaySelect = std::make_unique<Image>("assets/buttonNoMusicDaySelect.png", 40, 70);
    buttonNoMusicRainSelect = std::make_unique<Image>("assets/buttonNoMusicRainSelect.png", 40, 70);
    buttonNoMusicSnowSelect = std::make_unique<Image>("assets/buttonNoMusicSnowSelect.png", 40, 70);
    buttonBackSelect = std::make_unique<Image>("assets/buttonBackSelect.png", 496.5, 580);
    buttonBackDeselect = std::make_unique<Image>("assets/buttonBackDeselect.png", 496.5, 580);
    font = std::make_unique<TextFont>("assets/TextFont.ttf", 50);
    font->setColor(218, 15, 15);
}

State* SettingsMenu::handle_input(const ALLEGRO_EVENT& ev) {
  // aqui sao implementados os eventos de teclado e mouse
  if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
       ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
    selectSound->playSound(0.3);
    if (menuButtons[buttonPositionSelected].name == "Music") {
        if(musicState){
            std::cout << "Música desligada!" << std::endl;
            musicState = false;
        }else{
            std::cout << "Música ligada!" << std::endl;
            musicState = true;
        }

    } else if (menuButtons[buttonPositionSelected].name == "Day") {
      std::cout << "Clima Dia selecionada!" << std::endl;
      weatherSelected = "Day";
    } else if (menuButtons[buttonPositionSelected].name == "Snow") {
      std::cout << "Clima Neve selecionada!" << std::endl;
      weatherSelected = "Snow";
    }else if (menuButtons[buttonPositionSelected].name == "Rain") {
      std::cout << "Clima Rain selecionada!" << std::endl;
      weatherSelected = "Rain";
    }else if (menuButtons[buttonPositionSelected].name == "Back") {
      std::cout << "Clima " << weatherSelected << " salva!" << std::endl;
      return new MainMenu();
    }
  }

  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
    return new MainMenu();
  }
  ///////

   if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
    switch (ev.keyboard.keycode) {
      case ALLEGRO_KEY_DOWN:
      case ALLEGRO_KEY_RIGHT:
        menuButtons[buttonPositionSelected].buttonSelectState = 0;

        if (buttonPositionSelected == 4)
          buttonPositionSelected = 0;
        else
          buttonPositionSelected++;

        menuButtons[buttonPositionSelected].buttonSelectState = 1;
        break;

      case ALLEGRO_KEY_UP:
      case ALLEGRO_KEY_LEFT:
          menuButtons[buttonPositionSelected].buttonSelectState = 0;

          if (buttonPositionSelected == 0)
            buttonPositionSelected = 4;
          else
            buttonPositionSelected--;

          menuButtons[buttonPositionSelected].buttonSelectState = 1;
        break;
    }
  }
  return this;
}

void SettingsMenu::enter() {
  // Reseta a seleção visual dos botões
  for (auto& button : menuButtons) {
    button.buttonSelectState = 0;
  }

  // Define a seleção inicial para o botão "Normal" (posição 1)
  buttonPositionSelected = 0;
  menuButtons[buttonPositionSelected].buttonSelectState = 1;
}

State* SettingsMenu::update(Motion& motion) {
  motion.update();
  return this;
}

void SettingsMenu::draw(Motion& motion) {
  motion.draw();

  if (menuButtons[0].buttonSelectState){
    if(musicState)
    campSettingsMusic->Draw();
    else
    campSettingsNoMusic->Draw();

    buttonMusicSelect->Draw();
  }

  if(menuButtons[1].buttonSelectState){  
    if(musicState)
    buttonMusicDaySelect->Draw();
    else
    buttonNoMusicDaySelect->Draw();
  }else if (menuButtons[2].buttonSelectState){
    if(musicState)
    buttonMusicSnowSelect->Draw();
    else
    buttonNoMusicSnowSelect->Draw();
  }else if (menuButtons[3].buttonSelectState){
    if(musicState)
    buttonMusicRainSelect->Draw();
    else
    buttonNoMusicRainSelect->Draw();
  }

  if (menuButtons[4].buttonSelectState) {
    if(musicState)
    campSettingsMusic->Draw();
    else
    campSettingsNoMusic->Draw();
    buttonBackSelect->Draw();
  } else {
    buttonBackDeselect->Draw();
  }

  if (weatherSelected == "Day")
    font->writeText("Day weather selected!", ALLEGRO_ALIGN_CENTER, 640, 485);
  else if (weatherSelected == "Snow")
    font->writeText("Snow weather selected!", ALLEGRO_ALIGN_CENTER, 640, 485);
  else if (weatherSelected == "Rain")
    font->writeText("Rain weather selected!", ALLEGRO_ALIGN_CENTER, 640, 485);
}
