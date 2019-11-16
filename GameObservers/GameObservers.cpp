
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

void PhaseObserver::Update(const GameEngine& game_data){
    Player* current_player = (*game_data.GetPlayers())[game_data.GetGameStart()->current_player_index_];
    if(!current_player) {
        cout << "Something went wrong! Unable to update phase observer" << endl;
    }

    int current_phase = game_data.GetCurrentPhase();
    DisplayCurrentPhase(current_player, current_phase);
}

void PhaseObserver::DisplayCurrentPhase(const Player* current_player, int current_phase) {
    cout << string( 100, '\n' );
    cout << "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # ";
    cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";

   switch(current_phase) {
       case GamePhase::Startup:
           cout << "Currently on startup phase\n";
           break;
       case GamePhase::Reinforce:
           ReinforceDisplay(current_player);
           break;
       case GamePhase ::Attack:
           AttackDisplay(current_player);
           break;
       case GamePhase::Fortify:
           FortifyDisplay(current_player);
           break;
   }

    cout << "\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void PhaseObserver::ReinforceDisplay(const Player* current_player) {

    string name = *current_player->GetPlayerName();
    ReinforcePhase* phase = current_player->GetReinforcePhase();

    if(!phase) {
        cout << name << ": Reinforce\n";
        return;
    }

    cout << "Total armies avaiable to reinforce with: " << phase->TotalReinforceArmy() << endl;

    if(phase->TotalReinforceArmy() < 1) {
        cout << name << " currently has to armies to reinforce a country with. Please try again next round" << endl;
        return;
    }

    if(!phase->GetReinforcementMap() || phase->GetReinforcementMap()->empty()) {
        return;
    }

    for(auto& entry : *phase->GetReinforcementMap()) {
        Country* country= current_player->GetCountryById(entry.first);
        string country_name = *country->GetCountryName();
        cout << name << " reinforcing " << country_name << " with " << entry.second << " armies" << endl;
        cout << "Result: " << country_name << " | #armies: " << country->GetNumberOfArmies() << endl;
    }
}

void PhaseObserver::AttackDisplay(const Player* current_player) {
    cout << *current_player->GetPlayerName() << ": Attack\n";
    string name = *current_player->GetPlayerName();
    AttackPhase* phase = current_player->GetAttackPhase();

    if(!phase) {
        cout << name << ": Attack\n";
        return;
    }

//    if(current_player_index_ == GamePhase::Attack) {
//        if (current_player->GetAttackPhase()) {
//            AttackPhase* attack_phase = current_player->GetAttackPhase();
//            if (attack_phase->GetDefendingCountry()->GetNumberOfArmies() == 0) {
//                cout << "Player has won the battle" << endl;
//            } else if (attack_phase->GetAttackingCountry()->GetNumberOfArmies() == 0) {
//                cout << "Player has lost the battle" << endl;
//            } else {
//                cout << "Player stopped attacking." << endl;
//            }
////        } else if (!player_subject_->GetHasAttacked()) {
////            cout << "Player did not attack." << endl;
////        }
//        }
//    }
}

void PhaseObserver::FortifyDisplay(const Player* current_player) {
    cout << *current_player->GetPlayerName() << ": Fortify\n";
//    if(current_player_index_ == GamePhase::Reinforce) {
//        FortifyPhase* fortify_phase = current_player->GetFortifyPhase();
////
////        if (fortify_phase && fortify_phase->GetFortificationArmiesMoved() == 0) {
////            cout << "No fortifications were made." << endl;
////        } else if (fortify_phase && fortify_phase->GetFortificationArmiesMoved() > 0){
////            cout << fortify_phase->GetTargetCountry()->GetCountryName() << " has been fortified with "
////                 << fortify_phase->GetFortificationArmiesMoved() << " armies from "
////                 << fortify_phase->GetSourceCountry()->GetCountryName()
////                 << endl;//not sure if this returns country names--------------------------------
////        }
//    }
}