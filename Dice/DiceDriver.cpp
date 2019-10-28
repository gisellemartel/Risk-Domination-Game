/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include "Dice.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    cout << "\nTesting Dice Driver...\n\n";

    Dice *dice = new Dice();

    dice->PromptPlayerToRollDice();

    dice = nullptr;

    delete dice;

    return 0;
}
