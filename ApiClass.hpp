#ifndef API_CLASS_H
#define API_CLASS_H

#include <string>
using namespace std;

class Request
{
    // private member variables
    char *url;
    string jsonString;

public:
    Request(string givenURL); // constructor
    ~Request();
    bool execute();  // member method
    string result(); // member method
};

#endif // API_CLASS_H