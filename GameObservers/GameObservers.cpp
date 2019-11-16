
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
    cout << *current_player->GetPlayerName() << ": Reinforce\n";
//    if(GameEngine::current_player_turn_ == GamePhase::Reinforce) {
//        cout << "Player has " << current_player->GetReinforcementPhase()->Get << " armies available for reinforcement." << endl;
//    } else if(GameEngine::current_player_turn_  == GamePhase::Attack) {
//        for (size_t i = 0; i < player_subject_->GetCountriesReinforced()->size(); i++) {
//            cout << "Player has reinforced " << player_subject_->GetCountriesReinforced()->at(i)->GetCountryName()
//                 << " with " << player_subject_->GetNumberOfArmiesReinforced()->at(i) << " armies." << endl;
//        }
//    }
}

void PhaseObserver::AttackDisplay(const Player* current_player) {
    cout << *current_player->GetPlayerName() << ": Attack\n";
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