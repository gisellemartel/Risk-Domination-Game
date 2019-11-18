
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

    //only print header once at start of phase or if we've filled the screen and need to clear it again
    if(current_phase_.empty() || phase_start) {
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }

}

void PhaseObserver::DisplayPhaseHeader() {
    cout << endl << "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #" << endl << endl;
    cout << current_player_name_ + ": " + current_phase_ << endl << endl;
    cout << "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # " << endl << endl;
}


// GameStatisticObserver -----------------------------------------------------------------------------------------------
GameStatisticObserver::GameStatisticObserver() {
    game_engine_ = nullptr;
}

GameStatisticObserver::GameStatisticObserver(const GameStatisticObserver &game_statistic_observer) {
    game_engine_ = game_statistic_observer.game_engine_;
}

GameStatisticObserver& GameStatisticObserver::operator=(const GameStatisticObserver &game_statistic_observer) {
    game_engine_ = game_statistic_observer.game_engine_;
    return *this;
}

GameStatisticObserver::GameStatisticObserver(GameEngine* game_engine){
    game_engine_ = game_engine;
}

GameStatisticObserver::~GameStatisticObserver(){
    game_engine_ = nullptr;
    delete game_engine_;
}

void GameStatisticObserver::Update(string msg, bool country_is_defeated, bool player_eliminated, bool game_won){

    if(country_is_defeated || player_eliminated || game_won) {
        Utility::ClearScreen();
    }

    DisplayStats();
}

void GameStatisticObserver::DisplayStats(){

    Utility::ClearScreen();

    cout << "+++++++++++ Current Game Statistics +++++++++++" << endl
    << "Current Number of Card Swaps: "
    << CardExchangesCompleted()
    << endl << endl
    << "List of Active Players: " << endl<<endl;

    DisplayActivePlayerStats();
}

int GameStatisticObserver::CardExchangesCompleted(){
    //check for nullptr
    vector<Player*>* players = game_engine_->GetPlayers();

    if(!players) {
        return 0;
    }

    Player* current = players->at(0);
    if(!current) {
        return 0;
    }

    Hand* a_hand = current->GetPlayersCards();

    if(a_hand) {
        return Hand::exchanges_done;
    }

    return 0;
}

void GameStatisticObserver::DisplayActivePlayerStats(){

    vector<Player*>* game_players = game_engine_->GetPlayers();

    if(!game_players || game_players->empty()) {
        cout<<"game_players error"<<endl;
        return;
    }

    for(Player* player : *game_players) {

        vector<Country*>* player_countries = player->GetPlayersCountries();
        if(!player_countries){
            cout<<"player_countries"<<endl;
            return;
        }

        vector<Country*>* map_countries = player->GetGameMap()->GetCountries();
        //Display the stats of players with at least 1 country
        if(player_countries && !player_countries->empty() && !map_countries->empty()){
            cout << "Player: "
            << *player->GetPlayerName()
            << endl
            << "Countries owned: "
            << player_countries->size()
            << endl
            << "% Map Conquered: "
            << fixed << setprecision(0) <<((float)(player_countries->size()) / (float)(map_countries->size()))*100
            << "%"
            << endl<<endl;
        }
        //Display winning message if a player owns the same amount of countries the map has
        if(player_countries && map_countries && player_countries->size() == map_countries->size()) {
            cout << "Congratulations "
                 << *player->GetPlayerName()
                 << " has won the game!"
                 << endl;
        }
    }
}