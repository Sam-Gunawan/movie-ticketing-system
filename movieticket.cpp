#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <vector>

#include "UI.h"
#include "Movie.h"

using namespace std;

void UI::welcome() {
    cout << "+------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                                                                          |" << endl;
    cout << "|                                                                                          |" << endl;
    cout << "|    ___       __   _______   ___       ________  ________  _____ ______   _______         |" << endl;
    cout << "|   |\\  \\     |\\  \\|\\  ___ \\ |\\  \\     |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\        |" << endl;
    cout << "|   \\ \\  \\    \\ \\  \\ \\   __/|\\ \\  \\    \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|       |" << endl;
    cout << "|    \\ \\  \\  __\\ \\  \\ \\  \\_|/_\\ \\  \\    \\ \\  \\    \\ \\  \\\\\\  \\ \\  \\\\|__| \\  \\ \\  \\_|/__     |" << endl;
    cout << "|     \\ \\  \\|\\__\\_\\  \\ \\  \\_|\\ \\ \\  \\____\\ \\  \\____\\ \\  \\\\\\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\    |" << endl;
    cout << "|      \\ \\____________\\ \\_______\\ \\_______\\ \\_______\\ \\_______\\ \\__\\    \\ \\__\\ \\_______\\   |" << endl;
    cout << "|       \\|____________|\\|_______|\\|_______|\\|_______|\\|_______|\\|__|     \\|__|\\|_______|   |" << endl;
    cout << "|                                                                                          |" << endl;
    cout << "|                                                                                          |" << endl;
    cout << "|                                                                                          |" << endl;
    cout << "+------------------------------------------------------------------------------------------+" << endl << endl;
}
    
void UI::refresh() {
    cout.flush();
    system("CLS");
}

string UI::multiply_string(string str, int n) {
    // This function is to reiterate strings n amount of times
    string result = "";
    for (int i = 0; i < n; i++) {
        result += str;        
    }
    return result;
}

void UI::display_current_time(time_t current_time) {
    // The display is in day, dd month yyyy, hh:mm format
    // To make the date and time always centered in the 'box', we need to calculate the distance so that it can be dyanmic and adjust according to the length of the different months

    tm* now = localtime(&current_time); // convert the time_t data type into tm structure for ease of calculation and comparation

    // NOTE: to review more about ctime, go here: https://www.javatpoint.com/cpp-date-and-time

    const string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    const string days[8] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday"};

    string day = days[(now -> tm_mday) % 7 + 1];
    string month = months[(now -> tm_mon)];
    int year = (now -> tm_year) + 1900; // ctime counts from 1900

    string display = "";
    display += day; display += ", ";
    display += to_string(now -> tm_mday); display += " ";
    display += month; display += " ";
    display += to_string(year); display += ", ";
    display += (now -> tm_hour < 10 ? "0" : "") + to_string(now -> tm_hour); display += ":";
    display += (now -> tm_min < 10 ? "0" : "") + to_string(now -> tm_min);

    int display_length = display.length();

    cout << "+" << multiply_string("-", display_length + 6) << "+" << endl;
    // cout << "|" << multiply_string(" ", display_length + 6) << "|" << endl;
    cout << "|   " << display << "   |" << endl;
    // cout << "|" << multiply_string(" ", display_length + 6) << "|" << endl;
    cout << "+" << multiply_string("-", display_length + 6) << "+" << endl << endl;
}

int UI::display_start_menu() {
    int choice;
    cout << "Welcome to Nonton Kuy!" << endl;
    cout << "1. Login" << endl;
    cout << "2. Sign up" << endl;
    cout << "3. Exit Nonton Kuy" << endl;
    cout << "Select an option: ";
    cin >> choice;
    return choice;
}

void UI::exit_message() {
    
}

void UI::admin_header() {
    cout << "+---------------------------------+" << endl;
    cout << "|    You're logged in as ADMIN    |" << endl;
    cout << "+---------------------------------+" << endl << endl;
    display_current_time(time(0));
}

void UI::view_admin_options() {
    cout << "Available options:" << endl;
    cout << "1. Show all movies" << endl;
    cout << "2. Show all theatres" << endl;
    cout << "3. Add a new movie" << endl;
    cout << "4. Delete a movie" << endl;
    cout << "5. Show sales summary" << endl;
    cout << "6. Logout" << endl << endl;

    cout << "Select an option: ";

}

void UI::display_all_movies(vector<Movie> movies) {
    for (int i = 0; i < movies.size(); i++) {
        cout << i + 1 << ". " << movies[i].name << endl;
    }
    cout << endl;
}

void UI::display_all_theatres(vector<Theatres> theatres) {
    for (int i = 0; i < theatres.size(); i++) {
        cout << i + 1 << ". " << theatres[i].name << endl;
    }
    cout << endl;
}

// float showtime;
// int showtime_hour, showtime_minute;
// int count = 1;
// for (int i = 0; i < movies.size(); i++) {
//     for (int j = 0; j < movies[i].showtimes.size(); j++) {
//         showtime = movies[i].showtimes[j];
//         showtime_hour = showtime; // typecast into int so it truncuates the fractional part
//         showtime_minute = (showtime - showtime_hour) * 60; // get only the fractional part and multiply with 60 minutes
//         cout << movies[i].name << " " << showtime_hour << ":";
//         cout << setw(2) << setfill('0') << showtime_minute; // add leading zeros up to 2 digits for the minute display
//         cout << " | The showtime availablity: " << IsShowtimeAvailable(now -> tm_hour, now -> tm_min, showtime_hour, showtime_minute) << endl;       
//     }
// }
