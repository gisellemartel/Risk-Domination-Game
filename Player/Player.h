/**
 * Assignment #4 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "../Map/Country.h"
#include "../Cards/Hand.h"
#include "../Cards/Cards.h"
#include "PlayerStrategies.h"
#include "FortifyPhase.h"
#include "AttackPhase.h"
#include "ReinforcePhase.h"

#include <iostream>
#include <vector>
#include <map>
#include <filesystem>
using namespace std;

class Hand;
class Dice;
class Cards;
class ReinforcePhase;
class AttackPhase;
class FortifyPhase;
class GameEngine;

class Player {

private:
    bool is_human_;
    bool is_aggressive_;
    bool is_benevolant_;
    bool is_random_;
    bool is_cheater_;
    const int player_id_;

    string* player_name_;

    vector<Country*>* countries_;

    Hand* risk_cards_;
    Dice* dice_roll_;
    Map* game_map_;

    ReinforcePhase* reinforce_phase_;
    AttackPhase* attack_phase_;
    FortifyPhase* fortify_phase_;

    ConcreteStrategies* player_strategy_;
    GameEngine* game_engine_;

    //helper function for Attack()
    string AttackerConquersDefeatedCountry();
    void RemoveDefeatedPlayerFromGame(Country* defeated_country, Player* defender);

public:
    Player(string player_name, int player_id, Map* game_map, GameEngine* game_engine);
    Player(const Player &player);
    ~Player();

    Player& operator=(const Player& player);
    bool operator==(const Player& player);

    void SetPlayerName(string* player_name);
    void SetPlayerDice(Dice* dice);
    void SetPlayerHand(Hand* hand);
    void SetGameMap(Map* map);
    void SetPlayerStrategy(ConcreteStrategies* player_strategy);
    void SetAsHuman();
    void SetAsRandom();
    void SetAsCheater();
    void SetAsAggressive();
    void SetAsBenevolent();

    int GetPlayerID() const;
    vector<Country*>* GetPlayersCountries() const;
    GameEngine* GetGameEngine() const;
    ReinforcePhase* GetReinforcePhase() const;
    AttackPhase* GetAttackPhase() const;
    FortifyPhase* GetFortifyPhase() const;
    Country* GetCountryById(int id) const;
    Hand* GetPlayersCards() const;
    Dice* GetPlayerDice() const;
    Map* GetGameMap() const;
    string* GetPlayerName() const;

    Country* PromptPlayerToSelectCountry() const;
    Country* GetCountryInVectorById(vector<Country*>* countries, int country_id);

    bool DoesPlayerOwnCountry(int id) const;
    bool IsHuman() const;
    bool IsRandom() const;
    bool IsCheater() const;
    bool IsAggressive() const;
    bool IsBenevolant() const;

    int Find(Country* country) const;

    void AddCountryToCollection(Country* country);
    void RemoveCountryFromCollection(Country* country);
    void AddCardToCollection(Cards* card);
    void DisplayPlayerStats() const;
    void DisplayCountries() const;

    void Reinforce();
    void Attack();
    void Fortify();

    //will be used to implicitly notify the game engine of phase changes
    void Notify(Player* current_player, int current_phase, const string& current_action_description, bool phase_start, bool phase_over);
    void Notify(string msg, const vector<Player*>& players);
};

#endif //PLAYER_H
