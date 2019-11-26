/**
 * Assignment #4 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include "Dice.h"

#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

Dice::Dice() {
    roll_num_stats_ = new vector<int>(6);
    total_rolls_ = new int(0);
}

Dice::Dice(const Dice &dice) {
    for (size_t i = 0; i < dice.roll_num_stats_->size(); ++i) {
        roll_num_stats_[i] = dice.roll_num_stats_[i];
    }

    roll_num_stats_ = dice.roll_num_stats_;
    total_rolls_ = dice.total_rolls_;
}

Dice::~Dice() {
    delete roll_num_stats_;
    delete[] total_rolls_;
}


Dice& Dice::operator=(const Dice &dice) {
    for (size_t i = 0; i < dice.roll_num_stats_->size(); ++i) {
        roll_num_stats_[i] = dice.roll_num_stats_[i];
    }

    roll_num_stats_ = dice.roll_num_stats_;
    total_rolls_ = dice.total_rolls_;
    return *this;
}

int Dice::GetRollNumStats(size_t roll_num) {
    return roll_num_stats_ -> at(roll_num - 1);
}

int Dice::GetTotalRolls() {
    return *total_rolls_;
}

vector<int> Dice::Roll(int num_of_dice) {
    vector<int> dice_rolls;
    random_device rd;
    mt19937 randomGenerator(rd());
    uniform_int_distribution<int> dist(1, 6); //random number of equal distribution from 1 to 6

    for (std::size_t i = 0; i < num_of_dice; i++) {
        int dice_roll = dist(randomGenerator);
        dice_rolls.push_back(dice_roll);
        roll_num_stats_->at((size_t)dice_roll - 1)++;
        (*total_rolls_)++;
    }
    sort(dice_rolls.begin(), dice_rolls.end(), greater<>());
    return dice_rolls;
}

void Dice::PromptPlayerToRollDice() {

    int num_of_dice = 0;
    string input;
    bool reroll = true;
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

        vector<int> dice_rolls = Roll(num_of_dice);

        cout << "Dice rolled:\n";

        for (const int& dice_roll : dice_rolls) {
            //print dice rolls
            cout << ' ' << dice_roll << endl;
        }

        cout << endl;

        for (size_t i = 1; i <= 6; i++) {
            double percentage = (static_cast<double>(GetRollNumStats(i)) / GetTotalRolls()) * 100;
            cout << "Frequency of dice value " << i << ": " << GetRollNumStats(i) << "(" << fixed << setprecision(2)
                 << percentage << "%)" << endl;//sets number of decimals to 2
        }
        cout << "\nTotal Rolls: " << GetTotalRolls() << endl;

        input = "";
        cout << "\nDo you wish to reroll?(Enter y, any other char otherwise): ";
        cin >> input;

        if(input.find('y') == -1) {
            reroll = false;
        }

        cout << endl;

    } while(reroll);

}
