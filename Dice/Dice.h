/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#ifndef DICE_H
#define DICE_H
#include <vector>
using namespace std;

class Dice {

private:
    vector<int> *roll_num_stats_;
    int *total_rolls_;

public:
    Dice();
    Dice(const Dice& dice);
    ~Dice();

    Dice& operator=(const Dice& dice);
    vector<int> Roll(int num_of_dice);
    int GetRollNumStats(int roll_num);
    int GetTotalRolls();
};
#endif
