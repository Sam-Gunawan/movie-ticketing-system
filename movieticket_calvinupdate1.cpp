#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Define a class for Movie
class Movie {
public:
    string name;
    string studio;
    vector<string> showtimes;

    // Constructor
    Movie(string n, string s, vector<string> st) : name(n), studio(s), showtimes(st) {}
};

// Define a class for Order
class Order {
public:
    string movieName;
    string showtime;
    int row;
    int column;

    // Constructors
    Order() : row(0), column(0) {}  // Default constructor
    Order(string mName, string st, int r, int c) : movieName(mName), showtime(st), row(r), column(c) {}
};

// Define a class for Binary Search Tree Node
class TreeNode {
public:
    Movie movie;
    TreeNode* left;
    TreeNode* right;

    // Constructor
    TreeNode(Movie m) : movie(m), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class MovieBST {
private:
    TreeNode* root;

    // Helper function for inserting a movie into the BST
    TreeNode* insert(TreeNode* node, Movie m) {
        if (node == nullptr) {
            return new TreeNode(m);
        }

        if (m.name < node->movie.name) {
            node->left = insert(node->left, m);
        } else if (m.name > node->movie.name) {
            node->right = insert(node->right, m);
        }

        return node;
    }

public:
    // Helper function for displaying movies in-order
    void displayInOrder(TreeNode* node) {
        if (node != nullptr) {
            displayInOrder(node->left);
            cout << node->movie.name << " (" << node->movie.studio << ")\n";
            displayInOrder(node->right);
        }
    }


    // Constructor
    MovieBST() : root(nullptr) {}

    // Public function to insert a movie into the BST
    void insertMovie(Movie m) {
        root = insert(root, m);
    }

    // Public function to display movies
    void displayMovies() {
        cout << "Available Movies:\n";
        displayInOrder(root);
    }

    // Public function to find a movie by name
    Movie* findMovie(const string& movieName) {
        TreeNode* current = root;

        while (current != nullptr) {
            if (movieName == current->movie.name) {
                return &(current->movie);
            } else if (movieName < current->movie.name) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return nullptr;
    }
};

// Function to simulate ordering tickets
void orderTickets(vector<Order>& orders, Movie* selectedMovie, unordered_map<string, int>& salesSummary, int choice) {
    string selectedMovieee = selectedMovie->name;
    MovieBST movieBST;
    
    if (selectedMovie == nullptr) {
        cout << "Invalid movie selection.\n";
        return;
    }

    cout << "You've selected: " << selectedMovie->name << " at " << selectedMovie->studio << endl;

    // Get showtime
    cout << "Available Showtimes:\n";
    for (size_t i = 0; i < selectedMovie->showtimes.size(); ++i) {
        cout << i + 1 << ". " << selectedMovie->showtimes[i] << endl;
    }

    int showtimeChoice;
    cout << "Select a showtime (enter the showtime number): ";
    cin >> showtimeChoice;

    if (showtimeChoice >= 1 && showtimeChoice <= static_cast<int>(selectedMovie->showtimes.size())) {
        string selectedShowtime = selectedMovie->showtimes[showtimeChoice - 1];

        // Get the number of tickets
        int ticketCount;
        cout << "How many tickets would you like to order? ";
        cin >> ticketCount;

        // In a real system, you'd handle seat selection and other details here.
        // For this example, we'll skip those details.
        orders.push_back(Order(selectedMovie->name, selectedShowtime, 0, 0));

        int duhcalvin = 0;

        while (duhcalvin != 1){
            cout << "Judul Film: " << selectedMovie->name << endl;
            cout << "Waktu: " << selectedShowtime << endl;
            cout << "Jumlah Tiket: " << ticketCount << endl;
            cout << "Please check the summary above (1. OK, 2. Do correction)" << endl;
            int calvinn;
            cin >> calvinn;
            
            if (calvinn == 1){
                duhcalvin = 1;
                break;
            } else {
                int gantifilm, gantijam, gantijumlah, clv;
                
                cout << "1. Ganti Film" << endl << "2. Ganti Waktu" << endl << "3. Ganti Jumlah tiket" << endl;
                cin >> clv;

                if (clv == 1){
                    
                    
                    
                    cout << "Which Movie you wish to change to: ";
                    cin >> gantifilm;
                    
                    
                } else if (clv == 2){
                    cout << "Which time would you like to change";
                    cin >> gantijam;
                } else {
                    cout << "How many ticket would you purchase";
                    cin >> gantijumlah;
                }

                Movie* selectedMovie = movieBST.findMovie("Movie " + to_string(gantifilm));
                ticketCount = gantijumlah;
                showtimeChoice = gantijam;
            }

        }

        // Update sales summary
        salesSummary[selectedMovie->name] += ticketCount;

        // Display order summary
        cout << ticketCount << " tickets have been ordered for movie "
        << selectedMovie->name << " at " << selectedShowtime << endl;
    } else {
        cout << "Invalid showtime choice. Please try again.\n";
    }
}



int main() {
    // Create a MovieBST instance to store movie information
    MovieBST movieBST;

    // Insert movies into the BST
    movieBST.insertMovie({"Movie 1", "Studio A", {"10:00 AM", "02:00 PM", "06:00 PM"}});
    movieBST.insertMovie({"Movie 2", "Studio B", {"11:00 AM", "03:00 PM", "07:00 PM"}});
    movieBST.insertMovie({"Movie 3", "Studio C", {"12:00 PM", "04:00 PM", "08:00 PM"}});

    vector<Order> orders;
    unordered_map<string, int> salesSummary;

    // Display available movies
    movieBST.displayMovies();

    int choice;
    bool isDone = false;

    while (!isDone) {
        cout << "Select a movie to order tickets (enter the movie number), or enter 0 to view sales summary: ";
        cin >> choice;

        if (choice == 0) {
            isDone = true;
            break;
        }

        Movie* selectedMovie = movieBST.findMovie("Movie " + to_string(choice));
        orderTickets(orders, selectedMovie, salesSummary, choice);
    }

    // Display sales summary
    cout << "\nSales Summary:\n";
    for (const auto& entry : salesSummary) {
        cout << "Tickets sold for " << entry.first << ": " << entry.second << endl;
    }

    // Process payment, generate invoices, and print tickets
    // (You would need to implement this part based on your requirements)

    cout << "Thank you for using the Movie Ticketing System!\n";

    return 0;
}