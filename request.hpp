/*
Author: Gabrielle Niamat
Description: Implementation of Game Class. Responsible for populating a JSON object representing a game match.
Date: Feb 6, 2023
*/

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request
{
private:
    char *url;
    std::string jsonString;

public:
    Request(std::string givenURL);
    ~Request();
    bool execute();
    std::string result();
};

#endif // REQUEST_H