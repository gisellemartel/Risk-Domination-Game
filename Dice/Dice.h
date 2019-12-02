

#ifndef DICE_H
#define DICE_H

#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Dice {

private:
    vector<int>* roll_num_stats_;
    int* total_rolls_;

public:
    Dice();
    Dice(const Dice& dice);
    ~Dice();

    Dice& operator=(const Dice& dice);

    int GetRollNumStats(size_t roll_num);
    int GetTotalRolls();

    vector<int> Roll(int num_of_dice);

    void PromptPlayerToRollDice();
};
#endif
