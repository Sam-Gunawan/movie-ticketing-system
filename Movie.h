#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>
#include <map>

using namespace std;

struct Movie {
    string name;
    vector<float> showtimes; // showtimes will be stored in float so that it can store the hours and the minutes. 
    map<string, int> movie_tickets_sold;
};

struct Theatres {
    string name;
    map<string, int> theatre_tickets_sold;
};

struct User {
    string name;
    string password;
    map<string, int> purchase_history; // to store each user's ticket purchases and their corresponding movie
};

#endif