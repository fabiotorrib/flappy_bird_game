#include "../../include/states/main_menu.hpp"
#include <allegro5/allegro_primitives.h>   // usado nesse exemplo aqui
#include "../../include/states/states.hpp" //necessario para modificar o objeto play (ou qualquer outro)
#include "../../include/init.hpp"
#include <string>
#include <map>
#include <vector>
#include "../../include/defines.hpp"


ScreenState MainMenu::loop()
{
    // aqui sao implementados os eventos de teclado e mouse
    while (al_get_next_event(queue, &ev))
    {
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            return ScreenState::EXIT;

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
            (ev.keyboard.keycode == ALLEGRO_KEY_ENTER || ev.keyboard.keycode == ALLEGRO_KEY_SPACE))
        {
            if (menuButtons[buttonPositionSelected].name == "NewGame")
            {
                std::cerr << "Botão NewGame selecionado!" << std::endl;
            }
            else if (menuButtons[buttonPositionSelected].name == "LoadGame")
            {
                std::cerr << "Botão LoadGame selecionado!" << std::endl;
            }
            else if (menuButtons[buttonPositionSelected].name == "Settings")
            {
                std::cerr << "Botão Settings selecionado!" << std::endl;
            }
            else if (menuButtons[buttonPositionSelected].name == "Difficulty")
            {
                std::cerr << "Botão Difficulty selecionado!" << std::endl;
            }
            else if (menuButtons[buttonPositionSelected].name == "Leaderboard")
            {
                std::cerr << "Botão Leaderboard selecionado!" << std::endl;
            }
            else if (menuButtons[buttonPositionSelected].name == "Exit")
            {
                std::cerr << "Botão Exit selecionado!" << std::endl;
                return ScreenState::EXIT;
            }
            // reseta antes de começar a partida
            // play.reset();
            // return ScreenState::PLAY;
        }

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
            ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
        {
            menuButtons[buttonPositionSelected].buttonSelectState = 0;

            if (buttonPositionSelected == 5)
                buttonPositionSelected = 0;
            else
                buttonPositionSelected++;

            menuButtons[buttonPositionSelected].buttonSelectState = 1;
        }
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
            ev.keyboard.keycode == ALLEGRO_KEY_UP)
        {
            menuButtons[buttonPositionSelected].buttonSelectState = 0;

            if (buttonPositionSelected == 0)
                buttonPositionSelected = 5;
            else
                buttonPositionSelected--;

            menuButtons[buttonPositionSelected].buttonSelectState = 1;
        }
    }

    // aqui sao implementados as partes visuais
    // Desenha o background
    al_draw_bitmap(background, 0, 0, 0);
    // Desenha a logo
    al_draw_bitmap(logoNormal, 346.5, 100, 0);
    // Desenha o botão NewGame
    if (menuButtons[0].buttonSelectState)
        al_draw_bitmap(buttonNewGameSelect, 496.5, 300, 0);
    else
        al_draw_bitmap(buttonNewGameDeselect, 496.5, 300, 0);

    // Desenha o botão LoadGame
    if (!menuButtons[1].buttonSelectState)
        al_draw_bitmap(buttonLoadGameSelect, 496.5, 370, 0);
    else
        al_draw_bitmap(buttonLoadGameDeselect, 496.5, 370, 0);

    // Desenha o botão Settings
    if (!menuButtons[2].buttonSelectState)
        al_draw_bitmap(buttonSettingsSelect, 496.5, 440, 0);
    else
        al_draw_bitmap(buttonSettingsDeselect, 496.5, 440, 0);

    // Desenha o botão Difficulty
    if (!menuButtons[3].buttonSelectState)
        al_draw_bitmap(buttonDifficultySelect, 496.5, 510, 0);
    else
        al_draw_bitmap(buttonDifficultyDeselect, 496.5, 510, 0);

    // Desenha o botão Leaderboard
    if (!menuButtons[4].buttonSelectState)
        al_draw_bitmap(buttonLeaderboardSelect, 496.5, 580, 0);
    else
        al_draw_bitmap(buttonLeaderboardDeselect, 496.5, 580, 0);

    // Desenha o botão Exit
    if (!menuButtons[5].buttonSelectState)
        al_draw_bitmap(buttonExitSelect, 496.5, 650, 0);
    else
        al_draw_bitmap(buttonExitDeselect, 496.5, 650, 0);

    // esse eh o update
    al_flip_display();
    return ScreenState::MAIN_MENU;
}
