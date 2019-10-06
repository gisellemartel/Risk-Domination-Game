/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */


#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "Dice.h"
using namespace std;

Dice::Dice() {
    cout << "Constructing dice object" << endl;
    roll_num_stats_ = new vector<int>(6);
    total_rolls_ = new int(0);
}

vector<int> Dice::Roll(int num_of_dice) {
    vector<int> dice_rolls;
    random_device rd;
    mt19937 randomGenerator(rd());
    uniform_int_distribution<int> dist(1, 6); //random number of equal distribution from 1 to 6

    for (int i = 0; i < num_of_dice; i++) {
        int dice_roll = dist(randomGenerator);
        dice_rolls.push_back(dice_roll);
        roll_num_stats_->at(dice_roll-1)++;
        (*total_rolls_)++;
    }
    sort(dice_rolls.begin(), dice_rolls.end(), greater<>());
    return dice_rolls;
}

int Dice::GetRollNumStats(int roll_num) {
    return roll_num_stats_ -> at(roll_num-1);
}
int Dice::GetTotalRolls() {
    return *total_rolls_;
}

Dice::~Dice() {
    cout << "Destroying dice object" << endl;
    delete roll_num_stats_;
    delete total_rolls_;
}
