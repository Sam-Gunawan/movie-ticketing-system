#include <iostream>
#include <string>
#include <ctime>
#include <unistd.h>  // for sleep function

using namespace std;

class UserAuthentication {
private:
    string username;
    string password;
    int maxAttempts;
    int timeoutDuration;  // Changed to int to store seconds
    int attempts;

    void displayTimer(int remainingSeconds) {
        cout << "Timeout in " << remainingSeconds << " seconds. Please wait...\n";
    }

public:
    UserAuthentication() : maxAttempts(3), timeoutDuration(15), attempts(0) {}

    void setUsername(const string& newUsername) {
        username = newUsername;
    }

    void setPassword(const string& newPassword) {
        password = newPassword;
    }

    bool login() {
        string enteredUsername;
        string enteredPassword;

        cout << "Enter username: ";
        cin >> enteredUsername;

        cout << "Enter password: ";
        cin >> enteredPassword;

        if (enteredUsername == username && enteredPassword == password) {
            cout << "Login successful!\n";
            attempts = 0; // Reset attempts on successful login
            return true;
        } else {
            cout << "Login failed. Incorrect username or password.\n";
            attempts++;

            if (attempts >= maxAttempts) {
                int remainingTime = timeoutDuration;
                while (remainingTime > 0) {
                    displayTimer(remainingTime);
                    sleep(1);  // Sleep for 1 second
                    remainingTime--;
                }

                cout << "Timeout complete. Please try again.\n";
                attempts = 0; // Reset attempts after the timeout
            }

            return false;
        }
    }
};

int main() {
    UserAuthentication userAuth;

    string newUsername;
    string newPassword;

    cout << "Set your username: ";
    cin >> newUsername;
    userAuth.setUsername(newUsername);

    cout << "Set your password: ";
    cin >> newPassword;
    userAuth.setPassword(newPassword);

    cout << "Username and password set.\n";

    // Attempt to log in
    while (!userAuth.login()) {
        // Continue to prompt for login until successful
    }

    return 0;
}
