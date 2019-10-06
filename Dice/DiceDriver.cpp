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
    int num_of_dice;
    int reroll;
    do {
        while (true) {
            cout << "How many dice do you wish to roll?(max 3):\n";
            cin >> num_of_dice;
            if (num_of_dice > 3 || num_of_dice < 1) {//Determining attacking and defending players(max number of dice) in another class
                cout << "Invalid number of dice selected, roll again.\n\n";
            } else {
                cout << "Rolling " << num_of_dice << " dice.\n" << endl;
                break;
            }
        }

        vector<int> dice_rolls = player->Roll(num_of_dice);

        cout << "Dice rolled:\n";
        for (int & dice_roll : dice_rolls)
            cout << ' ' << dice_roll << endl;//print dice rolls

        for (int i = 1; i <= 6; i++) {
            double percentage = (static_cast<double>(player->GetRollNumStats(i)) / player->GetTotalRolls()) * 100;
            cout << "Frequency of dice value " << i << ": " << player->GetRollNumStats(i) << "(" << fixed << setprecision(2)
                 << percentage << "%)" << endl;//sets number of decimals to 2
        }
        cout << "Total Rolls: " << player->GetTotalRolls() << endl;

        cout << "\nDo you wish to reroll?(Enter 0 if not)\n";
        cin >> reroll;
        cout << endl;
    }while(reroll);

    delete player;
    return 0;
}

