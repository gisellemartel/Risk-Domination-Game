/**
 * Assignment #4 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef GAMEOBSERVERS_H
#define GAMEOBSERVERS_H

#include <iomanip>
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

#include "../Map/Map.h"
#include "../MapLoader/MapLoader.h"
#include "../MapLoader/ConquestMapLoader.h"
#include "../Dice/Dice.h"
#include "../Cards/Cards.h"
#include "../Cards/Deck.h"
#include "../Cards/Hand.h"
#include "../Utility/Utility.h"
#include "../Player/Player.h"
#include "StartupPhase.h"

enum GamePhase {
    Startup = 0,
    Reinforce = 1,
    Attack = 2,
    Fortify = 3
};

//Observer interface ---------------------------------------------------------------------------------------------------
class Observer {

public:
    Observer() = default;
    virtual ~Observer() = default;
    virtual void Update(Player* current_player, int current_phase, string current_action_description, bool phase_start, bool phase_over) = 0;

    // to be overidden by GameStatistics Observer
    virtual void Update(string msg) = 0;
};

//StatisticsSubject interface ----------------------------------------------------------------------------------------------------
class StatisticsSubject {

public:
    StatisticsSubject() = default;
    virtual void Register(Observer* observer) = 0;
    virtual void Unregister(Observer* observer) = 0;

    // you may need to add parameters to this function as needed (see PhaseSubject for example)
    virtual void Notify(string msg) = 0;
};


//PhaseSubject interface ----------------------------------------------------------------------------------------------------
class PhaseSubject {

public:
    PhaseSubject() = default;
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
    bool phase_start_;


    void DisplayPhaseData();
    void DisplayPhaseHeader();

public:
    PhaseObserver();
    PhaseObserver(const PhaseObserver& phase_observer);
    ~PhaseObserver() override = default;

    PhaseObserver& operator=(const PhaseObserver& phase_observer);

    void Update(Player* current_player, int current_phase, string current_action_description, bool phase_start, bool phase_over) override;
    void Update(string msg) override {};
};

//------------------------------------GameStatisticObserver-----------------------------
class GameStatisticObserver: public Observer {

private:
    vector<Player*>* players_;
    void DisplayStats();
    int CardExchangesCompleted();
    void DisplayActivePlayerStats();


public:
    // Dont forget everytime you have one or more pointer data member you absolutely need to also make your own copy constructor and assignment operator
    // I added them here for you
    GameStatisticObserver();
    explicit GameStatisticObserver(vector<Player*>* players);
    GameStatisticObserver(const GameStatisticObserver& game_statistic_observer);
    ~GameStatisticObserver() override;

    GameStatisticObserver& operator=(const GameStatisticObserver& game_statistic_observer);

    void Update(Player* current_player, int current_phase, string current_action_description, bool phase_start, bool phase_over) override {}
    void Update(string msg) override;

};
#endif //GAMEOBSERVERS_H
