/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "../Map/Map.h"
#include "../Dice/Dice.h"
#include "../Cards/Cards.h"

#include <iostream>
#include <vector>
using namespace std;

//forward declaration
class Country;

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
#endif //PLAYER_H
