//
//
//

#ifndef GAMEOBSERVERS_H
#define GAMEOBSERVERS_H

#include <list>

class Observer{
public:
    Observer();
    ~Observer();
    virtual void Update() = 0;
};

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
#endif //GAMEOBSERVERS_H
