
/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <iostream>

using namespace std;

#include "../GameEngine/GameEngine.h"
#include "GameObservers.h"

// PhaseObserver -------------------------------------------------------------------------------------------------------

void PhaseObserver::Update(Player* current_player, int current_phase, string current_action_description) {
    if(!current_player) {
        cout << "Something went wrong! Unable to update phase observer" << endl;
    }

    current_player_ = current_player;
    current_action_description_ = current_action_description;
    current_phase_ = current_phase;


    switch(current_phase) {
        case GamePhase::Startup :
            current_phase_ = "Current Phase: Startup";
            break;
        case GamePhase::Reinforce :
            current_phase_ = "Current Phase: Reinforce";
            break;
        case GamePhase::Attack :
            current_phase_ = "Current Phase: Attack";
            break;
        case GamePhase::Fortify :
            current_phase_ = "Current Phase: Fortify";
            break;
        default:
            current_phase_ = "";
            break;
    }

    DisplayPhaseData();
}

void PhaseObserver::DisplayPhaseData() {
    cout << endl << "__________________________________________________" << endl;
    cout << *current_player_->GetPlayerName() + ": " + current_phase_ + " phase" << endl;
    cout << current_action_description_ << endl;
    cout << "__________________________________________________" << endl << endl;
}