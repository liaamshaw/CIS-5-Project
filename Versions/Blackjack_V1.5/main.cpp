
/*
 * File:   main.cpp
 * Author: Liam Shaw
 *
 * Created on July 30, 2023
 * Purpose: The classic card game, Blackjack.
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random card index from 0 to 12 (representing A to K)
int generateRandomCard() {
    return rand() % 13;
}

// Function to get the value of a card
int getCardValue(int card, int total) {
    // Ace can have a value of 1 or 11, depending on the current total
    if (card == 0)
        return (total + 11 <= 21) ? 11 : 1;
    // 10, J, Q, K all have a fixed value of 10
    else if (card >= 9)
        return 10;
    // 2 to 9 have their face value as their value
    else
        return card + 1;
}

// Function to display cards from an array
void displayCards(int cardArray[], int numCards, const string cards[]) {
    for (int i = 0; i < numCards; i++) {
        cout << "|" << cards[cardArray[i]] << "| ";
    }
    cout << endl;
}

// Function to play a single round of Blackjack
bool playRound(float& balance) {
    // Seed the random number generator with the current time
    srand(time(0));

    // Array to store card names
    string cards[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    // Display the bet rates
    cout << "---------------------------------\n";
    cout << "           Bet Rates:\n";
    cout << "       $ Win: 2x your bet\n";
    cout << "    $$ Blackjack: 3x your bet\n";

    // Arrays to store player's and dealer's cards
    int pcard[10];
    int dcard[10];

    // Blackjack flag to check if someone has already won with Blackjack
    bool bj = false;

    // Sets player and dealer cards total to 0
    int ptotal = 0;
    int dtotal = 0;

    // Initialize the number of cards for player and dealer to 1
    int pcards = 1;
    int dcards = 1;

    // Generate two random cards for the player and dealer
    for (int i = 0; i < 2; i++) {
        pcard[i] = generateRandomCard();
        dcard[i] = generateRandomCard();
    }

    // Calculate the initial total of the player's and dealer's cards
    for (int i = 0; i < 2; i++) {
        ptotal += getCardValue(pcard[i], ptotal);
        dtotal += getCardValue(dcard[i], dtotal);
    }

    // Display initial balance and get the player's bet
    cout << "---------------------------------\n";
    cout << "   - Your balance is: $" << balance << " -\n\n";
    cout << "        Place your bets!\n        Min Bet is $5.00  \n        Max Bet is $50.00  \n";
    cout << "---------------------------------\n";

    float bet = 0;
    cout << "Your bet: $";
    cin >> bet;
    cout << "---------------------------------\n";

    // Makes sure bet is within range
    while (bet < 5 or bet > 50) {
        cout << "Please choose an amount that is between $5.00 and $50.00\n";
        cout << "Your bet: $";
        cin >> bet;
        cout << "---------------------------------\n";
        cin.clear();
    }

    // Display the player's cards
    cout << "Your cards:\n\n";
    displayCards(pcard, 2, cards);
    cout << "\nTotal: " << ptotal << endl;

    // Check if the player has immediate Blackjack
    if (ptotal == 21) {
        float betadd = (bet * 3);
        cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
        cout << " Lucky you, first try Blackjack!\n";
        cout << "           You win!\n\n";
        cout << "         You made $" << betadd << "!\n";
        balance = ((bet * 3) + balance);
        cout << fixed << setprecision(2);
        cout << "  - Your balance is: $" << balance << " -\n";
        cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
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
            pcard[pcards] = generateRandomCard();
            cout << "Your cards:\n\n";
            displayCards(pcard, pcards + 1, cards);

            ptotal += getCardValue(pcard[pcards], ptotal);

            cout << "\nTotal: " << ptotal << endl;

            if (ptotal == 21) {
                float betadd = (bet * 3);
                cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
                cout << "       Blackjack! You win!\n\n";
                cout << "         You made $" << betadd << "!\n";
                balance = ((bet * 3) + balance);
                cout << fixed << setprecision(2);
                cout << "  - Your balance is: $" << balance << " -\n";
                cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
                bj = true;
                turn = false;
            } else if (ptotal > 21) {
                cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
                cout << "        Bust! You lose.\n\n";
                cout << "         You lost $" << bet << "!\n";
                balance = (balance - bet);
                cout << fixed << setprecision(2);
                cout << "  - Your balance is: $" << balance << " -\n";
                cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
                bj = true;
                turn = false;
            }
        } else if (choice == 'S' or choice == 's') {
            cout << "       You chose to stay.\n";
            turn = false;
        } else {
            cout << "Invalid choice. Please enter 'H' to hit or 'S' to stay.\n";
        }
    }

    // Dealer's turn to hit
    while (dtotal < 17 && !bj) {
        dcards++;
        dcard[dcards] = generateRandomCard();
        dtotal += getCardValue(dcard[dcards], dtotal);
    }

    // Determine the winner
    if (!bj) {
        // Show the dealer's cards
        cout << "---------------------------------\n";
        cout << "Dealer's cards:\n\n";
        displayCards(dcard, dcards + 1, cards);
        cout << "\nTotal: " << dtotal << "\n";
        cout << "---------------------------------\n";

        if (dtotal > 21 || (ptotal <= 21 && ptotal > dtotal)) {
            float betadd = (bet * 2);
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
            cout << "   Congratulations! You win!\n\n";
            cout << "         You made $" << betadd << "!\n";
            balance = ((bet * 2) + balance);
            cout << fixed << setprecision(2);
            cout << "  - Your balance is: $" << balance << " -\n";
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
        } else if (ptotal == dtotal) {
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
            cout << "          It's a tie!\n";
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
        } else {
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
            cout << "        The dealer wins.\n\n";
            cout << "         You lost $" << bet << "!\n";
            balance = (balance - bet);
            cout << fixed << setprecision(2);
            cout << "  - Your balance is: $" << balance << " -\n";
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
        }
    }

    // Ask if the player wants to play again
    cout << "           Play again?\nEnter 'Y' to continue or 'N' to exit.\n";
    cin >> choice;
    // Clear the input buffer
    cin.ignore();

    // Validate the input
    while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        cout << "Invalid choice, Enter 'Y' to continue or 'N' to exit.\n";
        cin >> choice;
        // Clear the input buffer
        cin.ignore();
    }

    return (choice == 'y' || choice == 'Y');
}

int main(int argc, char** argv) {
    float balance = 100.00;
    bool again = true;

    // Display welcome message and wait for player to press any key to start
    cout << "<><><><><><><><><><><><><><><><><>\n";
    cout << "     Welcome to Liam's Casino!\n";
    cout << "         - Blackjack -\n             $ $ $\n";
    cout << "     Enter any key to begin:\n";
    cout << "<><><><><><><><><><><><><><><><><>\n";
    cin.get();

    // Play rounds of Blackjack until the player chooses not to continue or runs out of balance
    while (again && balance > 5) {
        again = playRound(balance);
        if (balance < 5) {
            cout << "\n!-------------------------------------------------!\n";
            cout << " Sorry! Your balance is lower than the minimum bet.\n";
            cout << "!-------------------------------------------------!\n";
        }
    }

    // Exit Program
    return 0;
}
