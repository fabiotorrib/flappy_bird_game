#pragma once

#include "../include/init.hpp"

using namespace std;

class Player {
private:
    string name;
    int score;

public:
    Player(string name); //construtor

    //getters e setters
    string GetName();
    int GetScore();
    void SetScore(int points);

    static vector<Player> ReadLeaderboard(string file_name);
    static void SortLeaderboard(vector<Player>& ranking);
    static void SaveLeaderboard(string fileName, vector<Player>& ranking);
    static void ShowLeaderboard(vector<Player>& ranking, ALLEGRO_FONT* font);
    bool operator<(const Player& other_p); //sobrecarga do operador <
};
