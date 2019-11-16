/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef GAMEOBSERVERS_H
#define GAMEOBSERVERS_H

#include <list>

#include "../Player/Player.h"
class GameEngine;

//Observer interface ---------------------------------------------------------------------------------------------------
class Observer {

public:
    virtual ~Observer() = default;
    virtual void Update(const GameEngine& game_data) = 0;
};

//Subject interface ----------------------------------------------------------------------------------------------------
class Subject {

public:
    virtual void Register(Observer* observer) = 0;
    virtual void Unregister(Observer* observer) = 0;
    virtual void Notify() = 0;
};


//Phase observer implements Observer interface -------------------------------------------------------------------------
class PhaseObserver : public Observer {
private:
    void DisplayCurrentPhase(const Player* current_player, int current_phase);

    void ReinforceDisplay(const Player* current_player);
    void AttackDisplay(const Player* current_player);
    void FortifyDisplay(const Player* current_player);


public:
    PhaseObserver() = default;
    ~PhaseObserver() override = default;
    void Update(const GameEngine& game_data) override;
};

#endif //GAMEOBSERVERS_H
