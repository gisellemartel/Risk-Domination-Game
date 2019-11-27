//
// Created by Giselle Martel on 2019-11-26.
//

#ifndef TEAMPROJECT_COMP345_PHASES_H
#define TEAMPROJECT_COMP345_PHASES_H

#include <iostream>
using namespace std;

#include "Player.h"

class Map;

// ReinforcePhase --------------------------------------
class ReinforcePhase
{
private:
    Player* turn_player_;
    int num_of_swaps_;
    int divider_;
    int reinforcement_army_;
    vector<int>* countries_to_reinforce_;
    vector<int>* reinforce_values_;

public:
    explicit ReinforcePhase();
    ReinforcePhase(Player* turn_player, int num_of_swaps);
    ReinforcePhase(const ReinforcePhase& reinforce);
    ~ReinforcePhase();

    ReinforcePhase& operator = (const ReinforcePhase& reinforce);

    void SetTotalReinforcementArmy(int num_reinforcements);

    vector<int>* GetCountriesToReinforce() const;
    vector<int>* GetReinforceValues() const;

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
    int rand_player_num_attacks_;

public:
    static const int RAND_PLAYER_MAX_NUM_ATTACKS = 20;

    explicit AttackPhase();
    explicit AttackPhase(Player *player);
    AttackPhase(const AttackPhase& attack);
    ~AttackPhase();

    AttackPhase& operator=(const AttackPhase& attack);

    Country* GetAttackingCountry() const;
    Country* GetDefendingCountry() const;
    vector<Country*>* GetOpponentNeighbours() const;
    int GetRandPlayerNumAttacks() const;

    void SetAttackingCountry(Country* attacking_country);
    void SetDefendingCountry(Country* defending_country);
    void SetDefender(Player* defender);
    void SetRandPlayerNumAttacks(int num_attacks);

    void UpdateNumAttacks();
    void RemoveDefeatedCountryFromOpponents(Country* defeated_country);

    bool DoesOpposingCountryExist();
    bool PlayerHasCountryWithEnoughArmiesToAttack();

    void FindOpponentNeighboursToAttackingCountry();
};


class FortifyPhase {

private:
    Player* player_;
    Map* game_map_;
    Country* source_country_;
    Country* target_country_;

    vector<Country*>* neighbours_to_fortify_;

public:

    explicit FortifyPhase();
    explicit FortifyPhase(Player* player);
    FortifyPhase(const FortifyPhase& fortify);
    ~FortifyPhase();

    FortifyPhase& operator=(const FortifyPhase& fortify);

    Country* GetSourceCountry() const;
    Country* GetTargetCountry() const;
    vector<Country*>* GetNeighboursToFortify() const;

    void SetSourceCountry(Country* source);
    void SetTargetCountry(Country* target);
};


#endif //TEAMPROJECT_COMP345_PHASES_H
