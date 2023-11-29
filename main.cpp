#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include <stack>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
#include <conio.h>

#include "UI.cpp"
#include "Linkedlist.cpp"
#include "MiscellaneousFunctions.cpp"
#include "Movie.h"

using namespace std;

class TicketingSystem {
    public:        
        int contains_alpha(string var) {
            for (int i = 0; i < var.length(); i++) {
                if (isalpha(var[i])) {
                    return 1;
                }
            }
            return 0;
        }

        void add_movie() {
            Movie new_movie;
            vector<float> showtimes;
            string new_showtime = "-1"; // accept showtime input as string first so that we can validate it before converting to float
            string new_movie_name;

            cout << "Enter the movie name: ";
            cin.ignore();
            getline(cin, new_movie_name);

            cout << "Set the showtiems for " << new_movie_name << ". Enter '-1' to finish." << endl;
            counter = 1;
            while ((counter <= 1 && new_showtime == "-1") || new_showtime != "-1") {
                cout << "Enter showtime " << counter << " (in 24-hour format): ";
                cin >> new_showtime;
                if (contains_alpha(new_showtime)) {
                    cout << "Invalid input! Enter in 24-hour format (e.g. 12.5 represents 12:30 PM)." << endl;
                    continue;
                }
                if ((stof(new_showtime) < 0 && new_showtime != "-1") || stof(new_showtime) > 24) {
                    cout << "Invalid input! Showtimes are only valid from 0 - 24." << endl;
                    continue;
                }
                if (counter <= 1 && new_showtime == "-1") {
                    cout << "Invalid! You have to enter at least one showtime." << endl;
                    continue;
                }
                vector<float>::iterator is_duplicate;
                is_duplicate = find(showtimes.begin(), showtimes.end(), stof(new_showtime));
                if (is_duplicate != showtimes.end()) {
                    cout << "Duplicate found! There is already a showtime at " << new_showtime << "." << endl;
                    continue;
                }
                if (new_showtime == "-1") {
                    break;
                }
                counter++;
                showtimes.push_back(stof(new_showtime)); // stof() - string to float
            }

            sort(showtimes.begin(), showtimes.end()); // sort the showtimes from earliest to latest

            new_movie.name = new_movie_name;
            new_movie.showtimes = showtimes;

            movies.push_back(new_movie);

            cout << "Movie successfully added! Here's a preview of the movie." << endl;
            cout << "Movie name: " << new_movie.name << endl;
            for (int j = 0; j < new_movie.showtimes.size(); j++) {
                float showtime = new_movie.showtimes[j];
                int showtime_hour = showtime; // typecast into int so it truncuates the fractional part
                int showtime_minute = (showtime - showtime_hour) * 60; // get only the fractional part and multiply with 60 minutes
                cout << "Showtime #" << j + 1 << " - " << setw(2) << setfill('0') << showtime_hour << ":";
                cout << setw(2) << setfill('0') << showtime_minute; // add leading zeros up to 2 digits for the minute display
                cout << " | The showtime availablity: " << IsShowtimeAvailable(now -> tm_hour, now -> tm_min, showtime_hour, showtime_minute) << endl;       
            }
            cout << endl;
        }

        // Enumerator 
        enum IN { 
            // 13 is ASCII for carriage 
            IN_BACK = 8, 
            IN_RET = 13 
        }; 
        
        // Function that accepts the password 
        string password_input(char sp = '*') { 
            // Stores the password 
            string passwd = ""; 
            char ch_ipt; 
        
            // Until condition is true 
            while (true) { 
                ch_ipt = getch(); 
        
                // if the ch_ipt 
                if (ch_ipt == IN::IN_RET) { 
                    cout << endl; 
                    return passwd; 
                } 
                else if (ch_ipt == IN::IN_BACK && passwd.length() != 0) { 
                    passwd.pop_back(); 
        
                    // Cout statement is very important as it will erase previously printed character 
                    cout << "\b \b"; 
                    continue; 
                } 
        
                // Without using this, program will crash as \b can't be print in beginning of line 
                else if (ch_ipt == IN::IN_BACK && passwd.length() == 0) { 
                    continue; 
                } 
        
                passwd.push_back(ch_ipt); 
                cout << sp;
            }
        }

        int login_page() {
            string username, pwd;
            cout << "Username: ";
            cin.ignore();
            getline(cin, username);
        }

        void start_menu() {
            int login_choice = screen.display_start_menu();

            while (true) {
                if (login_choice == 1) { // login
                    screen.refresh();
                    int user = login_page();
                    if (user) {admin_start_page();}
                    else {user_start_page();}
                } else if (login_choice == 2) { // sign up
                    break;
                } else if (login_choice == 3) { // exit
                    screen.exit_message();
                    exit(0);
                } else {
                    cout << "Invalid option. Please choose again: ";
                    cin >> login_choice;
                }
            }
        }

        void admin_start_page() {
            int admin_choice;
            screen.admin_header();
            screen.view_admin_options();
            cin >> admin_choice;

            while (admin_choice != 6) {
                switch (admin_choice) {
                case 1: // Show all movies
                    screen.display_all_movies(movies);

                    system("PAUSE");
                    screen.refresh();
                    screen.admin_header();
                    screen.view_admin_options();
                    cin >> admin_choice;

                    break;

                case 2: // Show all theatres
                    screen.display_all_theatres(theatres);

                    system("PAUSE");
                    screen.refresh();
                    screen.admin_header();
                    screen.view_admin_options();
                    cin >> admin_choice;

                    break;
                
                case 3: // Add a mew movie
                    add_movie();

                    system("PAUSE");
                    screen.refresh();
                    screen.admin_header();
                    screen.view_admin_options();
                    cin >> admin_choice;

                    break;
                
                default:
                    cout << "Invalid option! Choose another option." << endl;
                    screen.view_admin_options();
                    cin >> admin_choice;
                    break;
                }
            }

            start_menu();
        }
        
        void user_start_page() {

        }
    private:
        UI screen;
        vector<Movie> movies = {
            {"Dune", {10, 14, 18.25, 24}},
            {"The Godfather", {11.5, 15, 19, 24}},
            {"Gran Turismo", {12, 16, 20.25, 24}},
            {"Avengers", {13, 16.5, 21, 24}},
            {"Hunger Games", {14.5, 18, 20.75, 24}},
        };
        vector<Theatres> theatres = {
            {"Kota Kasablanka"}, 
            {"Kalibata City"}, 
            {"Gandaria City"}, 
            {"Mall Kelapa Gading"}
        };
        time_t current_time = time(0);
        tm* now = localtime(&current_time);
        int counter;
        const string admin_info[2] = {"admin", "admin123"};
        vector<User> users = {
            {"Jorel", "Halo123!"},
            {"Calvin", "Hola321!"},
            {"Sam", "Testing123!"}
        };
};

class Admin {

};

class User {

};

int main() {
    time_t current_time = time(0); // get current date and time
    tm* now = localtime(&current_time); // convert to tm structure

    int showtime_hour, showtime_minute;
    float showtime;

    UI screen;
    TicketingSystem sys;

    screen.welcome();
    screen.display_current_time(current_time);
    // system("PAUSE");
    // screen.refresh();
    // cout << "Refreshed!" << endl;

    sys.start_menu();
    
}
