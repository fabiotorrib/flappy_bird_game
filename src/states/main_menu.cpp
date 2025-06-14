// ./src/states/main_menu.cpp

#include "states/main_menu.hpp"
#include "states/load_game.hpp"
#include "states/states.hpp"  // Adicionado para ter acesso a 'motion' e 'motion_bird'

std::string inputNameScreen = "";

State* MainMenu::loop(FlappyBird* game) {
  // aqui sao implementados os eventos de teclado e mouse
  while (al_get_next_event(queue, &ev)) {
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
         ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
      if (menuButtons[buttonPositionSelected].name == "NewGame") {
        std::cerr << "Botão NewGame selecionado!" << std::endl;
        inputNameScreen = "NewGame";
        return new LoadName();
      } else if (menuButtons[buttonPositionSelected].name == "LoadGame") {
        std::cerr << "Botão LoadGame selecionado!" << std::endl;
        inputNameScreen = "LoadGame";
        return new LoadName();
      } else if (menuButtons[buttonPositionSelected].name == "Settings") {
        std::cerr << "Botão Settings selecionado!" << std::endl;
      } else if (menuButtons[buttonPositionSelected].name == "Difficulty") {
        std::cerr << "Botão Difficulty selecionado!" << std::endl;
      } else if (menuButtons[buttonPositionSelected].name == "Leaderboard") {
        std::cerr << "Botão Leaderboard selecionado!" << std::endl;
      } else if (menuButtons[buttonPositionSelected].name == "Exit") {
        std::cerr << "Botão Exit selecionado!" << std::endl;
        return nullptr;
      }
    }

    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
      menuButtons[buttonPositionSelected].buttonSelectState = 0;

      if (buttonPositionSelected == 5)
        buttonPositionSelected = 0;
      else
        buttonPositionSelected++;

      menuButtons[buttonPositionSelected].buttonSelectState = 1;
    }
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
        ev.keyboard.keycode == ALLEGRO_KEY_UP) {
      menuButtons[buttonPositionSelected].buttonSelectState = 0;

      if (buttonPositionSelected == 0)
        buttonPositionSelected = 5;
      else
        buttonPositionSelected--;

      menuButtons[buttonPositionSelected].buttonSelectState = 1;
    }
  }

  // ===================================================================
  // ALTERAÇÕES AQUI: RENDERIZAÇÃO COM ANIMAÇÃO
  // ===================================================================

  // 1. Chame motion.loop() para desenhar o fundo animado.
  //    Isso substitui a antiga chamada a al_draw_bitmap(background, 0, 0, 0);
  motion.loop();

  // 2. Defina a posição do pássaro animado e chame seu loop.
  //    Escolha uma posição que fique boa no menu.
  motion_bird.setterX(150);
  motion_bird.setterY(SCREEN_H / 2 - 50);
  motion_bird.loop();

  // 3. Desenhe os elementos da UI (logo e botões) SOBRE as animações.
  al_draw_bitmap(logoNormal, -20, -10, 0);

  // Desenha o botão NewGame
  if (menuButtons[0].buttonSelectState)
    al_draw_bitmap(buttonNewGameSelect, 496.5, 270, 0);
  else
    al_draw_bitmap(buttonNewGameDeselect, 496.5, 270, 0);

  // Desenha o botão LoadGame (lógica invertida no seu código original)
  if (menuButtons[1].buttonSelectState)
    al_draw_bitmap(buttonLoadGameDeselect, 496.5, 340, 0);  // select
  else
    al_draw_bitmap(buttonLoadGameSelect, 496.5, 340, 0);  // deselect

  // Desenha o botão Settings (lógica invertida no seu código original)
  if (menuButtons[2].buttonSelectState)
    al_draw_bitmap(buttonSettingsDeselect, 496.5, 410, 0);  // select
  else
    al_draw_bitmap(buttonSettingsSelect, 496.5, 410, 0);  // deselect

  // Desenha o botão Difficulty (lógica invertida no seu código original)
  if (menuButtons[3].buttonSelectState)
    al_draw_bitmap(buttonDifficultyDeselect, 496.5, 480, 0);  // select
  else
    al_draw_bitmap(buttonDifficultySelect, 496.5, 480, 0);  // deselect

  // Desenha o botão Leaderboard (lógica invertida no seu código original)
  if (menuButtons[4].buttonSelectState)
    al_draw_bitmap(buttonLeaderboardDeselect, 496.5, 550, 0);  // select
  else
    al_draw_bitmap(buttonLeaderboardSelect, 496.5, 550, 0);  // deselect

  // Desenha o botão Exit (lógica invertida no seu código original)
  if (menuButtons[5].buttonSelectState)
    al_draw_bitmap(buttonExitDeselect, 496.5, 620, 0);  // select
  else
    al_draw_bitmap(buttonExitSelect, 496.5, 620, 0);  // deselect

  // esse eh o update
  al_flip_display();
  return this;
}