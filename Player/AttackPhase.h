//
// Created by Giselle Martel on 2019-11-29.
//

#ifndef TEAMPROJECT_COMP345_ATTACKPHASE_H
#define TEAMPROJECT_COMP345_ATTACKPHASE_H

#include <iostream>
using namespace std;

#include "Player.h"

class Map;
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


#endif //TEAMPROJECT_COMP345_ATTACKPHASE_H
