/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */
#pragma once

#include <Vector>
class Player;
using namespace std;

class Observer{
public:
    Observer();
    ~Observer();
    virtual void Update() = 0;

//protected:
//    Observer():

 } ;

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

class Subject: public Observable{
private:
    vector<Observer*> *observers_;
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
    Subject();
    ~Subject();
};

class GameStatisticObserver: Observer{
private:
    vector<Player*>* Players_;

public:
    GameStatisticObserver();
    GameStatisticObserver(Player players);
    ~GameStatisticObserver();

    void update();
};



