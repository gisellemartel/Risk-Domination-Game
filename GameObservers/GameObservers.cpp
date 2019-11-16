
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
    current_player_name_ = "";
    current_phase_ = "";
    current_action_description_ = "";
    phase_over_ = false;
}

PhaseObserver::PhaseObserver(const PhaseObserver &phase_observer) {
    current_player_name_ = phase_observer.current_player_name_;
    current_phase_ = phase_observer.current_phase_;
    current_action_description_ = phase_observer.current_action_description_;
    phase_over_ = phase_observer.phase_over_;
}

PhaseObserver& PhaseObserver::operator=(const PhaseObserver &phase_observer) {
    current_player_name_ = phase_observer.current_player_name_;
    current_phase_ = phase_observer.current_phase_;
    current_action_description_ = phase_observer.current_action_description_;
    phase_over_ = phase_observer.phase_over_;
    return *this;
}

void PhaseObserver::Update(Player* current_player, int current_phase, string current_action_description, bool phase_start, bool phase_over) {
    if(!current_player) {
        cout << "Something went wrong! Unable to update phase observer" << endl;
        return;
    }

    current_player_name_ = *current_player->GetPlayerName();
    current_action_description_ = current_action_description;
    phase_over_ = phase_over;

    //only print header once at start of phase
    if(current_phase_.empty() && phase_start) {
        switch(current_phase) {
            case GamePhase::Startup :
                Utility::ClearScreen();
                current_phase_ = "Startup Phase";
                DisplayPhaseHeader();
                break;
            case GamePhase::Reinforce :
                Utility::ClearScreen();
                current_phase_ = "Reinforce Phase";
                DisplayPhaseHeader();
                break;
            case GamePhase::Attack :
                Utility::ClearScreen();
                current_phase_ = "Attack Phase";
                DisplayPhaseHeader();
                break;
            case GamePhase::Fortify :
                Utility::ClearScreen();
                current_phase_ = "Fortify Phase";
                DisplayPhaseHeader();
                break;
            default:
                Utility::ClearScreen();
                current_phase_ = "";
                break;
        }
    }

    DisplayPhaseData();
}

void PhaseObserver::DisplayPhaseData() {
    cout << current_action_description_ << endl;
    if(phase_over_) {
        current_phase_ = "";
        //put thread to sleep to allow smoother visual transition
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

}

void PhaseObserver::DisplayPhaseHeader() {
    cout << endl << "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #" << endl << endl;
    cout << current_player_name_ + ": " + current_phase_ << endl << endl;
    cout << "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # " << endl << endl;
}