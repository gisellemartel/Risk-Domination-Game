//
//
//

#include <iostream>

using namespace std;

#include "GameObservers.h"


Observer::Observer(){
}

Observer::~Observer(){
}

Subject::Subject(){
    observers_ = new list<Observer*>;
}

Subject::~Subject(){
    delete observers_;
}

void Subject::Attach(Observer* o){
    observers_->push_back(o);
}

void Subject::Detach(Observer* o){
    observers_->remove(o);
}

void Subject::Notify(){
    list<Observer*>::iterator i = observers_->begin();
    for(; i != observers_->end(); ++i){
        (*i)->Update();
    }
}

