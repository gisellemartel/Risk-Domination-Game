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
    observers_ = nullptr;
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

PhaseObserver::PhaseObserver(){
}

PhaseObserver::PhaseObserver(Player* subject) {
    player_subject_ = subject;
    player_subject_->Attach(this);
}
PhaseObserver::~PhaseObserver(){
    player_subject_->Detach(this);
    player_subject_ = nullptr;
    delete player_subject_;
}

void PhaseObserver::Update(){
    Display();
}

void PhaseObserver::Display() {

    cout << player_subject_->GetPlayerName() << ": ";

    if (player_subject_->GetGamePhase() == 1) {
        ReinforceDisplay();
    }else if(player_subject_->GetGamePhase() == 2) {
        AttackDisplay();
    }else if(player_subject_->GetGamePhase() == 3){
        FortifyDisplay();
    }

}

void PhaseObserver::ReinforceDisplay() {
    Reinforcement* reinforcement = new Reinforcement();
    cout << "Reinforcement Phase" << endl;
    cout << "Player has " << reinforcement->TotalReinforceArmy() << " armies available for reinforcement." << endl;

    for(size_t i = 0; i < player_subject_->GetCountriesReinforced()->size(); i++){
        cout << "Player has reinforced " << player_subject_->GetCountriesReinforced()->at(i)->GetCountryName() << " with " << player_subject_->GetNumberOfArmiesReinforced()->at(i) << " armies." << endl;
    }

    reinforcement = nullptr;
    delete reinforcement;
}

void PhaseObserver::AttackDisplay() {
    AttackPhase* attack_phase = new AttackPhase();
    cout << "Attack Phase" << endl;

    if(player_subject_->GetHasAttacked()) {
        if (attack_phase->GetDefendingCountry()->GetNumberOfArmies() == 0) {
            cout << "Player has won the battle" << endl;
        } else if (attack_phase->GetAttackingCountry()->GetNumberOfArmies() == 0) {
            cout << "Player has lost the battle" << endl;
        } else{
            cout << "Player no longer wanted to attack." << endl;
        }
    } else if(!player_subject_->GetHasAttacked()){
        cout << "Player did not attack." << endl;
    }
    attack_phase = nullptr;
    delete attack_phase;
}

void PhaseObserver::FortifyDisplay() {
    FortifyPhase* fortify_phase = new FortifyPhase();
    cout << "Fortification Phase" << endl;

    if(fortify_phase->GetFortificationArmiesMoved() == 0){
        cout << "No fortifications were made." << endl;
    }else {
        cout << fortify_phase->GetTargetCountry()->GetCountryName() << " has been fortified with "
             << fortify_phase->GetFortificationArmiesMoved() << " armies from "
             << fortify_phase->GetSourceCountry()->GetCountryName() << endl;//not sure if this returns country names--------------------------------
    }
    fortify_phase = nullptr;
    delete fortify_phase;
}

