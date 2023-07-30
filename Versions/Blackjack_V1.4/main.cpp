
/*
 * File:   main.cpp
 * Author: Liam Shaw
 *
 * Created on July, 22 
 * Purpose: The classic card game, Blackjack.
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib> 
#include <fstream>
#include <string>
#include <ctime> 

//User Libraries

//Function Prototypes
using namespace std;

int main(int argc, char** argv) {
    
    // Function pointer to generate a random card index from 0 to 12 (representing A to K)
    int (*rancrd)() = []() -> int  {
        return rand() % 13;
    };
    
    // Function pointer to get the value of a card
    int (*crdval)(int, int) = [](int cards, int total) -> int  {
        if (cards == 0) // Ace
            return (total + 11 <= 21) ? 11 : 1;
        else if (cards >= 9) // 10, J, Q, K
            return 10;
        else // 2 to 9
            return cards + 1;
    };
    
    srand(time(0));

    string cards[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    cout << "<><><><><><><><><><><><><><><><><>\n";
    cout << "     Welcome to Liam's Casino!\n";
    cout << "         - Blackjack -\n             $ $ $\n";
    cout << "     Enter any key to begin:\n";
    cout << "<><><><><><><><><><><><><><><><><>\n";
    cin.get();

    cout << "---------------------------------\n";
    cout << "           Bet Rates:\n";
    cout << "       $ Win: 2x your bet\n";
    cout << "    $$ Blackjack: 3x your bet\n";
    
    int pcard[10]; // Array to store the player's cards
    int dcard[10]; // Array to store the dealer's cards
    float bal = 100.00;
    bool again = true;
    
    while (again == true && bal > 5){
        
    bool bj = false; // Blackjack flag
    int ptotal = 0;
    int dtotal = 0;
    int pcards = 1; // Initialize pcards to 1
    int dcards = 1; // Initialize dcards to 1
    
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

    // Initial balance 
    cout << "---------------------------------\n";
    cout << "   - Your balance is: $"<< bal << " -\n\n";
    cout << "        Place your bets!\n        Min Bet is $5.00  \n        Max Bet is $50.00  \n";
    cout << "---------------------------------\n";
    
    // Initial bet 
    float bet = 0;
    cout << "Your bet: $";
    cin >> bet;
    cout << "---------------------------------\n";
    
    // Makes sure bet is within range
    while (bet < 5 or bet > 50){
        cout << "Please choose an amount that is between $5.00 and $50.00\n";
        cout << "Your bet: $";
        cin >> bet;
        cout << "---------------------------------\n";
        cin.clear();
    }
            
    // Display the player's cards
    cout << "Your cards:\n\n";
    for (int i = 0; i < 2; i++) {
        cout << "|" << cards[pcard[i]] << "| ";
    }
    cout << "\n\nTotal: " << ptotal << endl;

    // Check if the player has immediate Blackjack
    if (ptotal == 21) {
        float betadd = (bet * 3);
        cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
        cout << " Lucky you, first try Blackjack!\n";
        cout << "           You win!\n\n";
        cout << "         You made $" << betadd << "!\n";
        bal = ((bet * 3) + bal);
        cout << fixed << setprecision(2);
        cout << "  - Your balance is: $"<< bal << " -\n";
        cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
        cout << "           Play again?\nEnter 'Y' to continue or 'N' to exit.\n";
        char choice;
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        // Validate the input
        while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
            cout << "Invalid choice, Enter 'Y' to continue or 'N' to exit.\n";
            cin >> choice;
            cin.ignore(); // Clear the input buffer
        }

        if (choice == 'y' || choice == 'Y'){
            again = true;
        }
        else if(choice == 'n' || choice == 'N'){
            again = false;
        }
        
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
                float betadd = (bet * 3);
                cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
                cout << "       Blackjack! You win!\n\n";
                cout << "         You made $" << betadd << "!\n";
                bal = ((bet * 3) + bal);
                cout << fixed << setprecision(2);
                cout << "  - Your balance is: $"<< bal << " -\n";
                cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
                cout << "           Play again?\nEnter 'Y' to continue or 'N' to exit.\n";
                char choice;
                cin >> choice;
                cin.ignore(); // Clear the input buffer

            // Validate the input
            while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
                cout << "Invalid choice, Enter 'Y' to continue or 'N' to exit.\n";
                cin >> choice;
                cin.ignore(); // Clear the input buffer
            }
                
            if (choice == 'y' || choice == 'Y'){
                again = true;
            }
            else if(choice == 'n' || choice == 'N'){
                again = false;
            }
                bj = true;
                turn = false;
            } 
            
            else if (ptotal > 21) {
                cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
                cout << "        Bust! You lose.\n\n";
                cout << "         You lost $" << bet << "!\n";
                bal = (bal - bet);
                cout << fixed << setprecision(2);
                cout << "  - Your balance is: $"<< bal << " -\n";
                cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
                cout << "           Play again?\nEnter 'Y' to continue or 'N' to exit.\n";
                char choice;
                cin >> choice;
                cin.ignore(); // Clear the input buffer

                // Validate the input
                while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
                    cout << "Invalid choice, Enter 'Y' to continue or 'N' to exit.\n";
                    cin >> choice;
                    cin.ignore(); // Clear the input buffer
                }
                    
                if (choice == 'y' || choice == 'Y'){
                    again = true;
                }
                else if(choice == 'n' || choice == 'N'){
                    again = false;
                }
            bj = true;
            turn = false;
            }
        } 
        else if (choice == 'S' or choice == 's') {
            cout << "       You chose to stay.\n";
            turn = false;
        } 
        else {
            cout << "Invalid choice. Please enter 'H' to hit or 'S' to stay.\n";
        }
    }

    // Dealer's turn to hit
    while (dtotal < 17) {
        dcards++;
        dcard[dcards] = rancrd();
        dtotal += crdval(dcard[dcards], dtotal);
    }

    //Shows this when player does not blackjack or bust
    if (bj == false) {
        cout << "---------------------------------\n";
        cout << "Dealer's cards:\n\n";
        for (int i = 0; i <= dcards; i++) {
            cout << "|" << cards[dcard[i]] << "| ";
        }
        cout << "\n\nTotal: " << dtotal << "\n";
        
        //If player wins against the dealer
        if (dtotal > 21 || (ptotal <= 21 && ptotal > dtotal)) {
            float betadd = (bet * 2);
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
            cout << "   Congratulations! You win!\n\n";
            cout << "         You made $" << betadd << "!\n";
            bal = ((bet * 2) + bal);
            cout << fixed << setprecision(2);
            cout << "  - Your balance is: $"<< bal << " -\n";
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
            cout << "           Play again?\nEnter 'Y' to continue or 'N' to exit.\n";
            char choice;
            cin >> choice;
            cin.ignore(); // Clear the input buffer

            // Validate the input
            while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
                cout << "Invalid choice, Enter 'Y' to continue or 'N' to exit.\n";
                cin >> choice;
                cin.ignore(); // Clear the input buffer
            }

            if (choice == 'y' || choice == 'Y'){
                again = true;
            }
            else if(choice == 'n' || choice == 'N'){
                again = false;
            }
        } 
        // Tie between player and dealer
        else if (ptotal == dtotal) {
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
            cout << "          It's a tie!\n";
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
            cout << "           Play again?\nEnter 'Y' to continue or 'N' to exit.\n";
            char choice;
            cin >> choice;
            cin.ignore(); // Clear the input buffer

            // Validate the input
            while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
                cout << "Invalid choice, Enter 'Y' to continue or 'N' to exit.\n";
                cin >> choice;
                cin.ignore(); // Clear the input buffer
            }

            if (choice == 'y' || choice == 'Y'){
                again = true;
            }
            else if(choice == 'n' || choice == 'N'){
                again = false;
            }
        } 
        // Dealer wins
        else {
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
            cout << "        The dealer wins.\n\n";
            cout << "         You lost $" << bet << "!\n";
            bal = (bal - bet);
            cout << fixed << setprecision(2);
            cout << "  - Your balance is: $"<< bal << " -\n";
            cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
            cout << "           Play again?\nEnter 'Y' to continue or 'N' to exit.\n";
            char choice;
            cin >> choice;
            cin.ignore(); // Clear the input buffer

            // Validate the input
            while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
                cout << "Invalid choice, Enter 'Y' to continue or 'N' to exit.\n";
                cin >> choice;
                cin.ignore(); // Clear the input buffer
            }

            if (choice == 'y' || choice == 'Y'){
                again = true;
            }
            else if(choice == 'n' || choice == 'N'){
                again = false;
            }
        }
    }
        if (bal < 5){
            cout << "Sorry! Your balance is lower than the minimum bet.";
        }
    }

    //Exit Program
    return 0;
}