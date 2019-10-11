/**
 * Assignment #1 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include "Dice.h"

#include <random>
#include <vector>
#include <algorithm>

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

    for (size_t i = 0; i < num_of_dice; i++) {
        int dice_roll = dist(randomGenerator);
        dice_rolls.push_back(dice_roll);
        roll_num_stats_->at((size_t)dice_roll - 1)++;
        (*total_rolls_)++;
    }
    sort(dice_rolls.begin(), dice_rolls.end(), greater<>());
    return dice_rolls;
}
