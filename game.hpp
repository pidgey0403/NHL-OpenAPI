/*
Author: Gabrielle Niamat
Description: Game class header file. Responsible for defining the Game Class, member variables, and methods.
Date: Feb 6, 2023
*/

#ifndef GAME_H
#define GAME_H

#include <string.h>
#include "json.hpp"

class Game
{
private:
    nlohmann::json gameDictionary;
    int homeScore;
    int awayScore;
    std::string homeName;
    std::string awayName;

public:
    Game();

    ~Game();

    void setHomeScore(int score);

    void setAwayScore(int score);

    void setHomeName(const std::string &name);

    void setAwayName(const std::string &name);

    void printGame();

    nlohmann::json getJSONObj();
};

#endif // GAME_H