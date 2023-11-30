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
        int is_showtime_available(int current_hour, int current_minute, int showtime_hour, int showtime_minute) {
            // returns 1 if showtime has not exceeded the current time, 0 if not.
            if (current_hour != showtime_hour) { return current_hour < showtime_hour; }
            else { return current_minute < showtime_minute; }
        }       

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

            cout << "Adding movie";
            for (int i = 0; i < 3; i++) {
                pause(1);
                cout << " . ";
            }

            cout << "\nMovie successfully added! Here's a preview of the movie." << endl;
            cout << "Movie name: " << new_movie.name << endl;
            for (int j = 0; j < new_movie.showtimes.size(); j++) {
                float showtime = new_movie.showtimes[j];
                int showtime_hour = showtime; // typecast into int so it truncuates the fractional part
                int showtime_minute = (showtime - showtime_hour) * 60; // get only the fractional part and multiply with 60 minutes
                cout << "Showtime #" << j + 1 << " - " << setw(2) << setfill('0') << showtime_hour << ":";
                cout << setw(2) << setfill('0') << showtime_minute; // add leading zeros up to 2 digits for the minute display
                string availability = is_showtime_available(now -> tm_hour, now -> tm_min, showtime_hour, showtime_minute) ? "Available" : "Unavailable";
                cout << " | " << availability << endl;
            }
            cout << endl;
        }

        void delete_movie() {
            if (movies.empty()) {
                cout << "No movies to delete." << endl;
                return;
            }

            cout << "Current Movies:" << endl;
            for (size_t i = 0; i < movies.size(); ++i) {
                cout << i + 1 << ". " << movies[i].name << endl;
            }

            cout << "Enter the index of the movie to delete: ";
            size_t index;
            cin >> index;

            if (index > 0 && index <= movies.size()) {
                auto it = movies.begin() + index - 1; // Adjust index to 0-based
                movies.erase(it);

                cout << "Deleting movie";
                for (int i = 0; i < 3; i++) {
                    pause(1);
                    cout << " . ";
                }

                cout << endl << movies[index - 1].name << " successfully deleted." << endl;
            } else {
                cout << "Invalid index. No movie deleted." << endl;
            }
        }

        enum IN { 
            // 13 is ASCII for carriage 
            IN_BACK = 8, 
            IN_RET = 13 
        }; 
        
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

        void pause(int dur) {
        	int temp = time(NULL) + dur;
        	while(temp > time(NULL));
        }

        bool login_page() {
            string username, pwd;
            int tries = 1;
            cout << "Username: ";
            cin >> username;

            cout << "Password: ";
            pwd = password_input();

            while(!(pwd == admin.password && username == admin.name)) {
                cout << "Incorrect password or username. Please try again." << endl;
                
                cout << "Username: ";
                cin >> username;

                cout << "Password: ";
                pwd = password_input();
            }
            cout << "Login successful! Welcome, " << admin.name << endl;
            screen.refresh();
            return 1;
        }

        void start_menu() {
            int login_choice = screen.display_start_menu();
            int maxAttempts;
            int timeoutDuration;  // Changed to int to store seconds
            int attempts;


            while (true) {
                if (login_choice == 1) { // login as admin
                    // screen.refresh();
                    bool login = login_page();
                    if (login) {admin_start_page();}
                    
                } else if (login_choice == 2) { // exit
                    screen.exit_message();
                    exit(0);
                } else {
                    cout << "Invalid option. Please choose again: ";
                    cin >> login_choice;
                }
            }
        }

        bool confirm_purchase() {
            char choice;
            cout << "Do you want to confirm the purchase? (y/n): ";
            cin >> choice;
            return (choice == 'y' || choice == 'Y');
        }

        void order_tickets() {
            int selected_movie;
            int selected_theatre;
            int selected_showtime;
            int ticket_amount;
            stack<string> movie_stack;
            stack<string> location_stack;
            stack<float> showtime_stack;

            screen.display_all_movies(movies);
            cout << "Select a movie by number: ";
            cin >> selected_movie;
            while (selected_movie < 0 || selected_movie > movies.size()) {
                cout << "Invalid movie number! Please select another movie: ";
                cin >> selected_movie;
            }
            movie_stack.push(movies[selected_movie - 1].name);
            cout << movies[selected_movie - 1].name << " was selected!" << endl << endl;

            screen.display_all_theatres(theatres);
            cout << "Select a theatre by number: ";
            cin >> selected_theatre;
            while (selected_theatre < 0 || selected_theatre > theatres.size()) {
                cout << "Invalid theatre! Please select another movie: ";
                cin >> selected_theatre;
            }
            location_stack.push(theatres[selected_theatre - 1].name);
            cout << theatres[selected_theatre - 1].name << " was selected!" << endl << endl;

            screen.display_showtimes(movies, selected_movie - 1, now);
            cout << "Select a showtime by number: ";
            cin >> selected_showtime;

            float showtime = movies[selected_movie - 1].showtimes[selected_showtime - 1];
            int showtime_hour = showtime; // typecast into int so it truncuates the fractional part
            int showtime_minute = (showtime - showtime_hour) * 60; // get only the fractional part and multiply with 60 minutes
            while ((selected_showtime < 0 || selected_showtime > movies[selected_movie - 1].showtimes.size()) || !is_showtime_available(now -> tm_hour, now -> tm_min, showtime_hour, showtime_minute)) {
                // cout << !is_showtime_available(now -> tm_hour, now -> tm_min, showtime_hour, showtime_minute) << endl;
                cout << "Invalid showtime! Please select another showtime: ";
                cin >> selected_showtime;

                showtime = movies[selected_movie - 1].showtimes[selected_showtime - 1];
                showtime_hour = showtime; // typecast into int so it truncuates the fractional part
                showtime_minute = (showtime - showtime_hour) * 60; // get only the fractional part and multiply with 60 minutes
            }
            showtime_stack.push(showtime);
            screen.convert_to_showtime(showtime);
            cout << " was selected!" << endl << endl;

            cout << "How many tickets would you like to order (max. 8)? ";
            cin >> ticket_amount;
            while (ticket_amount <= 0 || ticket_amount > 8) {
                cout << "Invalid number of tickets. Please enter a number between 1 and 8: ";
                cin >> ticket_amount;
            }
            cout << ticket_amount << " ticket(s) have been ordered!" << endl << endl;

            process_order(ticket_amount, movies, movies[selected_movie - 1].showtimes[selected_showtime - 1], theatres[selected_theatre - 1].name, movies[selected_movie - 1].name, selected_movie - 1, selected_theatre - 1);
        }

        void process_order(int amount, vector<Movie> movies, float showtime, string theatre, string movie, int movie_index, int theatre_index) {
            while (amount <= 0 || amount > 8) {
                cout << "Invalid number of tickets. Please enter a number between 1 and 8: ";
                cin >> amount;
            }

            movies[movie_index].movie_tickets_sold[theatre] += amount;
            theatres[theatre_index].theatre_tickets_sold[movie] += amount;

            cout << "-- Review your purchase --\n";
            cout << "Movie: " << movies[movie_index].name << endl;
            cout << "Location: " << theatre << endl;
            cout << "Time: "; screen.convert_to_showtime(showtime); cout << endl;
            cout << "Amount: " << amount << " tickets\n\n";

            if (confirm_purchase()) {
                cout << "Processing order";
                for (int i = 0; i < 3; i++) {
                    pause(1);
                    cout << " . ";
                }
                cout << endl << "Purchase confirmed!\n";
            } else {
                // Discard the selected options
                movies[movie_index].movie_tickets_sold[theatre] -= amount;
                theatres[theatre_index].theatre_tickets_sold[movie] -= amount;
                cout << "Purchase canceled. Selected options discarded.\n";
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
                
                case 3: // order a movie
                    order_tickets();

                    system("PAUSE");
                    screen.refresh();
                    screen.admin_header();
                    screen.view_admin_options();
                    cin >> admin_choice;

                    break;

                case 4: // add a mew movie
                    add_movie();
                    
                    system("PAUSE");
                    screen.refresh();
                    screen.admin_header();
                    screen.view_admin_options();
                    cin >> admin_choice;

                    break;

                case 5: // Delete a mew movie
                    delete_movie();

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
            screen.refresh();
            screen.welcome();
            screen.display_current_time(time(0));
            start_menu();
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
        User admin = {"admin", "admin123"};
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

    sys.start_menu();
    
}
