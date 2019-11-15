/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */
#pragma once

#include <Vector>
#include "../GameEngine/GameEngine.h"

class Player;
using namespace std;

//------------------------------------Observer-----------------------------
class Observer{
public:
    ~Observer();
    virtual void Update() = 0;

protected:
    Observer();
 } ;

//------------------------------------Observable-----------------------------
class Observable{
public:
    virtual ~Observable(){};
    virtual void Attach(Observer *) = 0;
    virtual void Detach(Observer *) = 0;
    virtual void notify() = 0;
protected:
    Observable(){};
private:
    vector<Observer*> observers_;
};

//------------------------------------Subject-----------------------------
class Subject: public Observable{
private:
    vector<Observer*>* observers_;
public:
    Subject();
    ~Subject();

    void Attach(Observer *);
    void Detach(Observer *);
    void Notify();

};

//------------------------------------GameStatisticObserver-----------------------------
class GameStatisticObserver: public Observer{
private:
    vector<Player*>* Players_;
    GameLoop *GameSubject_;
    int totalCountries;
    int totalCardSwaps;

public:
    GameStatisticObserver();
    GameStatisticObserver(GameLoop* liveGame);
    ~GameStatisticObserver();

    void update();
    void DisplayStats();
};





