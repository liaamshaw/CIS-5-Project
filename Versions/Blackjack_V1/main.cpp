
/*
 * File:   main.cpp
 * Author: Liam Shaw
 *
 * Created on July, 20 
 * Purpose: The classic card game, Blackjack.
 */

//System Libraries

#include <iostream>
#include <iomanip> // betting
#include <cmath> // betting ?
#include <cstdlib> // rand + more? 
#include <fstream> // files
#include <string> // string
#include <ctime> // time

using namespace std;

//User Libraries

//Global Constants Only
//Conversions/Math/Physics Constants like PI/Speed of Light, etc...

//Function Prototypes

//Execution Begins Here
 
int main(int argc, char** argv) {
    
    //Set Random Number Seed here
    srand (time(0)); // cstdlib
    int rndnum1 = (rand() % 13);
    int rndnum2 = (rand() % 13);
    
    int rnddlr1 = (rand() % 13);
    int rnddlr2 = (rand() % 13);
    
    int dlrhit1 = (rand() % 13);
    int dlrhit2 = (rand() % 13);
    int dlrhit3 = (rand() % 13);
    int dlrhit4 = (rand() % 13);
    
    int rndhit1 = (rand() % 13);
    int rndhit2 = (rand() % 13);
    int rndhit3 = (rand() % 13);
    int rndhit4 = (rand() % 13); // 4 just in case
    
    cout << rndnum1 << " " << rndnum2;
    
    rndnum1 = 1, rndnum2 = 1;
    
    string cards[13] {"A","2","3","4","5","6","7","8","9","10","J","Q","K"}; //card library
    
    cout << "\nWelcome to Blackjack!\n";
    cout << "---------------------------------\n";
    cout << "Your cards:\n";
    
    string c1 = cards[rndnum1]; //random cards from library
    string c2 = cards[rndnum2];
    
    cout << "\n|" << c1 << "| |" << c2 << "|\n\n"; //starting cards
    
    int dlrttl = 0;
    
    while (dlrttl < 21){
        
        if (rnddlr1 > 0 & rnddlr1 < 11){
            dlrttl += rnddlr1;
        }
            else if (rnddlr1 > 9){
                dlrttl += 10;
            }
            else if (rnddlr1 == 0){
                dlrttl += 11;
            }
    
        if (rnddlr2 > 0 & rnddlr2 < 11){
            dlrttl += rnddlr2;
        }
            else if (rnddlr2 > 9){
                dlrttl += 10;
            }
            else if (rnddlr1 == 0){
                dlrttl += 11;
            }
        
        if (dlrttl < 21){
            if (dlrhit1 > 0 & dlrhit1 < 11){
            dlrttl += dlrhit1;
        }
            else if (dlrhit1 > 9){
                dlrttl += 10;
            }
            else if (dlrhit1 == 0){
                dlrttl += 11;
            }
        }
        
        if (dlrttl < 21){
            if (dlrhit2 > 0 & dlrhit2 < 11){
            dlrttl += dlrhit2;
        }
            else if (dlrhit2 > 9){
                dlrttl += 10;
            }
            else if (dlrhit2 == 0){
                dlrttl += 11;
            }
        }
        
        if (dlrttl < 21){
            if (dlrhit3 > 0 & dlrhit3 < 11){
            dlrttl += dlrhit3;
        }
            else if (dlrhit3 > 9){
                dlrttl += 10;
            }
            else if (dlrhit3 == 0){
                dlrttl += 11;
            }
        }
        
        if (dlrttl < 21){
            if (dlrhit4 > 0 & dlrhit4 < 11){
            dlrttl += dlrhit4;
        }
            else if (dlrhit4 > 9){
                dlrttl += 10;
            }
            else if (dlrhit4 == 0){
                dlrttl += 11;
            }
        }
    }
    
    cout << "DEALER: " << dlrttl << " NUMS: " << rnddlr1 << " " << rnddlr2 << " " << dlrhit1 <<  " " << dlrhit2 <<  " " << dlrhit3 <<  " " << dlrhit4 << "\n";
    
    int cN1 = 0, cN2 = 0, hN1 = 0, hN2 = 0, hN3 = 0, hN4 = 0; //initial value of cards
    
    if (rndnum1 > 0 & rndnum1 < 10){ //setting up value setting for future iterations with multiple types of cards
        cN1 = stoi(c1);
    }
        else if (rndnum1 > 9){
            cN1 += 10;
        }
            else {
            cN1 += 11;
            }
    
    if (rndnum2 > 0 & rndnum2 < 10){ // card 2 value
        cN2 = stoi(c2);
    }
        else if (rndnum2 > 9){
            cN2 += 10;
        }
            else {
            cN2 += 11;
            }
    
    int total = (cN1 + cN2); 
    cout << "Total: " << total;
    
    if (total == 21){
        cout << "\n---------------------------------\n";
        cout << "\nBlackjack! You win!\n";
    }
    
    char choice;
    if (total < 21){ // hit 1
        cout << "\n---------------------------------\n";
        cout << "Enter 'H' to hit or 'S' to stay.\n";
        cin >> choice;
        cout << "---------------------------------\n";
    
        if (choice == 'H' or choice == 'h'){
            string h1 = cards[rndhit1];
            cout << "Your cards:\n";
            cout << "\n|" << c1 << "| |" << c2 << "| |" << h1 << "|\n\n"; 
        
            if (rndhit1 > 0 & rndhit1 < 10){
                hN1 = stoi(h1);
            }
            else if (rndhit1 > 9){
                hN1 = 10;
            }
            else {
                hN1 = 11;
            }
        
        total += hN1;
        cout << "Total: " << total;
        
            if (total == 21){
                cout << "\n---------------------------------\n";
                cout << "\nBlackjack! You win!\n";
            }
            if (total > 21){\
                cout << "\n---------------------------------\n";
                cout << "\nBust! You lose.\n";
            }
        }
    }
    
    if (total < 21 & (choice == 'h' or choice == 'H')){ //hit 2
        cout << "\n---------------------------------\n";
        cout << "Enter 'H' to hit or 'S' to stay.\n";
        cin >> choice;
        cout << "---------------------------------\n";
        if (choice == 'H' or choice == 'h'){
            string h1 = cards[rndhit1];
            string h2 = cards[rndhit2];
            cout << "Your cards:\n";
            cout << "\n|" << c1 << "| |" << c2 << "| |" << h1 << "| |" << h2 << "|\n\n"; 
        
            if (rndhit2 > 0 & rndhit2 < 10){
                hN2 = stoi(h2);
            }
            else if (rndhit2 > 9){
                hN2 = 10;
            }
            else {
                hN2 = 11;
            }
        
        total += hN2;
        cout << "Total: " << total;
        
            if (total == 21){\
                cout << "\n---------------------------------\n";
                cout << "\nBlackjack! You win!\n";
            }
            if (total > 21){
                cout << "\n---------------------------------\n";
                cout << "\nBust! You lose.\n";
            }
        }
    }
        
    if (total < 21 & (choice == 'h' or choice == 'H')){ //hit 3
        cout << "\n---------------------------------\n";
        cout << "Enter 'H' to hit or 'S' to stay.\n";
        cin >> choice;
        cout << "---------------------------------\n";
        if (choice == 'H' or choice == 'h'){
            string h1 = cards[rndhit1];
            string h2 = cards[rndhit2];
            string h3 = cards[rndhit3];
            cout << "Your cards:\n";
            cout << "\n|" << c1 << "| |" << c2 << "| |" << h1 << "| |" << h2 << "| |" << h3 << "|\n\n"; 
        
            if (rndhit3 > 0 & rndhit3 < 10){
                hN3 = stoi(h3);
            }
            else if (rndhit3 > 9){
                hN3 = 10;
            }
            else {
                hN3 = 11;
            }
        
        total += hN3;
        cout << "Total: " << total;
        
            if (total == 21){\
                cout << "\n---------------------------------\n";
                cout << "\nBlackjack! You win!\n";
            }
            if (total > 21){
                cout << "\n---------------------------------\n";
                cout << "\nBust! You lose.\n";
            }
        }
    }
    
    //Declare Variables/Data Types here
    
    //Initialize Variable values here
    
    //Process inputs here
    
    //Display results
    
    //Exit Program
    return 0;
}

