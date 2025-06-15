#pragma once
#include "../motion.hpp"

#include "difficulty_menu.hpp"
#include "leaderboard.hpp"
#include "load_game.hpp"
#include "main_menu.hpp"
#include "play.hpp"

// criando e distribuindo os objetos globais de cada estado
inline MainMenu mainMenu;
inline Play play;
inline LoadName loadName;
inline Motion motion;
inline DifficultyMenu difficultyMenu;
inline LeaderboardMenu leaderboardMenu;
