/*
Author: Gabrielle Niamat
Description: Implementation of Game class. Responsible for populating a JSON object representing a game match.
Date: Feb 6, 2023
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.hpp"

#include "request.hpp"
#include "game.hpp"

using namespace std;
using json = nlohmann::json;

/*
Name: Game constructor
Description: The Game class's constructor method
Parameters: None
Return: None
*/
Game::Game();

/*
Name: Game destructor
Description: The Game class's destructor method. Allows deallocation of used memory.
Parameters: None
Return: None
*/
Game::~Game();

/*
Name: setHomeScore method
Description: The Game class's setHomeScore method. Takes in an integer value and populates JSON object and class variable.
Parameters: int score: a number representing the home team's final score
Return: Void
*/
void Game::setHomeScore(int score)
{
    // populate appropriate field in dictionary
    gameDictionary["homeScore"] = score;
    homeScore = score;
};

/*
Name: setAwayScore method
Description: The Game class's setAwayScore method. Takes in an integer value and populates JSON object and class variable.
Parameters: int score: a number representing the away team's final score
Return: Void
*/
void Game::setAwayScore(int score)
{
    gameDictionary["awayScore"] = score;
    awayScore = score;
};

/*
Name: setHomeName method
Description: The Game class's setHomeName method. Takes in an string memory address and populates JSON object and class variable.
Parameters: const string &name: a string representing the home team's name
Return: Void
*/
void Game::setHomeName(const string &name)
{
    gameDictionary["homeName"] = name;
    homeName = name;
};

/*
Name: setAwayName method
Description: The Game class's setAwayName method. Takes in an string memory address and populates JSON object and class variable.
Parameters: const string &name: a string representing the away team's name
Return: Void
*/
void Game::setAwayName(const string &name)
{
    gameDictionary["awayName"] = name;
    awayName = name;
};

/*
Name: printGame method
Description: The Game class's printGame method. Verifies that all 4 match variables have been initialized and then prints out the match data.
Parameters: None
Return: Void
*/
void Game::printGame()
{
    // check if all data variables have been initialized
    if (homeName != "" && awayName != "" && homeScore != -1 && awayScore != -1)
    {
        cout << homeName << " vs. " + awayName << " : " << homeScore << " - " << awayScore << endl;
    }
};

/*
Name: getJSONObj method
Description: The Game class's getJSONObj method. Returns the populated JSON object containing all 4 data fields.
Parameters: None
Return: json object
*/
json Game::getJSONObj()
{
    return gameDictionary;
};