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
class Player;

//Observer interface ---------------------------------------------------------------------------------------------------
class Observer {

public:
    virtual ~Observer() = default;
    virtual void Update(Player* current_player, int current_phase, string current_action_description, bool phase_start, bool phase_over) = 0;
};

//Subject interface ----------------------------------------------------------------------------------------------------
class Subject {

public:
    virtual void Register(Observer* observer) = 0;
    virtual void Unregister(Observer* observer) = 0;
    virtual void Notify(Player* current_player, int current_phase, string current_action_description, bool phase_start, bool phase_over) = 0;
};


//Phase observer implements Observer interface -------------------------------------------------------------------------
class PhaseObserver : public Observer {
private:
    Player* current_player_;
    string current_phase_;
    string current_action_description_;
    bool phase_over_;


    void DisplayPhaseData();
    void DisplayPhaseHeader();

public:
    PhaseObserver();
    PhaseObserver(const PhaseObserver& phase_observer);
    ~PhaseObserver() override;

    PhaseObserver& operator=(const PhaseObserver& phase_observer);

    void Update(Player* current_player, int current_phase, string current_action_description, bool phase_start, bool phase_over) override;
};

#endif //GAMEOBSERVERS_H
