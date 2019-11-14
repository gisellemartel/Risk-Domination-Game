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
    Observer();
    ~Observer();

    virtual void Update() = 0;

//protected:
//    Observer();

 } ;
//------------------------------------Observable-----------------------------
class Observable{
public:
    virtual ~Observable(){};
    virtual void attach(Observer *) = 0;
    virtual void detach(Observer *) = 0;
    virtual void notify() = 0;
protected:
    Observable(){};
private:
    vector<Observer*> observers_;
};
//------------------------------------Subject-----------------------------
class Subject: public Observable{
private:
    vector<Observer*> *observers_;
public:
    void Attach(Observer* o);
    void Detach(Observer* o);
    void Notify();
    Subject();
    ~Subject();
};
//------------------------------------GameStatisticObserver-----------------------------
class GameStatisticObserver: public Observer{
private:
    vector<Player*>* Players_;
    GameLoop *GameSubject_;
    int totalCountries;

public:
    GameStatisticObserver();
    GameStatisticObserver(GameLoop* liveGame);
    ~GameStatisticObserver();

    void update();
    void DisplayStats();
};





