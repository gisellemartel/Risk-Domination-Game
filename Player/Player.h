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
class Continent;
class Map;
class Attack;

class Player {
private:
    string* player_name_;
    vector<Country*>* countries_;
    Hand* risk_cards_;
    Dice* dice_roll_;
    bool is_player_turn_;
    int  number_of_armies_;
    Map* game_map_;

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
    void SetNumberOfArmies(int number_of_armies);
    void SetGameMap(Map* map);

    vector<Country*>* GetPlayersCountries() const;
    Country* GetCountryById(int id) const;
    Hand* GetPlayersCards() const;
    Dice* GetPlayerDice() const;
    Map* GetGameMap() const;
    string* GetPlayerName() const;
    bool DoesPlayerOwnCountry(int id) const;
    bool IsCurrentlyPlayersTurn() const;
    int Find(Country* country) const;

    void AddCountryToCollection(Country* country);
    void RemoveCountryFromCollection(Country* country);
    void AddCardToCollection(Cards* card);
    void DisplayPlayerStats() const;
    void DisplayCountries() const;

    void Reinforce();
    void Attack();
    void Fortify();
};

class Reinforcement
{
private:
    Cards* player_cards_;
    int num_of_swaps_;
    int divider;
    int reinforcement_army;

public:
    explicit Reinforcement();
    Reinforcement(Cards* player_cards, int num_of_swaps);
    Reinforcement(const Reinforcement& reinforce);
    ~Reinforcement();

    Reinforcement& operator = (const Reinforcement& reinforce);

    int TotalReinforceArmy();
    int PerCountryReinforceArmy();
    int PerContinentReinforceArmy();
    int CardSwapReinforceArmy();

};

class AttackPhase {
private:
    Player* attacker_;
    Player* defender_;
    Map* game_map_;
    Country* attacking_country_;
    Country* defending_country_;

    //private helper methods
    Country* PromptPlayerToSelectAttacker();
    Country* PromptPlayerToSelectDefender(vector<Country*>* neighbouring_countries);

public:

    explicit AttackPhase();
    AttackPhase(Player *player);
    AttackPhase(const AttackPhase& attack);
    ~AttackPhase();

    AttackPhase& operator=(const AttackPhase& attack);

    void SetAttackingCountry(Country* country);
    void SetDefendingCountry(Country* country);

    Country* GetAttackingCountry() const;
    Country* GetDefendingCountry() const;

    bool PromptUserToAttack();
    Country* SelectCountryToAttackFrom();
    Country* SelectCountryToAttack();
    void PerformDiceRoll();
};



#endif //PLAYER_H
