//
// Created by Giselle Martel on 2019-11-29.
//

#ifndef TEAMPROJECT_COMP345_REINFORCEPHASE_H
#define TEAMPROJECT_COMP345_REINFORCEPHASE_H

#include <vector>
#include <iostream>
using namespace std;

#include "Player.h"

class Player;
class Continent;

// ReinforcePhase --------------------------------------
class ReinforcePhase
{
private:
    int num_of_swaps_;
    int divider_;
    int reinforcement_army_;
    vector<int>* countries_to_reinforce_;
    vector<int>* reinforce_values_;

public:
    explicit ReinforcePhase();
    ReinforcePhase(const ReinforcePhase& reinforce);
    ~ReinforcePhase();

    ReinforcePhase& operator = (const ReinforcePhase& reinforce);

    void SetTotalReinforcementArmy(int num_reinforcements);

    vector<int>* GetCountriesToReinforce() const;
    vector<int>* GetReinforceValues() const;

    int TotalReinforceArmy(Player* player, vector<Continent*>* continents);
    int PerCountryReinforceArmy(vector<Country*>* countries);
    int PerContinentReinforceArmy(Player* player, vector<Continent*>* continents);
    int CardSwapReinforceArmy(Player* player);
};

#endif //TEAMPROJECT_COMP345_REINFORCEPHASE_H
