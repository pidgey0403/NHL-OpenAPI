/*
Author: Gabrielle Niamat
Description: Implementation of Request class. Responsible for calling to the NHL's Open Data API and returning a response.
Date: Feb 6, 2023
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "request.hpp"

using namespace std;

struct MemoryStruct
{
    char *memory;
    size_t size;
};

/*
Name: WriteMemoryCallback method
Description: Shows how the write callback function can be used to download data into a chunk of memory instead of storing it in a file
Parameters: void *contents: contents to add, size_t size: size of a member, size_t nmemb: number of members, void*userp: pointer to memory to write to
Return: the size of contents in total
*/
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr)
    {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

/*
Name: Request class constructor
Description: The constructor for the Request class. Sets url data member to the given url endpoint.
Parameters: string givenURL: cpp string for the API endpoint to parse
Return: None
*/
Request::Request(string givenURL)
{
    char *cstr = new char[givenURL.length() + 1];
    url = strcpy(cstr, givenURL.c_str());
};

/*
Name: Request class destructor
Description: The constructor for the Request class. Deallocates used memory by the class.
Parameters: None
Return: None
*/
Request::~Request(){};

/*
Name: Execute method for Request class
Description: The execute method for the Request class. Retrieves document using from the URL endpoint.
Parameters: None
Return: Boolean; true if successful retrieval of data, false otherwise
*/
bool Request::execute()
{
    CURL *curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;

    chunk.memory = (char *)malloc(1); /* will be grown as needed by the realloc above */
    chunk.size = 0;                   /* no data at this point */

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* specify URL to get */
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);

    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

    /* some servers do not like requests that are made without a user-agent
        field, so we provide one */
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    /* get it! */
    res = curl_easy_perform(curl_handle);

    /* check for errors */
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        return false;
    }
    else
    {
        // chunk.memory points to a memory block that is chunk.size bytes
        jsonString = chunk.memory;
        return true;
    }

    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);

    free(chunk.memory);

    /* we are done with libcurl, so clean it up */
    curl_global_cleanup();
};

/*
Name: Result method for Request class
Description: The result method for the Request class. Returns a string object containing the JSON data retrieved from the API request.
Parameters: None
Return: None
*/
string Request::result()
{
    // return result of JSON data from the request
    return jsonString;
};