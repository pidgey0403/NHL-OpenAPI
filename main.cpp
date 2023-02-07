/*
Author: Gabrielle Niamat
Description: Main function. Responsible for driving the program by calling the Game class and Request class.
Date: Feb 6, 2023
*/

#include <iostream>
#include <vector>
#include "json.hpp"
#include "request.hpp"
#include "game.hpp"

using namespace std;
using json = nlohmann::json;

/*
Name: Program main function
Description: The driver function responsible for calling the request class and game class and printing out all match data fetched by the API.
Parameters: None
Return: None
*/
int main()
{
    Request request("https://statsapi.web.nhl.com/api/v1/schedule?season=20222023&gameType=R");
    if (!request.execute())
    {
        return 1;
    }
    string result = request.result();             // get raw data from API request
    json data = json::parse(result);              // parse json data
    vector<Game> gamesVector(data["totalGames"]); // allocating enough space for all games of the season
    int i = 0;                                    // control index in gamesVector
    for (const auto &date : data["dates"])
    {
        for (const auto &game : date["games"])
        {
            if (game["status"]["codedGameState"] != "7")
            {
                continue; // continue while match score isn't the final one
            }

            // populate the home and away teams with the appropriate name or score data
            json awayGame = game["teams"]["away"];
            gamesVector[i].setAwayName(awayGame["team"]["name"]);
            gamesVector[i].setAwayScore(awayGame["score"]);

            json homeGame = game["teams"]["home"];
            gamesVector[i].setHomeName(homeGame["team"]["name"]);
            gamesVector[i].setHomeScore(homeGame["score"]);

            i++;
        }
    }

    // iterate through game vector and print every game
    for (Game &game : gamesVector)
    {
        game.printGame();
    }
};