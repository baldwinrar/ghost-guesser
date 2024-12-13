#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <fstream>

using namespace std;

void save_points(int points) {
    ofstream MyFile("points.txt");
    string s = to_string(points);
    MyFile << s;
    MyFile.close();
}

int load_points() {
    ifstream MyFile("points.txt");
    string s;
    getline(MyFile, s);
    return stoi(s);
}

int input_value() {
    int val;
    cin >> val;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Bad entry. Enter a number:\n>";
        cin >> val;
    }
    return val;
}

bool input_yorn() {
    char input;
    bool yorn;
    bool loop = true;
    while (loop) {
        cin >> input;
        if (input == 'y' || input == 'Y') {
            yorn = true;
            loop = false;
        }
        else if (input == 'n' || input == 'N') {
            yorn = false;
            loop = false;
        }
        else {
            cout << "Please enter 'y' or 'n'" << endl;
            cin.ignore(1000,'\n');
        }
    }
    return yorn;
}

int main() {
    // Begin random number generator
    random_device rd{};
    mt19937 engine{rd()};
    uniform_int_distribution<int> uniform_dist(0, 22);

    // List of all of our game's ghosts
    string ghosts[24] = 
    {"Spirit" /*0*/, "Wraith" /*1*/, "Phantom" /*2*/,
    "Poltergeist" /*3*/, "Banshee" /*4*/, "Jinn" /*5*/,
    "Mare" /*6*/, "Revenant" /*7*/, "Shade" /*8*/,
    "Demon" /*9*/, "Yurei" /*10*/, "Oni" /*11*/,
    "Yokai" /*12*/, "Hantu" /*13*/, "Goryo" /*14*/,
    "Myling" /*15*/, "Onryo" /*16*/, "The Twins" /*17*/,
    "Raiju" /*18*/, "Obake" /*19*/, "Moroi" /*20*/,
    "Deogen" /*21*/, "Thaye" /*22*/, "Mimic" /*23*/};

    // Set up points
    int points = load_points();
    double risky_payout = 15.0;
    double safe_payout = 1.5;

    // Run the main game loop
    bool game = true;
        while (game) {

        // Choose the ghost
        int prediction = uniform_dist(engine);
        cout << "I predict the ghost will be a: " << ghosts[prediction] << ", or a Mimic, and you currently have " << points << " points to bet with." << endl;
        cout << "Do you think it will be a "<< ghosts[prediction] << "/Mimic?" <<  "\n(y) or (n)?\n>";
        bool bet = input_yorn();

        // Set this to true when the user is good to move on to the next step
        bool ready = false;

        // Determine bet amount
        int amount;
        while (!ready) {
            cout << "How many points would you like to bet? (" << points << ") available:\n>";
            amount = input_value();
            if (amount < 0) {
                cout << "Please enter a positive value continue...";
            }
            else if (amount > points) {
                cout << "You cannot bet more points than you have..."<< endl;
                cout << "Do you wanna bet all your points? (y) or (n):\n>";
                bool betall = input_yorn();
                if (betall) {
                    amount = points;
                    ready = true;
                }
            }
            else {
                ready = true;
            }
        }
        
        points -= amount;

        // After the game is played, user enters discovered ghost type and bet is concluded
        cout << "After the game is finished, please enter the number of the correct ghost below:" << endl;
        for (int i=0; i<24; i++) {
            if (i%3 == 0) {cout << endl;}
            cout << "#" << i+1 << ": " << ghosts[i] << "\t";
        }
        cout << endl << ">";

        // Input discovered ghost type
        int discovered;
        ready = false;
        while (!ready) {
            discovered = input_value();
            if (discovered < 1 || discovered > 24) {
                cout << "Please enter a number between 1 and 24 to continue:\n>";
            }
            else {
                ready = true;
            }
        }
        discovered -= 1;
        
        // Prediction was correct
        if (discovered == 23 || discovered == prediction) {
            if (bet) {
                points += ceil(amount * risky_payout);
                cout << "You won your risky bet! Congratulations!" << endl;
            }
            else {
                cout << "Oh, too bad. Better luck next time!" << endl;
            }
        }

        // Prediction was incorrect
        else {
            if (!bet) {
                points += ceil(amount * safe_payout);
                cout << "You played it safe and earned some points! Nicely done." << endl;
            }
            else {
                cout << "Seems like the odds were against you! Next time for sure." << endl;
            }
        }

        // Show final points
        cout << "You finished this round with " << points << " points." << endl;

        // Did the player lose?
        if (points <= 0) {
            cout << "Oh, it seems like you lost all of your points. That's too bad :(" << endl;
            cout << "Let's fix that and reset you back to 100 points." << endl;
            points = 100;
        }

        // Did the player earn over 1,000,000 points?
        if (points >= 1000000) {
            cout << "Whoa! You earned over a million points! Congratulations! You're a ghost-guessing pro!" << endl;
            cout << "For my own sanity, I'm resetting you back to 1000 points. But we both know you're a winner in my heart." << endl;
            points = 1000;
        }

        // Wrap up the game, or keep playing?
        save_points(points);
        cout << "Do you want to play again? (y) or (n)?\n>";
        bool play = input_yorn();
        if (!play) {
            cout << "Alright, thanks for playing!" << endl;
            game = false;
        }
        else {
            cout << "Just one more round, right?" << endl;
        }
    }

    return 0;
}