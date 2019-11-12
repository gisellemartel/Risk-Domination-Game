/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "../Map/Map.h"
#include "../Dice/Dice.h"
#include "../Cards/Cards.h"
#include "PlayerStrategies.h"

#include <iostream>
#include <vector>
using namespace std;

//forward declaration
class Country;
class Dice;
class Cards;
class Hand;
class Map;
class Continent;
class ConcreteStrategies;
class AttackPhase;

class Player {

private:
    bool is_player_turn_;
    bool is_human_;
    int number_of_armies_;
    string* player_name_;
    vector<Country*>* countries_;
    Hand* risk_cards_;
    Dice* dice_roll_;
    Map* game_map_;
    AttackPhase* attack_phase_;

    ConcreteStrategies* player_strategy_;

public:
    explicit Player(string player_name);
    Player(string player_name, Map* game_map);
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
    void SetPlayerStrategy(ConcreteStrategies* player_strategy);

    void SetAsHuman();

    vector<Country*>* GetPlayersCountries() const;
    AttackPhase* GetAttackPhase() const;
    Country* GetCountryById(int id) const;
    Hand* GetPlayersCards() const;
    Dice* GetPlayerDice() const;
    Map* GetGameMap() const;
    string* GetPlayerName() const;

    Country* PromptPlayerToSelectCountry() const;
    Country* GetCountryInVectorById(vector<Country*>* countries, int country_id);

    bool DoesPlayerOwnCountry(int id) const;
    bool IsCurrentlyPlayersTurn() const;
    bool IsHuman() const;

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

// ReinforcePhase --------------------------------------
class ReinforcePhase
{
private:
    Player* turn_player_;
    int num_of_swaps_;
    int divider_;
    int reinforcement_army_;

public:
    explicit ReinforcePhase();
    ReinforcePhase(Player* turn_player, int num_of_swaps);
    ReinforcePhase(const ReinforcePhase& reinforce);
    ~ReinforcePhase();

    ReinforcePhase& operator = (const ReinforcePhase& reinforce);

    int TotalReinforceArmy();
    int PerCountryReinforceArmy();
    int PerContinentReinforceArmy();
    int CardSwapReinforceArmy();
};


// AttackPhase --------------------------------------
class AttackPhase {

private:
    Player* attacker_;
    Player* defender_;
    Map* game_map_;
    Country* attacking_country_;
    Country* defending_country_;
    vector<Country*>* opponent_neighbours_;

    //private helper methods
    Country* PromptPlayerToSelectDefender(vector<Country*>* neighbouring_countries);

public:

    explicit AttackPhase();
    explicit AttackPhase(Player *player);
    AttackPhase(const AttackPhase& attack);
    ~AttackPhase();

    AttackPhase& operator=(const AttackPhase& attack);

    Country* GetAttackingCountry() const;
    Country* GetDefendingCountry() const;
    vector<Country*>* GetOpponentNeighbours() const;

    void SetAttackingCountry(Country* attacking_country);
    void SetDefender(Player* defender);
    void SetDefendingCountry(Country* defending_country);


    bool PromptUserToAttack();
    bool SelectCountryToAttack();
    bool SelectCountryToAttackFrom();

    void FindOpponentNeighboursToAttackingCountry();
    void PerformDiceRoll();
};


class FortifyPhase {

private:
    Player* player_;
    Map* game_map_;
    Country* source_country_;
    Country* target_country_;

public:

    explicit FortifyPhase();
    explicit FortifyPhase(Player* player);
    FortifyPhase(const FortifyPhase& fortify);
    ~FortifyPhase();

    FortifyPhase& operator=(const FortifyPhase& fortify);

    bool PromptUserToFortify();
    bool SelectTargetCountry();
    bool SelectSourceCountry();

    void MoveArmies();
};

#endif //PLAYER_H
