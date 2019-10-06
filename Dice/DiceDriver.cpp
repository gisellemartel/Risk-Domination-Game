/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include "Dice.h"
using namespace std;

int main() {
    Dice *player = new Dice();
    int numOfDice;
    int reroll;
    do {
        while (true) {
            cout << "How many dice do you wish to roll?(max 3):\n";
            cin >> numOfDice;
            if (numOfDice > 3 || numOfDice < 1) {//Determining attacking and defending players(max number of dice) in another class
                cout << "Invalid number of dice selected, roll again.\n\n";
            } else {
                cout << "Rolling " << numOfDice << " dice.\n" << endl;
                break;
            }
        }

        vector<int> diceRolls = player->roll(numOfDice);

        cout << "Dice rolled:\n";
        for (int & diceRoll : diceRolls)
            cout << ' ' << diceRoll << endl;//print dice rolls

        for (int i = 1; i <= 6; i++) {
            double percentage = (static_cast<double>(player->getRollNumStats(i)) / player->getTotalRolls()) * 100;
            cout << "Frequency of dice value " << i << ": " << player->getRollNumStats(i) << "(" << fixed << setprecision(2)
                 << percentage << "%)" << endl;//sets number of decimals to 2
        }
        cout << "Total Rolls: " << player->getTotalRolls() << endl;

        cout << "\nDo you wish to reroll?(Enter 0 if not)\n";
        cin >> reroll;
        cout << endl;
    }while(reroll);

    delete player;
    return 0;
}

