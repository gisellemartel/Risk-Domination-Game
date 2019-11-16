/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef GAMEOBSERVERS_H
#define GAMEOBSERVERS_H

#include <list>

#include "../GameEngine/GameEngine.h"

//Observer interface
class Observer {

public:
    virtual void Update() = 0;
};

//Subject interface
class Subject {

public:
    virtual void Register(Observer* observer) = 0;
    virtual void Unregister(Observer* observer) = 0;
    virtual void Notify() = 0;
};

class PhaseObserver : public Observer {

public:
    PhaseObserver();
    PhaseObserver(GameEngine* game_data_);
    PhaseObserver(const PhaseObserver& phase_observer);
    ~PhaseObserver();

    PhaseObserver& operator=(const Player& player);

    void Display();
    void ReinforceDisplay();
    void AttackDisplay();
    void FortifyDisplay();
    void Update() override;

private:
    GameEngine* game_data_;
};

#endif //GAMEOBSERVERS_H
