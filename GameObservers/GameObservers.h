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

//------------------------------------Observable-----------------------------

//Game Engine Should probably be the Observable object. I would pass a pointer to the whole game engine to this class
// Inside Game Engine class when creating new game:
// i.e. Observable* observable = new Observable(this);
class Observable : public StatisticsSubject {

private:
    vector<Observer*>* observers_;

public:
    Observable();
    Observable(const Observable& observable);
    ~Observable();

    Observable& operator=(const Observable& observable);

    void Register(Observer *) override;
    void Unregister(Observer *) override;

    //You may need to add parameters to this as needed
    void Notify() override;
};

//------------------------------------GameStatisticObserver-----------------------------
class GameStatisticObserver: public Observer {

private:
    void DisplayStats(); //should be private since this method is only used by this class

//    vector<Player*>* players_; //Not needed, the game_engine_ has a pointer with all the players already
    GameEngine *game_engine_;
//    int totalCountries; // Not needed, the game_engine_ has a pointer to the map which has an attribute for the number of countries
    int total_card_swaps_; //incorrect naming conventions

public:
    // Dont forget everytime you have one or more pointer data member you absolutely need to also make your own copy constructor and assignment operator
    // I added them here for you
    GameStatisticObserver();
    GameStatisticObserver(GameEngine* game_engine);
    GameStatisticObserver(const GameStatisticObserver& game_statistic_observer);
    ~GameStatisticObserver();

    GameStatisticObserver& operator=(const GameStatisticObserver& game_statistic_observer);

    void Update() override;
    int CardExchangesCompleted();
    void DisplayActivePlayerStats();

};


#endif //GAMEOBSERVERS_H
