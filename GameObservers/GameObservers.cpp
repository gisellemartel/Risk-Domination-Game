
/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <iostream>

using namespace std;

#include "GameObservers.h"


// Subject -------------------------------------------------------------------------------------------------------------

Subject::Subject(){
    observers_ = new list<Observer*>;
}

Subject::Subject(const Subject &subject) {
    observers_ = subject.observers_;

    for(int i = 0; i < subject.observers_->size(); ++i) {
        observers_[i] = subject.observers_[i];
    }
}

Subject::~Subject(){

    for(Observer* observer : *observers_ ) {
        observer = nullptr;
        delete observer;
    }

    observers_ = nullptr;
    delete [] observers_;
}

Subject& Subject::operator=(const Subject &subject) {
    observers_ = subject.observers_;

    for(int i = 0; i < subject.observers_->size(); ++i) {
        observers_[i] = subject.observers_[i];
    }
    return *this;
}

void Subject::Attach(Observer* o){
    if(!observers_ || observers_->empty()) {
        return;
    }
    observers_->push_back(o);
}

void Subject::Detach(Observer* o){
    if(!observers_ || observers_->empty()) {
        return;
    }
    observers_->remove(o);
}

void Subject::Notify(){
    for(Observer* observer : *observers_) {
      observer->Update();
    }
}



// PhaseObserver -------------------------------------------------------------------------------------------------------

PhaseObserver::PhaseObserver(){
    turn_ = 0;
}

PhaseObserver::PhaseObserver(Player* subject) {
    turn_ = 0;
    player_subject_ = subject;

    if(!player_subject_) {
        cout << "Invalid value passed for subject. Aborting!" << endl;
    }
    //player_subject_->Attach(this);//----------------------------------------------------------------------------------------Bug
}

PhaseObserver::~PhaseObserver(){
    //player_subject_->Detach(this);//----------------------------------------------------------------------------------------Bug
    player_subject_ = nullptr;
    delete player_subject_;
}

void PhaseObserver::Update(){
    Display();
}

void PhaseObserver::Display() {
    cout << player_subject_->GetPlayerName() << ": ";

    //TODO use enum for game phase
    if (player_subject_->GetGamePhase() == 1) {
        ReinforceDisplay();
    }else if(player_subject_->GetGamePhase() == 2) {
        AttackDisplay();
    }else if(player_subject_->GetGamePhase() == 3){
        FortifyDisplay();
    }
}

void PhaseObserver::ReinforceDisplay() {
    ReinforcePhase* reinforcement = new ReinforcePhase();
    cout << "Reinforcement Phase" << endl;

    if(turn_ == 0) {
        cout << "Player has " << reinforcement->TotalReinforceArmy() << " armies available for reinforcement." << endl;
    } else if(turn_ == 1) {
        for (size_t i = 0; i < player_subject_->GetCountriesReinforced()->size(); i++) {
            cout << "Player has reinforced " << player_subject_->GetCountriesReinforced()->at(i)->GetCountryName()
                 << " with " << player_subject_->GetNumberOfArmiesReinforced()->at(i) << " armies." << endl;
        }
    }

    turn_++;
    turn_ %= 2;
    reinforcement = nullptr;
    delete reinforcement;
}

void PhaseObserver::AttackDisplay() {
    AttackPhase* attack_phase = new AttackPhase();
    cout << "Attack Phase" << endl;

    if(turn_ == 1) {
        if (player_subject_->GetHasAttacked()) {
            if (attack_phase->GetDefendingCountry()->GetNumberOfArmies() == 0) {
                cout << "Player has won the battle" << endl;
            } else if (attack_phase->GetAttackingCountry()->GetNumberOfArmies() == 0) {
                cout << "Player has lost the battle" << endl;
            } else {
                cout << "Player stopped attacking." << endl;
            }
        } else if (!player_subject_->GetHasAttacked()) {
            cout << "Player did not attack." << endl;
        }
    }

    turn_++;
    turn_ %= 2;
    attack_phase = nullptr;
    delete attack_phase;
}

void PhaseObserver::FortifyDisplay() {
    FortifyPhase* fortify_phase = new FortifyPhase();
    cout << "Fortification Phase" << endl;

    if(turn_ == 1) {
        if (fortify_phase->GetFortificationArmiesMoved() == 0) {
            cout << "No fortifications were made." << endl;
        } else {
            cout << fortify_phase->GetTargetCountry()->GetCountryName() << " has been fortified with "
                 << fortify_phase->GetFortificationArmiesMoved() << " armies from "
                 << fortify_phase->GetSourceCountry()->GetCountryName()
                 << endl;//not sure if this returns country names--------------------------------
        }
    }
    turn_++;
    turn_ %= 2;
    fortify_phase = nullptr;
    delete fortify_phase;
}


