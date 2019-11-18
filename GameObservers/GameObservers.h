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

    // to be overidden by GameStatistics Observer
    virtual void Update() = 0;
};

//StatisticsSubject interface ----------------------------------------------------------------------------------------------------
class StatisticsSubject {

public:
    virtual void Register(Observer* observer) = 0;
    virtual void Unregister(Observer* observer) = 0;

    // you may need to add parameters to this function as needed (see PhaseSubject for example)
    virtual void Notify() = 0;
};


//PhaseSubject interface ----------------------------------------------------------------------------------------------------
class PhaseSubject {

public:
    virtual void Register(Observer* observer) = 0;
    virtual void Unregister(Observer* observer) = 0;
    virtual void Notify(Player* current_player, int current_phase, string current_action_description, bool phase_start, bool phase_over) = 0;
};


//Phase observer implements Observer interface -------------------------------------------------------------------------
class PhaseObserver : public Observer {
private:
    string current_player_name_;
    string current_phase_;
    string current_action_description_;
    bool phase_over_;


    void DisplayPhaseData();
    void DisplayPhaseHeader();

public:
    PhaseObserver();
    PhaseObserver(const PhaseObserver& phase_observer);
    ~PhaseObserver() override = default;

    PhaseObserver& operator=(const PhaseObserver& phase_observer);

    void Update(Player* current_player, int current_phase, string current_action_description, bool phase_start, bool phase_over) override;
    void Update() override {};
};

//------------------------------------GameStatisticObserver-----------------------------
class GameStatisticObserver: public Observer {

private:
    GameEngine *game_engine_;
    void DisplayStats();
    int CardExchangesCompleted();
    void DisplayActivePlayerStats();


public:
    // Dont forget everytime you have one or more pointer data member you absolutely need to also make your own copy constructor and assignment operator
    // I added them here for you
    GameStatisticObserver();
    GameStatisticObserver(GameEngine* game_engine);
    GameStatisticObserver(const GameStatisticObserver& game_statistic_observer);
    ~GameStatisticObserver();

    GameStatisticObserver& operator=(const GameStatisticObserver& game_statistic_observer);

    void Update(Player* current_player, int current_phase, string current_action_description, bool phase_start, bool phase_over) override {}
    void Update() override;

};
#endif //GAMEOBSERVERS_H
