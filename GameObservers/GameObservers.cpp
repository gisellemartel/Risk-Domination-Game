/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */
#include <iostream>
#include "GameObservers.h"
#include "../Player/Player.h"

using namespace std;

Observer::Observer() {
};
Observer::~Observer() {
};

Subject::Subject(){
    observers_ = new vector<Observer*>;
}

Subject::~Subject(){
    delete observers_;
}

void Subject::Attach(Observer* o){
    observers_->push_back(o);
}

void Subject::Detach(Observer* o){

}

void Subject::Notify(){
    vector<Observer*>::iterator i = observers_->begin();
    for (; i!= observers_->end(); ++i)
        (*i)->Update();
}

GameStatisticObserver::GameStatisticObserver(Player players){
    Players_ = new vector<Player*>;
}

void GameStatisticObserver::update(){
    int totalCountries = Players_->at(0)->GetGameMap()->GetCountries()->size();
    int playerCountries;
    float ownedRatio;

    for(int i= 0; i< Players_->size() ; i++){
        playerCountries = Players_->at(i)->GetPlayersCountries()->size();
        ownedRatio = playerCountries / totalCountries;

        cout<<Players_->at(i)->GetPlayerName();

        cout<<ownedRatio;
    }
}

