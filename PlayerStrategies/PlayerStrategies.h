/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef PLAYER_STRATEGIES_H
#define PLAYER_STRATEGIES_H

#include "../Player/Player.h"

class Player;

//interface for different player strategies
class ConcreteStrategies {

protected:
    Player* player_;

public:
    ConcreteStrategies(Player* player);
    virtual ~ConcreteStrategies() = 0;
    virtual void UseStrategy() = 0;

};


class HumanPlayerStrategy : ConcreteStrategies {

public:
    HumanPlayerStrategy(Player* player) : ConcreteStrategies(player) {};
    virtual ~HumanPlayerStrategy();

    virtual void UseStrategy();

};

class AggressiveComputerPlayerStrategy : ConcreteStrategies {

public:
    AggressiveComputerPlayerStrategy(Player* player) : ConcreteStrategies(player) {};
    virtual ~AggressiveComputerPlayerStrategy();

    virtual void UseStrategy();

};

class BenevolantComputerPlayerStrategy : ConcreteStrategies {
    BenevolantComputerPlayerStrategy(Player* player) : ConcreteStrategies(player) {};
    virtual ~BenevolantComputerPlayerStrategy();

    virtual void UseStrategy();
};


#endif //PLAYER_STRATEGIES_H