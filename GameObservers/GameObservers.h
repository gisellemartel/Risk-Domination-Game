//
//
//

#ifndef GAMEOBSERVERS_H
#define GAMEOBSERVERS_H

#include <list>

#include "../Player/Player.h"

class Observer{
public:
    ~Observer();
    virtual void Update() = 0;
protected:
    Observer();
};

class Observer;//forward declaration of Observer?
class Subject{
public:
    Subject();
    ~Subject();
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
private:
    list<Observer*>* observers_;
};

class PhaseObserver : public Observer{
public:
    PhaseObserver();
    PhaseObserver(Player* subject);
    ~PhaseObserver();
    void Display();
    void ReinforceDisplay();
    void AttackDisplay();
    void FortifyDisplay();
    void Update();
private:
    Player* player_subject_;
    int turn_;
};
#endif //GAMEOBSERVERS_H
