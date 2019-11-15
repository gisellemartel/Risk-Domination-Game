/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */
#include <iostream>
#include "GameObservers.h"
#include "../GameEngine/GameEngine.h"

using namespace std;
//------------------------------------Observer-----------------------------
Observer::Observer() {
};
Observer::~Observer() {
};


//------------------------------------Subject-----------------------------
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


//------------------------------------GameStatisticObserver-----------------------------
GameStatisticObserver::GameStatisticObserver(GameLoop* liveGame){

    GameSubject_ = liveGame;
    Players_ = liveGame->GetPlayers();
    totalCountries = liveGame->GetPlayers()->at(0)->GetGameMap()->GetCountries()->size();
    totalCardSwaps = liveGame->GetPlayers()->at(0)->GetPlayersCards()->exchanges_done;
    GameSubject_->Attach(this);
}

GameStatisticObserver::~GameStatisticObserver(){
    GameSubject_->Detach(this);
}

void GameStatisticObserver::update(){

    DisplayStats();
}

void GameStatisticObserver::DisplayStats(){
    int playerCountries;
    float ownedRatio;

    for(int i= 0; i< Players_->size() ; i++){
        playerCountries = Players_->at(i)->GetPlayersCountries()->size();
        ownedRatio = playerCountries / totalCountries;

        cout<<"Player: "<<Players_->at(i)->GetPlayerName()
        <<"\t"
        <<"% Map Owned: "<<ownedRatio<<"%"
        <<endl;
    }
    cout<<"Number of Card Swaps: "<<totalCardSwaps;
}

