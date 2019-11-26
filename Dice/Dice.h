/**
 * Assignment #4 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef DICE_H
#define DICE_H

#include <vector>

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
