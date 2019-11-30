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
    std::shared_ptr<Player> attacker_;
    std::shared_ptr<Player> defender_;
    std::shared_ptr<Country>attacking_country_;
    std::shared_ptr<Country> defending_country_;
    vector<std::shared_ptr<Country>>* opponent_neighbours_;
    int rand_player_num_attacks_;

public:
    static const int RAND_PLAYER_MAX_NUM_ATTACKS = 20;

    explicit AttackPhase();
    explicit AttackPhase(std::shared_ptr<Player> player);
    AttackPhase(const AttackPhase& attack);
    ~AttackPhase();

    AttackPhase& operator=(const AttackPhase& attack);

    std::shared_ptr<Country> GetAttackingCountry() const;
    std::shared_ptr<Country> GetDefendingCountry() const;
    vector<std::shared_ptr<Country>>* GetOpponentNeighbours() const;
    int GetRandPlayerNumAttacks() const;

    void SetAttackingCountry(std::shared_ptr<Country>attacking_country);
    void SetDefendingCountry(std::shared_ptr<Country> defending_country);
    void SetDefender(std::shared_ptr<Player> defender);
    void SetRandPlayerNumAttacks(int num_attacks);

    void UpdateNumAttacks();
    void RemoveDefeatedCountryFromOpponents(std::shared_ptr<Country> defeated_country);

    bool DoesOpposingCountryExist();
    bool PlayerHasCountryWithEnoughArmiesToAttack();

    void FindOpponentNeighboursToAttackingCountry();
};


#endif //TEAMPROJECT_COMP345_ATTACKPHASE_H
