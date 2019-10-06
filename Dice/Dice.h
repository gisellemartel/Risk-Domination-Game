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
    vector<int> *rollNumStats;
    int *totalRolls;
public:
    Dice();
    ~Dice();
    vector<int> roll(int numOfDice);
    int getRollNumStats(int rollNum);
    int getTotalRolls();
};
#endif
