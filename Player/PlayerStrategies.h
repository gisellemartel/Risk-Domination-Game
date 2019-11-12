/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef PLAYER_STRATEGIES_H
#define PLAYER_STRATEGIES_H

#include "Player.h"
#include <map>

class Player;

//interface for different player strategies
class ConcreteStrategies {

protected:
    Player* player_;

public:
    explicit ConcreteStrategies(Player* player) : player_(player) {};
    ConcreteStrategies(const ConcreteStrategies& strategy);
    ConcreteStrategies& operator=(const ConcreteStrategies& concrete_strategies);
    virtual ~ConcreteStrategies() = 0;

    virtual void ReinforceStrategy(map<int, int>& country_indices, int& num_bonus_army) = 0;
    virtual void AttackStrategy() = 0;
    virtual void FortifyStrategy() = 0;

};


class HumanPlayerStrategy : ConcreteStrategies {

public:
    explicit HumanPlayerStrategy(Player* player) : ConcreteStrategies(player) {};
    virtual ~HumanPlayerStrategy();

    virtual void ReinforceStrategy(map<int, int>& country_indices, int& num_bonus_army);
    virtual void AttackStrategy();
    virtual void FortifyStrategy();
};

class AggressiveComputerPlayerStrategy : ConcreteStrategies {

public:
    explicit AggressiveComputerPlayerStrategy(Player* player) : ConcreteStrategies(player) {};
    virtual ~AggressiveComputerPlayerStrategy();

    virtual void ReinforceStrategy(map<int, int>& country_indices, int& num_bonus_army);
    virtual void AttackStrategy();
    virtual void FortifyStrategy();
};

class BenevolantComputerPlayerStrategy : ConcreteStrategies {
    explicit BenevolantComputerPlayerStrategy(Player* player) : ConcreteStrategies(player) {};
    virtual ~BenevolantComputerPlayerStrategy();

    virtual void ReinforceStrategy(map<int, int>& country_indices, int& num_bonus_army);
    virtual void AttackStrategy();
    virtual void FortifyStrategy();
};


#endif //PLAYER_STRATEGIES_H