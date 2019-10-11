/**
 * Assignment #1 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include "Dice.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>

using namespace std;

int main() {
    Dice *player = new Dice();

    int num_of_dice = 0;
    string input;
    bool reroll = true;

    cout << "\nTesting Dice Driver...\n\n";
    do {
        while (true) {

            cout << "How many dice do you wish to roll?(max 3): ";

            try {
                cin >> input;
                num_of_dice = std::stoi(input);
            } catch (invalid_argument& e) {
                cout << "\nInvalid number of dice selected, roll again.\n\n";
                continue;
            }

            //Determining attacking and defending players(max number of dice) in another class
            if (num_of_dice > 3 || num_of_dice < 1) {
                cout << "\nInvalid number of dice selected, roll again.\n\n";
                continue;
            } else {
                cout << "\n\nRolling " << num_of_dice << " dice.\n\n";
                break;
            }
        }

        vector<int> dice_rolls = player->Roll(num_of_dice);

        cout << "Dice rolled:\n";

        for (int & dice_roll : dice_rolls) {
            //print dice rolls
            cout << ' ' << dice_roll << endl;
        }

        cout << endl;

        for (size_t i = 1; i <= 6; i++) {
            double percentage = (static_cast<double>(player->GetRollNumStats(i)) / player->GetTotalRolls()) * 100;
            cout << "Frequency of dice value " << i << ": " << player->GetRollNumStats(i) << "(" << fixed << setprecision(2)
                 << percentage << "%)" << endl;//sets number of decimals to 2
        }
        cout << "\nTotal Rolls: " << player->GetTotalRolls() << endl;

        input = "";
        cout << "\nDo you wish to reroll?(Enter y, any other char otherwise): ";
        cin >> input;

        if(input.find('y') == -1) {
            reroll = false;
        }

        cout << endl;

    } while(reroll);

    delete player;

    return 0;
}

