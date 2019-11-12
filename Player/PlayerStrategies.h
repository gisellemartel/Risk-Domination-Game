/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef PLAYER_STRATEGIES_H
#define PLAYER_STRATEGIES_H

#include "../Map/Map.h"
#include <map>

class Country;

//interface for different player strategies
class ConcreteStrategies {

protected:
    //Player* player_;

public:
   // explicit ConcreteStrategies() {};
//    ConcreteStrategies(const ConcreteStrategies& strategy);
//    ConcreteStrategies& operator=(const ConcreteStrategies& concrete_strategies);
    virtual ~ConcreteStrategies() = default;

    virtual void ReinforceStrategy(const vector<Country*>& countries, map<int, int>& country_num_army_to_add_pairs, int& num_bonus_army) = 0;
    virtual void AttackStrategy() = 0;
    virtual void FortifyStrategy() = 0;

    //virtual void SetPlayer(Player* player) = 0;

};


class HumanPlayerStrategy : public ConcreteStrategies {

public:
    HumanPlayerStrategy() {};
    ~HumanPlayerStrategy() {};

    void ReinforceStrategy(const vector<Country*>& countries, map<int, int>& country_num_army_to_add_pairs, int& num_bonus_army) override;
    void AttackStrategy() override;
    void FortifyStrategy() override;

   // void SetPlayer(Player* player) override { player_ = player; }
};

//class AggressiveComputerPlayerStrategy : public ConcreteStrategies {
//
//public:
//    AggressiveComputerPlayerStrategy() : ConcreteStrategies() {};
//    virtual ~AggressiveComputerPlayerStrategy();
//
//    virtual void ReinforceStrategy(map<int, int>& country_num_army_to_add_pairs, int& num_bonus_army);
//    virtual void AttackStrategy();
//    virtual void FortifyStrategy();
//
//    virtual void SetPlayer(Player* player) override { player_ = player; }
//};
//
//class BenevolantComputerPlayerStrategy : public ConcreteStrategies {
//    BenevolantComputerPlayerStrategy() : ConcreteStrategies() {};
//    virtual ~BenevolantComputerPlayerStrategy();
//
//    virtual void ReinforceStrategy(map<int, int>& country_num_army_to_add_pairs, int& num_bonus_army);
//    virtual void AttackStrategy();
//    virtual void FortifyStrategy();
//
//    virtual void SetPlayer(Player* player) { player_ = player; }
//};


#endif //PLAYER_STRATEGIES_H