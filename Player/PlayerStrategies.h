/**
 * Assignment #4 COMP345, FALL 2019
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

    virtual void ReinforceStrategy(Player* player) = 0;

    virtual bool PromptPlayerToAttack(Player* player) = 0;
    virtual bool SelectCountryToAttack(Player* player) = 0;
    virtual bool SelectCountryToAttackFrom(Player* player) = 0;
    virtual void AttackerSelectNumberOfDice(Player* player, const int MAX_NUM_OF_DICE_ATTACKER,  int& attacker_num_dice)  = 0;
    virtual void MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) = 0;

    virtual bool PromptPlayerToFortify(Player* player) = 0;
    virtual bool SelectSourceCountry(Player* player) = 0;
    virtual bool SelectTargetCountry(Player* player) = 0;
    virtual void FortifyStrategy(Player* player, int& num_of_armies) = 0;

};


class HumanPlayerStrategy : public ConcreteStrategies {

public:
    HumanPlayerStrategy() {};
    ~HumanPlayerStrategy() override {};

    void ReinforceStrategy(Player* player) override;

    bool PromptPlayerToAttack(Player* player) override;
    bool SelectCountryToAttack(Player* player) override;
    bool SelectCountryToAttackFrom(Player* player) override;
    void AttackerSelectNumberOfDice(Player* player, const int MAX_NUM_OF_DICE_ATTACKER,  int& attacker_num_dice) override;
    void MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) override;

    bool PromptPlayerToFortify(Player* player) override;
    bool SelectSourceCountry(Player* player) override;
    bool SelectTargetCountry(Player* player) override;
    void FortifyStrategy(Player* player, int& num_of_armies) override;
};

class AggressiveComputerPlayerStrategy : public ConcreteStrategies {

public:
    AggressiveComputerPlayerStrategy() {};
    ~AggressiveComputerPlayerStrategy() override {};

    void ReinforceStrategy(Player* player) override;

    bool PromptPlayerToAttack(Player* player) override;
    bool SelectCountryToAttack(Player* player) override;
    bool SelectCountryToAttackFrom(Player* player) override;
    void AttackerSelectNumberOfDice(Player* player, const int MAX_NUM_OF_DICE_ATTACKER,  int& attacker_num_dice) override;
    void MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) override;

    bool PromptPlayerToFortify(Player* player) override;
    bool SelectSourceCountry(Player* player) override;
    bool SelectTargetCountry(Player* player) override;
    void FortifyStrategy(Player* player, int& num_of_armies) override;
};

class BenevolantComputerPlayerStrategy : public ConcreteStrategies {

public:
    BenevolantComputerPlayerStrategy() {};
    ~BenevolantComputerPlayerStrategy() override {};

    void ReinforceStrategy(Player* player) override;

    bool PromptPlayerToAttack(Player* player) override;
    bool SelectCountryToAttack(Player* player) override;
    bool SelectCountryToAttackFrom(Player* player) override;
    void AttackerSelectNumberOfDice(Player* player, const int MAX_NUM_OF_DICE_ATTACKER,  int& attacker_num_dice) override;
    void MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) override;


    bool PromptPlayerToFortify(Player* player) override;
    bool SelectSourceCountry(Player* player) override;
    bool SelectTargetCountry(Player* player) override;
    void FortifyStrategy(Player* player, int& num_of_armies) override;
};

class RandomComputerStrategy : public ConcreteStrategies {
public:
    RandomComputerStrategy() {};
    ~RandomComputerStrategy() override {};

    void ReinforceStrategy(Player* player) override;

    bool PromptPlayerToAttack(Player* player) override;
    bool SelectCountryToAttack(Player* player) override;
    bool SelectCountryToAttackFrom(Player* player) override;
    void AttackerSelectNumberOfDice(Player* player, const int MAX_NUM_OF_DICE_ATTACKER,  int& attacker_num_dice) override;
    void MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) override;


    bool PromptPlayerToFortify(Player* player) override;
    bool SelectSourceCountry(Player* player) override;
    bool SelectTargetCountry(Player* player) override;
    void FortifyStrategy(Player* player, int& num_of_armies) override;
};

class CheaterComputerStrategy : public ConcreteStrategies {
public:
    CheaterComputerStrategy() {};
    ~CheaterComputerStrategy() override {};

    void ReinforceStrategy(Player* player) override;

    bool PromptPlayerToAttack(Player* player) override;
    bool SelectCountryToAttack(Player* player) override;
    bool SelectCountryToAttackFrom(Player* player) override;
    void AttackerSelectNumberOfDice(Player* player, const int MAX_NUM_OF_DICE_ATTACKER,  int& attacker_num_dice) override;
    void MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) override;


    bool PromptPlayerToFortify(Player* player) override;
    bool SelectSourceCountry(Player* player) override;
    bool SelectTargetCountry(Player* player) override;
    void FortifyStrategy(Player* player, int& num_of_armies) override;
};


#endif //PLAYER_STRATEGIES_H