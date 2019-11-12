/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef PLAYER_STRATEGIES_H
#define PLAYER_STRATEGIES_H

#include "../Map/Map.h"
#include "Player.h"
#include "../Utility/Utility.h"
#include <map>

class Country;
class Player;
class Utility;

//interface for different player strategies
class ConcreteStrategies {

public:
    virtual ~ConcreteStrategies() = default;

    virtual void ReinforceStrategy(const vector<Country*>& countries, map<int, int>& country_num_army_to_add_pairs, int& num_bonus_army) = 0;

    virtual bool PromptPlayerToAttack(Player* player) = 0;
    virtual bool SelectCountryToAttack(Player* player) = 0;
    virtual bool SelectCountryToAttackFrom(Player* player) = 0;
    virtual void RollDiceToAttack(Player* player, const int MAX_NUM_OF_DICE_ATTACKER, const int MAX_NUM_OF_DICE_DEFENDER, int& attacker_num_dice, int& defender_num_dice) = 0;
    virtual void MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) = 0;

    virtual void FortifyStrategy() = 0;

};


class HumanPlayerStrategy : public ConcreteStrategies {

public:
    HumanPlayerStrategy() {};
    ~HumanPlayerStrategy() {};

    void ReinforceStrategy(const vector<Country*>& countries, map<int, int>& country_num_army_to_add_pairs, int& num_bonus_army) override;

    bool PromptPlayerToAttack(Player* player) override;
    bool SelectCountryToAttack(Player* player) override;
    bool SelectCountryToAttackFrom(Player* player) override;
    void RollDiceToAttack(Player* player, const int MAX_NUM_OF_DICE_ATTACKER, const int MAX_NUM_OF_DICE_DEFENDER, int& attacker_num_dice, int& defender_num_dice) override;
    void MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) override;

    void FortifyStrategy() override;
};

class AggressiveComputerPlayerStrategy : public ConcreteStrategies {

public:
    AggressiveComputerPlayerStrategy() {};
    ~AggressiveComputerPlayerStrategy() {};

    void ReinforceStrategy(const vector<Country*>& countries, map<int, int>& country_num_army_to_add_pairs, int& num_bonus_army) override;

    bool PromptPlayerToAttack(Player* player) override;
    bool SelectCountryToAttack(Player* player) override;
    bool SelectCountryToAttackFrom(Player* player) override;
    void RollDiceToAttack(Player* player, const int MAX_NUM_OF_DICE_ATTACKER, const int MAX_NUM_OF_DICE_DEFENDER, int& attacker_num_dice, int& defender_num_dice) override;
    void MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) override;

    void FortifyStrategy() override;
};

class BenevolantComputerPlayerStrategy : public ConcreteStrategies {

public:
    BenevolantComputerPlayerStrategy() {};
    ~BenevolantComputerPlayerStrategy() {};

    void ReinforceStrategy(const vector<Country*>& countries, map<int, int>& country_num_army_to_add_pairs, int& num_bonus_army) override;

    bool PromptPlayerToAttack(Player* player) override;
    bool SelectCountryToAttack(Player* player) override;
    bool SelectCountryToAttackFrom(Player* player) override;
    void RollDiceToAttack(Player* player, const int MAX_NUM_OF_DICE_ATTACKER, const int MAX_NUM_OF_DICE_DEFENDER, int& attacker_num_dice, int& defender_num_dice) override;
    void MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) override;

    void FortifyStrategy() override;
};


#endif //PLAYER_STRATEGIES_H