/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#pragma once

#ifndef TEAMPROJECT_COMP345_PLAYER_H
#define TEAMPROJECT_COMP345_PLAYER_H

#include "../Part1/Map.h"
#include "../Part3/Dice.h"
#include "../Part5/Cards.h"

#include <iostream>
#include <vector>
using namespace std;

class Player {
private:
    string player_name_;
    vector<Country*>* countries_;
    vector<Cards*>* risk_cards_;
    Dice* dice_roll_;
    bool is_player_turn_;

public:

    Player(string player_name, vector<Country*>* countries_to_assign_to_player, bool is_player_turn);
    ~Player();

    void Reinforce();
    void Attack();
    void Fortify();

    bool isCurrentlyPlayersTurn() const;

    void SetPlayersTurn(bool is_turn);
};
#endif //TEAMPROJECT_COMP345_PLAYER_H
