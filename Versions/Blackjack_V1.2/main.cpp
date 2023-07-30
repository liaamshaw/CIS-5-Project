
/*
 * File:   main.cpp
 * Author: Liam Shaw
 *
 * Created on July, 21 
 * Purpose: The classic card game, Blackjack.
 */

//System Libraries
#include <iostream>
#include <iomanip> // betting
#include <cmath> // betting ?
#include <cstdlib> 
#include <fstream> // files
#include <string> // string
#include <ctime> 

//User Libraries

//Function Prototypes
using namespace std;

// Function to generate a random card index from 0 to 12 (representing A to K)
int rancrd() {
    return rand() % 13;
}

// Function to get the value of a card
int crdval(int cards, int total) {
    if (cards == 0) // Ace
        return (total + 11 <= 21) ? 11 : 1;
    else if (cards >= 9) // 10, J, Q, K
        return 10;
    else // 2 to 9
        return cards + 1;
}

int main(int argc, char** argv) {
    srand(time(0));

    string cards[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    cout << "Welcome to Blackjack!\n";
    cout << "---------------------------------\n";

    int pcard[10]; // Array to store the player's cards
    int dcard[10]; // Array to store the dealer's cards
    int ptotal = 0;
    int dtotal = 0;
    int pcards = 1; // Initialize pcards to 1
    int dcards = 1; // Initialize dcards to 1
    bool bj = false; // Blackjack flag

    // Generate two random cards for the player and dealer
    for (int i = 0; i < 2; i++) {
        pcard[i] = rancrd();
        dcard[i] = rancrd();
    }

    // Calculate the initial total of the player's cards
    for (int i = 0; i < 2; i++) {
        ptotal += crdval(pcard[i], ptotal);
        dtotal += crdval(dcard[i], dtotal);
    }

    // Display the player's cards
    cout << "Your cards:\n\n";
    for (int i = 0; i < 2; i++) {
        cout << "|" << cards[pcard[i]] << "| ";
    }
    cout << "\n\nTotal: " << ptotal << endl;

    // Check if the player has Blackjack
    if (ptotal == 21) {
        cout << "\n---------------------------------\n";
        cout << "\nBlackjack! You win!\n";
        bj = true;
    }

    char choice;
    bool turn = true;

    // Player's turn to hit or stay
    while (ptotal < 21 && turn) {
        cout << "---------------------------------\n";
        cout << "Enter 'H' to hit or 'S' to stay.\n";
        cin >> choice;
        cin.ignore();

        cout << "---------------------------------\n";

        if (choice == 'H' or choice == 'h') {
            pcards++;
            pcard[pcards] = rancrd();
            cout << "Your cards:\n\n";
            for (int i = 0; i <= pcards; i++) {
                cout << "|" << cards[pcard[i]] << "| ";
            }

            ptotal += crdval(pcard[pcards], ptotal);

            cout << "\n\nTotal: " << ptotal << endl;

            if (ptotal == 21) {
                cout << "---------------------------------\n";
                cout << "\nBlackjack! You win!\n";
                bj = true;
                turn = false;
            } else if (ptotal > 21) {
                cout << "---------------------------------\n";
                cout << "\nBust! You lose.\n";
                bj = true;
                turn = false;
            }
        } else if (choice == 'S' or choice == 's') {
            cout << "You chose to stay.\n";
            turn = false;
        } else {
            cout << "Invalid choice. Please enter 'H' to hit or 'S' to stay.\n";
        }
    }

    // Dealer's turn to hit
    while (dtotal < 17) {
        dcards++;
        dcard[dcards] = rancrd();
        dtotal += crdval(dcard[dcards], dtotal);
    }

    if (bj == false) {
        cout << "---------------------------------\n";
        cout << "Dealer's cards:\n\n";
        for (int i = 0; i <= dcards; i++) {
            cout << "|" << cards[dcard[i]] << "| ";
        }
        cout << "\n\nTotal: " << dtotal << "\n";

        if (dtotal > 21 || (ptotal <= 21 && ptotal > dtotal)) {
            cout << "---------------------------------\n";
            cout << "\nCongratulations! You win!\n";
        } else if (ptotal == dtotal) {
            cout << "---------------------------------\n";
            cout << "\nIt's a tie!\n";
        } else {
            cout << "---------------------------------\n";
            cout << "\nThe dealer wins.\n";
        }
    }

    //Exit Program
    return 0;
}