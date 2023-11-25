#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>

using namespace std;

struct Movie {
    string name;
    vector<string> showtimes;
    map<string, int> ticketsSold;
};

struct ListNode {
    string name;
    int totalTickets;
    ListNode* next;

    ListNode(const string& n, int tickets) : name(n), totalTickets(tickets), next(nullptr) {}
};

class LinkedList {
public:
    ListNode* head;

    LinkedList() : head(nullptr) {}

    void insert(const string& name, int totalTickets) {
        ListNode* newNode = new ListNode(name, totalTickets);
        if (!head || totalTickets > head->totalTickets) {
            newNode->next = head;
            head = newNode;
        } else {
            ListNode* current = head;
            while (current->next && totalTickets <= current->next->totalTickets) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void display() {
        ListNode* current = head;
        while (current) {
            cout << current->name << ": " << current->totalTickets << " tickets\n";
            current = current->next;
        }
    }
};

class MovieTicketSystem {
public:
    stack<string> movieStack;
    stack<string> locationStack;
    stack<string> showtimeStack;

    void displayMovieMenu() {
        cout << "1. Movie Selection\n";
        cout << "2. Location Selection\n";
        cout << "3. View Sales Summary\n";
        cout << "0. Exit\n";
    }

    void displayBackOption() {
        cout << movies.size() + 1 << ". Previous Page\n";
    }

    void displaySelectionOptions() {
        cout << "1. Movie Selection\n";
        cout << "2. Location Selection\n";
        cout << "3. View Sales Summary\n";
        cout << "0. Exit\n";
    }

    void displayMovies() {
        cout << "Select a movie:\n";
        for (size_t i = 0; i < movies.size(); ++i) {
            cout << i + 1 << ". " << movies[i].name << endl;
        }
        displayBackOption();
    }

    void displayLocations() {
        cout << "Select a location:\n";
        cout << "1. Kalibata\n";
        cout << "2. Kelapa Gading\n";
        cout << "3. Bekasi\n";
        displayBackOption();
    }

    void displayShowtimes(const Movie& movie, const string& location) {
        cout << "Select a showtime for " << movie.name << " at " << location << ":\n";
        for (size_t i = 0; i < movie.showtimes.size(); ++i) {
            cout << i + 1 << ". " << movie.showtimes[i] << endl;
        }
        displayBackOption();
    }

    void displaySalesSummary() {
        cout << "Sales Summary:\n";

        // Create lists to store sorted movies and locations
        LinkedList movieList, locationList;

        for (const Movie& movie : movies) {
            int totalTickets = getTotalTicketsSold(movie);

            // Insert into the sorted linked list
            movieList.insert(movie.name, totalTickets);

            // Insert locations into the sorted linked list
            for (const auto& entry : movie.ticketsSold) {
                locationList.insert(entry.first, entry.second);
            }
        }

        // Display sorted movie list
        cout << "Movies:\n";
        movieList.display();

        // Display sorted location list
        cout << "\nLocations:\n";
        locationList.display();
    }

    int getTotalTicketsSold(const Movie& movie) const {
        int totalTickets = 0;
        for (const auto& entry : movie.ticketsSold) {
            totalTickets += entry.second;
        }
        return totalTickets;
    }

    void processOrder(int amount, Movie& movie, const string& showtime, const string& location) {
        movie.ticketsSold[location] += amount;

        cout << "Preview:\n";
        cout << "Movie: " << movie.name << endl;
        cout << "Location: " << location << endl;
        cout << "Time: " << showtime << endl;
        cout << "Amount: " << amount << " tickets\n";
    }

    void navigateBack() {
        cout << "Previous Selections:\n";
        if (!movieStack.empty()) {
            cout << "Movie: " << movieStack.top() << endl;
        }
        if (!locationStack.empty()) {
            cout << "Location: " << locationStack.top() << endl;
        }
        if (!showtimeStack.empty()) {
            cout << "Showtime: " << showtimeStack.top() << endl;
        }
    }

    void run() {
        int userChoice;
        int amount;

        do {
            displayMovieMenu();
            cin >> userChoice;

            switch (userChoice) {
                case 1:
                    displayMovies();
                    cin >> userChoice;
                    if (userChoice >= 1 && userChoice <= movies.size()) {
                        Movie& selectedMovie = movies[userChoice - 1];
                        movieStack.push(selectedMovie.name);

                        displayLocations();
                        cin >> userChoice;
                        if (userChoice >= 1 && userChoice <= 3) {
                            string selectedLocation;
                            switch (userChoice) {
                                case 1:
                                    selectedLocation = "Kalibata";
                                    break;
                                case 2:
                                    selectedLocation = "Kelapa Gading";
                                    break;
                                case 3:
                                    selectedLocation = "Bekasi";
                                    break;
                            }
                            locationStack.push(selectedLocation);

                            displayShowtimes(selectedMovie, selectedLocation);
                            cin >> userChoice;
                            if (userChoice >= 1 && userChoice <= selectedMovie.showtimes.size()) {
                                string selectedShowtime = selectedMovie.showtimes[userChoice - 1];
                                showtimeStack.push(selectedShowtime);

                                cout << "Enter the number of tickets: ";
                                cin >> amount;
                                processOrder(amount, selectedMovie, selectedShowtime, selectedLocation);
                            } else if (userChoice == movies.size() + 1) { // Go back to the previous selection
                                showtimeStack.pop();
                                locationStack.pop();
                                movieStack.pop();
                            } else {
                                cout << "Invalid showtime selection.\n";
                                // Go back to the previous selection
                                showtimeStack.pop();
                                locationStack.pop();
                                movieStack.pop();
                            }
                        } else if (userChoice == movies.size() + 1) { // Go back to the previous selection
                            locationStack.pop();
                            movieStack.pop();
                        } else {
                            cout << "Invalid location selection.\n";
                            // Go back to the previous selection
                            locationStack.pop();
                            movieStack.pop();
                        }
                    } else if (userChoice == movies.size() + 1) { // Go back to the previous selection
                        movieStack.pop();
                    } else {
                        cout << "Invalid movie selection.\n";
                    }
                    break;

                case 2:
                    displayLocations();
                    cin >> userChoice;
                    if (userChoice >= 1 && userChoice <= 3) {
                        string selectedLocation;
                        switch (userChoice) {
                            case 1:
                                selectedLocation = "Kalibata";
                                break;
                            case 2:
                                selectedLocation = "Kelapa Gading";
                                break;
                            case 3:
                                selectedLocation = "Bekasi";
                                break;
                        }
                        locationStack.push(selectedLocation);

                        displayMovies();
                        cin >> userChoice;
                        if (userChoice >= 1 && userChoice <= movies.size()) {
                            Movie& selectedMovie = movies[userChoice - 1];
                            movieStack.push(selectedMovie.name);

                            displayShowtimes(selectedMovie, selectedLocation);
                            cin >> userChoice;
                            if (userChoice >= 1 && userChoice <= selectedMovie.showtimes.size()) {
                                string selectedShowtime = selectedMovie.showtimes[userChoice - 1];
                                showtimeStack.push(selectedShowtime);

                                cout << "Enter the number of tickets: ";
                                cin >> amount;
                                processOrder(amount, selectedMovie, selectedShowtime, selectedLocation);
                            } else if (userChoice == movies.size() + 1) { // Go back to the previous selection
                                showtimeStack.pop();
                                locationStack.pop();
                                movieStack.pop();
                            } else {
                                cout << "Invalid showtime selection.\n";
                                // Go back to the previous selection
                                showtimeStack.pop();
                                locationStack.pop();
                                movieStack.pop();
                            }
                        } else if (userChoice == movies.size() + 1) { // Go back to the previous selection
                            movieStack.pop();
                        } else {
                            cout << "Invalid movie selection.\n";
                            // Go back to the previous selection
                            movieStack.pop();
                        }
                    } else if (userChoice == movies.size() + 1) { // Go back to the previous selection
                        locationStack.pop();
                    } else {
                        cout << "Invalid location selection.\n";
                    }
                    break;

                case 3:
                    displaySalesSummary();
                    break;

                case 6:
                    navigateBack();
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        } while (userChoice != 0 || (!movieStack.empty() || !locationStack.empty() || !showtimeStack.empty()));
    }

private:
    vector<Movie> movies = {
        {"Dune", {"10:00 AM", "02:00 PM", "06:00 PM"}},
        {"The Godfather", {"11:00 AM", "03:00 PM", "07:00 PM"}},
        {"Gran Turismo", {"12:00 PM", "04:00 PM", "08:00 PM"}},
        {"Avengers", {"01:00 PM", "05:00 PM", "09:00 PM"}},
        {"Hunger Games", {"02:00 PM", "06:00 PM", "10:00 PM"}},
    };
};

int main() {
    MovieTicketSystem ticketSystem;
    ticketSystem.run();
    return 0;
}