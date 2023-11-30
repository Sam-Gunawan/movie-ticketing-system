#ifndef UI_H
#define UI_H

#include "Movie.h"
using namespace std;

class UI {
    public:
        void welcome();
        void refresh();
        string multiply_string(string str, int n);
        void display_current_time(time_t current_time);
        int display_start_menu();
        void admin_header();
        void display_all_movies(vector<Movie> movies);
        void display_all_theatres(vector<Theatres> theatres);
        void view_admin_options();
        void exit_message();
        void display_showtimes(vector<Movie> movies, int movie_index, tm* now);
        void convert_to_showtime(float showtime);
        bool is_showtime_available(int current_hour, int current_minute, int showtime_hour, int showtime_minute);
};

#endif