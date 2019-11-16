/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef GAMEOBSERVERS_H
#define GAMEOBSERVERS_H

#include <list>

#include "../Player/Player.h"
class Player;

class Observer {

public:
    virtual ~Observer() {}
    virtual void Update() = 0;

protected:
    Observer() {}
};

class PhaseObserver : public Observer {

public:
    PhaseObserver();
    PhaseObserver(Player* subject);
    PhaseObserver(const PhaseObserver& player);
    ~PhaseObserver();

    PhaseObserver& operator=(const Player& player);

    void Display();
    void ReinforceDisplay();
    void AttackDisplay();
    void FortifyDisplay();
    void Update() override;

private:
    Player* player_subject_;
    int turn_;
};

class Subject {

public:
    Subject();
    Subject(const Subject& subject);
    ~Subject();

    Subject& operator=(const Subject& subject);

    void Attach(Observer* o);
    void Detach(Observer* o);
    void Notify();

private:
    list<Observer*>* observers_;
};


#endif //GAMEOBSERVERS_H
