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

Dice::Dice() {//constructor
    cout << "Constructing dice object" << endl;
    rollNumStats = new vector<int>(6);
    totalRolls = new int(0);
}

vector<int> Dice::roll(int numOfDice) {
    vector<int> diceRolls;
    random_device rd;
    mt19937 randomGenerator(rd());
    uniform_int_distribution<int> dist(1, 6); //random number of equal distribution from 1 to 6

    for (int i = 0; i < numOfDice; i++) {
        int diceRoll = dist(randomGenerator);
        diceRolls.push_back(diceRoll);
        rollNumStats->at(diceRoll-1)++;
        (*totalRolls)++;
    }
    sort(diceRolls.begin(), diceRolls.end(), greater<>());
    return diceRolls;
}

int Dice::getRollNumStats(int rollNum) {
    return rollNumStats -> at(rollNum-1);
}
int Dice::getTotalRolls() {
    return *totalRolls;//pointer?
}

Dice::~Dice() {//destructor
    cout << "Destroying dice object" << endl;
    delete rollNumStats;
    delete totalRolls;
}