
/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

#include "../GameEngine/GameEngine.h"
#include "GameObservers.h"

// PhaseObserver -------------------------------------------------------------------------------------------------------

PhaseObserver::PhaseObserver() {
    current_player_ = nullptr;
    current_phase_ = "";
    current_action_description_ = "";
    phase_over_ = false;
}

PhaseObserver::PhaseObserver(const PhaseObserver &phase_observer) {
    current_player_ = phase_observer.current_player_;
    current_phase_ = phase_observer.current_phase_;
    current_action_description_ = phase_observer.current_action_description_;
    phase_over_ = phase_observer.phase_over_;
}

PhaseObserver::~PhaseObserver() {
    current_player_ = nullptr;
    delete current_player_;
}

PhaseObserver& PhaseObserver::operator=(const PhaseObserver &phase_observer) {
    current_player_ = phase_observer.current_player_;
    current_phase_ = phase_observer.current_phase_;
    current_action_description_ = phase_observer.current_action_description_;
    phase_over_ = phase_observer.phase_over_;
    return *this;
}

void PhaseObserver::Update(Player* current_player, int current_phase, string current_action_description, bool phase_over) {
    if(!current_player) {
        cout << "Something went wrong! Unable to update phase observer" << endl;
    }

    current_player_ = current_player;
    current_action_description_ = current_action_description;
    phase_over_ = phase_over;

    //only print header once at start of phase
    if(current_phase_.empty()) {
        switch(current_phase) {
            case GamePhase::Startup :
                Utility::ClearScreen();
                current_phase_ = "Current Phase: Startup";
                cout << endl << "__________________________________________________" << endl;
                cout << *current_player_->GetPlayerName() + " is " + current_phase_ << endl;
                cout << "__________________________________________________" << endl << endl;
                break;
            case GamePhase::Reinforce :
                Utility::ClearScreen();
                current_phase_ = "Current Phase: Reinforce";
                cout << endl << "__________________________________________________" << endl;
                cout << *current_player_->GetPlayerName() + " is " + current_phase_ << endl;
                cout << "__________________________________________________" << endl << endl;
                break;
            case GamePhase::Attack :
                Utility::ClearScreen();
                current_phase_ = "Current Phase: Attack";
                cout << endl << "__________________________________________________" << endl;
                cout << *current_player_->GetPlayerName() + " is " + current_phase_ << endl;
                cout << "__________________________________________________" << endl << endl;
                break;
            case GamePhase::Fortify :
                Utility::ClearScreen();
                current_phase_ = "Current Phase: Fortify";
                cout << endl << "__________________________________________________" << endl;
                cout << *current_player_->GetPlayerName() + " is " + current_phase_ << endl;
                cout << "__________________________________________________" << endl << endl;
                break;
            default:
                Utility::ClearScreen();
                current_phase_ = "";
                break;
        }
    }

    if(phase_over_) {
        current_phase_ = "";
        //put thread to sleep to allow smoother visual transition
        std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    }

    DisplayPhaseData();
}

void PhaseObserver::DisplayPhaseData() {
    cout << current_action_description_ << endl;
}