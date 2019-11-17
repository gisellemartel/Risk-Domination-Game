
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

    // be careful about using incorrect naming conventions
    // also, this is a dangerous way of using pointers and getting a crash during runtime
//    totalCardSwaps = liveGame->GetPlayers()->at(0)->GetPlayersCards()->exchanges_done;
    //it is better to do it this way, where you check at each step for nullptr:

    /*
     * vector<Country*>* player = game_engine_->GetPlayers();
     *
     * if(!player) {
     *  return;
     * }
     *
     * Player* current_player = player->at(0);
     *
     * if(!player) {
     *      return;
     * }
     *
     * vector<Cards*>* card = player->GetPlayersCards();
     *
     * if(card ) {
     *  total_card_swaps_ = card->exchanges_done;
     * }
     *
     *
     */


    // Registering should be done by the Client i.e. in the driver. Please see GameEngineDriver.cpp for example
    //game_engine_->Register(); // remove
}


GameStatisticObserver::~GameStatisticObserver(){
    // This should be done by the Client i.e. in the driver. Please see GameEngineDriver.cpp for example
//    game_engine_->Unregister(this); // remove
// the destructor should only be used for destroying pointer data members

    game_engine_ = nullptr;
    delete game_engine_;
}

void GameStatisticObserver::Update(){

    DisplayStats();
}

void GameStatisticObserver::DisplayStats(){

    cout
    <<"Current Game Statistics"<<endl
    <<"Current Number of Card Swaps: "
    <<CardExchangesCompleted()
    <<endl
    <<"Active Players: "<<endl;
    DisplayActivePlayerStats();




//    for(int i= 0; i< Players_->size() ; i++){
//        playerCountries = Players_->at(i)->GetPlayersCountries()->size();
//        ownedRatio = playerCountries / totalCountries;
//
//        cout<<"Player: "<<Players_->at(i)->GetPlayerName()
//            <<"\t"
//            <<"% Map Owned: "<<ownedRatio<<"%"
//            <<endl;
//    }
}

int GameStatisticObserver::CardExchangesCompleted(){
    //check for nullptr
    vector<Player*>* players = game_engine_->GetPlayers();
    if(!players)
        return 0;

    Player* current = players->at(0);
    if(!current)
        return 0;

    Hand* a_hand = current->GetPlayersCards();
    if(a_hand)
        return a_hand->exchanges_done;

    return 0;
}

void GameStatisticObserver::DisplayActivePlayerStats(){

    for(int i= 0; i<game_engine_->GetPlayers()->size();++i){
        //Display the stats of players with at least 1 country
        if(!game_engine_->GetPlayers()->at(i)->GetPlayersCountries()->empty()){
            cout<<"Player: "
            <<game_engine_->GetPlayers()->at(i)->GetPlayerName()
            <<endl
            <<"Countries owned: "
            <<game_engine_->GetPlayers()->at(i)->GetPlayersCountries()->size()
            <<endl
            <<"% Map Conquered: "
            <<game_engine_->GetPlayers()->at(i)->GetPlayersCountries()->size() /
            game_engine_->GetPlayers()->at(i)->GetGameMap()->GetCountries()->size()
            <<endl;
        }
        //Display winning message if a player owns the same amount of countries the map has
        if(game_engine_->GetPlayers()->at(i)->GetPlayersCountries()->size() ==
        game_engine_->GetPlayers()->at(i)->GetGameMap()->GetCountries()->size())
            cout<<"Congrulations "
            <<game_engine_->GetPlayers()->at(i)->GetPlayerName()
            <<" has won the game!"
            <<endl;

    }
}

// TODO:
//This is an incorrect implementation of the Observer patten. The Subject class should be an abstract interface.
// The Observable Class should have implementations here instead. I left this here so you could see but code should be removed

//------------------------------------Subject-----------------------------
//Subject::Subject(){
//    observers_ = new vector<Observer*>;
//}
//
//Subject::~Subject(){
//    delete observers_;
//}
//
//void Subject::Attach(Observer* o){
//    observers_->push_back(o);
//}
//
//void Subject::Detach(Observer* o){
//
//}
//
//void Subject::Notify(){
//    vector<Observer*>::iterator i = observers_->begin();
//    for (; i!= observers_->end(); ++i)
//        (*i)->Update();
//}


//Observable class -----------------------------------------------------------------------------------------------------

Observable::Observable() {
    observers_ = new vector<Observer*>;
}

Observable::Observable(const Observable &observable) {
    observers_ = observable.observers_;

    for(int i = 0; i < observable.observers_->size(); ++i) {
        observers_[i] = observable.observers_[i];
    }
}

Observable::~Observable() {
    for(Observer* observer : *observers_) {
        observer = nullptr;
        delete observer;
    }

    observers_ = nullptr;
    delete[] observers_;
}

Observable& Observable::operator=(const Observable& observable){
    observers_ = observable.observers_;

    for(int i = 0; i < observable.observers_->size(); ++i) {
        observers_[i] = observable.observers_[i];
    }

    return *this;
}

void Observable::Register(Observer *o) {
    observers_->push_back(o);
    //TODO: implementation
}
void Observable::Unregister(Observer *o) {
    auto iterator = std::find(observers_->begin(), observers_->end(), o);

    if(iterator != observers_->end()){
        observers_->erase(iterator);
    }
    //TODO: implementation
}

//You may need to add parameters to this as needed
void Observable::Notify() {

    //TODO: implementation
};
