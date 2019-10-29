/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
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
class Dice;
class Cards;
class Hand;

class Player {
private:
    string* player_name_;
    vector<Country*>* countries_;
    Hand* risk_cards_;
    Dice* dice_roll_;
    bool is_player_turn_;

public:

    explicit Player(string player_name);
    Player(string player_name, vector<Country*>* countries_to_assign_to_player, bool is_player_turn);
    Player(const Player &player);
    ~Player();

    Player& operator=(const Player& player);
    bool operator==(const Player& player);

    void SetPlayersTurn(bool is_turn);
    void SetPlayerName(string* player_name);
    void SetPlayerDice(Dice* dice);
    void SetPlayerHand(Hand* hand);

    bool isCurrentlyPlayersTurn() const;
    string* GetPlayerName() const;
    Dice* GetPlayerDice() const;
    vector<Country*>* GetPlayersCountries() const;
    Hand* GetPlayersCards() const;

    void AddCountryToCollection(Country* country);
    void AddCardToCollection(Cards* card);

    void DisplayPlayerStats() const;

    void Reinforce();
    void Attack();
    void Fortify();
};
#endif //PLAYER_H
