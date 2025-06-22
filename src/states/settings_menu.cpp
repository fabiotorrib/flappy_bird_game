
/**
 * @file settings_menu.cpp
 * @brief Implementação da classe SettingsMenu, que gerencia a tela de configurações do jogo.
 * @details Este módulo contém a lógica para manipulação de entrada, atualização de estado e
 * renderização dos elementos gráficos da tela de configurações.
 */

/** Bibliotecas necessárias */
#include "../../include/states/settings_menu.hpp"
#include <memory>
#include "../../include/init.hpp"
#include "../../include/states/main_menu.hpp"

/**
 * @brief Construtor da classe SettingsMenu.
 * @details Inicializa e carrega todos os recursos gráficos (imagens e fontes)
 * necessários para a tela de configurações.
 */
SettingsMenu::SettingsMenu() {
  // Carrega as imagens de fundo para os estados com e sem música.
  campSettingsMusic =
      std::make_unique<Image>("assets/CampSettings.png", 40, 70);
  campSettingsNoMusic =
      std::make_unique<Image>("assets/CampSettingsWithoutMusic.png", 40, 70);
  
  // Carrega as imagens de seleção para cada botão do menu.
  buttonMusicSelect =
      std::make_unique<Image>("assets/ContourSelect.png", 40, 70);
  buttonMusicDaySelect =
      std::make_unique<Image>("assets/buttonMusicDaySelect.png", 40, 70);
  buttonMusicRainSelect =
      std::make_unique<Image>("assets/buttonMusicRainSelect.png", 40, 70);
  buttonMusicSnowSelect =
      std::make_unique<Image>("assets/buttonMusicSnowSelect.png", 40, 70);
  buttonNoMusicDaySelect =
      std::make_unique<Image>("assets/buttonNoMusicDaySelect.png", 40, 70);
  buttonNoMusicRainSelect =
      std::make_unique<Image>("assets/buttonNoMusicRainSelect.png", 40, 70);
  buttonNoMusicSnowSelect =
      std::make_unique<Image>("assets/buttonNoMusicSnowSelect.png", 40, 70);
  buttonBackSelect =
      std::make_unique<Image>("assets/buttonBackSelect.png", 496.5, 580);
  buttonBackDeselect =
      std::make_unique<Image>("assets/buttonBackDeselect.png", 496.5, 580);

  // Inicializa a fonte de texto e define sua cor.    
  font = std::make_unique<TextFont>("assets/TextFont.ttf", 50);
  font->setColor(218, 15, 15);
}

/**
 * @brief Processa a entrada do usuário (teclado e mouse).
 * @param ev O evento da Allegro a ser processado.
 * @return Retorna um ponteiro para o próximo estado do jogo. Retorna `this` para
 * continuar neste estado, `nullptr` para fechar a aplicação, ou um novo estado
 * para transição.
 */
State* SettingsMenu::handle_input(const ALLEGRO_EVENT& ev) {
  
  // Permite fechar a janela.
  if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return nullptr;

  // Trata o evento de pressionar Enter ou Espaço para confirmar uma seleção.
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
       ev.keyboard.keycode == ALLEGRO_KEY_SPACE)) {
    selectSound->playSound(0.3);
    if (menuButtons[buttonPositionSelected].name == "Music") {
      // Alterna o estado global da música.
      g_sound_on = !g_sound_on;

      // Aplica a alteração de volume ao mixer principal da Allegro.
      if (g_sound_on) {
        // Volume normal (1.0f = 100%)
        al_set_mixer_gain(al_get_default_mixer(), 1.0f);
        std::cout << "Música ligada!" << std::endl;
      } else {
        // Mudo (volume 0.0f = 0%)
        al_set_mixer_gain(al_get_default_mixer(), 0.0f);
        std::cout << "Música desligada!" << std::endl;
      }

    } else if (menuButtons[buttonPositionSelected].name == "Day") {
      std::cout << "Clima Dia selecionada!" << std::endl;
      weatherSelected = "Day";
    } else if (menuButtons[buttonPositionSelected].name == "Snow") {
      std::cout << "Clima Neve selecionada!" << std::endl;
      weatherSelected = "Snow";
    } else if (menuButtons[buttonPositionSelected].name == "Rain") {
      std::cout << "Clima Rain selecionada!" << std::endl;
      weatherSelected = "Rain";
    } else if (menuButtons[buttonPositionSelected].name == "Back") {
      std::cout << "Clima " << weatherSelected << " salva!" << std::endl;
      return new MainMenu();
    }
  }

  // Permite retornar ao menu principal com a tecla ESC.
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
      (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
    return new MainMenu();
  }

  // Processa a navegação no menu com as teclas direcionais.
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
    switch (ev.keyboard.keycode) {
      // Navega para o próximo item do menu.
      case ALLEGRO_KEY_DOWN:
      case ALLEGRO_KEY_RIGHT:
        menuButtons[buttonPositionSelected].buttonSelectState = 0;

        if (buttonPositionSelected == 4)
          buttonPositionSelected = 0;
        else
          buttonPositionSelected++;

        menuButtons[buttonPositionSelected].buttonSelectState = 1;
        break;

      // Navega para o item anterior do menu.
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

/**
 * @brief Executa ações ao entrar neste estado.
 * @details Garante que o menu de configurações seja inicializado em um estado visual previsível,
 * com o primeiro botão ("Música") selecionado por padrão.
 */
void SettingsMenu::enter() {
  // Garante que todos os botões comecem como não selecionados.
  for (auto& button : menuButtons) {
    button.buttonSelectState = 0;
  }

  // Define o botão inicial como selecionado.
  buttonPositionSelected = 0;
  menuButtons[buttonPositionSelected].buttonSelectState = 1;
}

/**
 * @brief Atualiza a lógica do estado de movimento/animação de fundo.
 * @param motion Referência ao objeto de controle de movimento/animação do fundo.
 * @return Retorna `this` para indicar a permanência no estado atual.
 */
State* SettingsMenu::update(Motion& motion) {
  motion.update(); // Atualiza a animação de fundo.

  // Define o controlador de clima com base na seleção do usuário.
  if (weatherSelected == "Day") {
    motion.setController(1);
  }
  if (weatherSelected == "Snow") {
    motion.setController(2);
  }
  if (weatherSelected == "Rain") {
    motion.setController(3);
  }
  return this;
}

/**
 * @brief Desenha todos os elementos visuais do estado na tela.
 * @param motion Referência ao objeto de controle de movimento para desenhar o fundo.
 * @details A função renderiza o fundo, os botões e os textos informativos
 * com base no estado atual das configurações (música ligada/desligada, botão selecionado).
 */
void SettingsMenu::draw(Motion& motion) {
  motion.draw(); // Desenha o fundo animado.

  bool is_music_button_selected = menuButtons[0].buttonSelectState;
  bool is_back_button_selected = menuButtons[4].buttonSelectState;

  if (is_music_button_selected) {
    if (g_sound_on)
      campSettingsMusic->Draw();
    else
      campSettingsNoMusic->Draw();
    buttonMusicSelect->Draw();
  }

  if (menuButtons[1].buttonSelectState) {
    if (g_sound_on)
      buttonMusicDaySelect->Draw();
    else
      buttonNoMusicDaySelect->Draw();
  } else if (menuButtons[2].buttonSelectState) {
    if (g_sound_on)
      buttonMusicSnowSelect->Draw();
    else
      buttonNoMusicSnowSelect->Draw();
  } else if (menuButtons[3].buttonSelectState) {
    if (g_sound_on)
      buttonMusicRainSelect->Draw();
    else
      buttonNoMusicRainSelect->Draw();
  }

  if (is_back_button_selected) {
    // Garante que o fundo correto é desenhado mesmo com o botão "Back"
    // selecionado
    if (g_sound_on)
      campSettingsMusic->Draw();
    else
      campSettingsNoMusic->Draw();
    buttonBackSelect->Draw();
  } else {
    buttonBackDeselect->Draw();
  }

  // Desenha o fundo principal se nenhum outro botão de clima o desenhou
  if (!menuButtons[1].buttonSelectState && !menuButtons[2].buttonSelectState &&
      !menuButtons[3].buttonSelectState && !is_music_button_selected &&
      !is_back_button_selected) {
    if (g_sound_on)
      campSettingsMusic->Draw();
    else
      campSettingsNoMusic->Draw();
  }

  // Exibe o texto confirmando a seleção de clima atual.
  if (weatherSelected == "Day")
    font->writeText("Day weather selected!", ALLEGRO_ALIGN_CENTER, 640, 485);
  else if (weatherSelected == "Snow")
    font->writeText("Snow weather selected!", ALLEGRO_ALIGN_CENTER, 640, 485);
  else if (weatherSelected == "Rain")
    font->writeText("Rain weather selected!", ALLEGRO_ALIGN_CENTER, 640, 485);
}
