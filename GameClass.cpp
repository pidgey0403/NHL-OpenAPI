#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.hpp"

#include "ApiClass.hpp"

using namespace std;
using json = nlohmann::json;

class Game
{
    json gameDictionary = {};
    int homeScore;
    int awayScore;
    string homeName;
    string awayName;

public:
    Game(){}; // constructor

    ~Game(){}; // destructor

    void setHomeScore(int score)
    {
        gameDictionary["homeScore"] = score;
        homeScore = score;
    }

    void setAwayScore(int score)
    {
        gameDictionary["awayScore"] = score;
        awayScore = score;
    }

    void setHomeName(const string &name)
    {
        gameDictionary["homeName"] = name;
        homeName = name;
    }

    void setAwayName(const string &name)
    {
        gameDictionary["awayName"] = name;
        awayName = name;
    }

    void printGame()
    {
        cout << homeName << " vs. " + awayName << " : " << homeScore << " - " << awayScore << endl;
    }

    json getJSONObj()
    {
        return gameDictionary;
    }
};

// to be transplanted to main.cpp file -> essentially done, just need to loop through all the JSON data returned by "data" and create a vector of answer objects
// will need to clean up a bit to add appropriate * and &, and const declarations on some methods
int main()
{
    string endpoint = "https://statsapi.web.nhl.com/api/v1/schedule?season=20222023&gameType=R";
    Request req(endpoint);
    req.execute();
    string temp = req.result();
    json data = json::parse(temp);

    Game game;
    game.setAwayScore(1);
    game.setHomeScore(5);
    game.setAwayName("Gonzaga");
    game.setHomeName("Fraser");
    game.printGame();

    return 0;
}
