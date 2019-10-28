/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <iostream>
#include <string>
#include <filesystem>

using namespace std;

#include "GameEngine.h"

GameEngine::GameEngine() {

}

GameEngine::GameEngine(const GameEngine& game_engine) {

}

GameEngine::~GameEngine() {

}

GameEngine& GameEngine::operator=(const GameEngine& game_engine) {


    return *this;
}

inline Map* GameEngine::GetGameMap() const {
    return game_map_;
}

inline vector<Cards*>* GameEngine::GetCardsDeck() const {
    return cards_deck_;
}

inline vector<Player*>* GameEngine::GetPlayers() const {
    return players_;
}

inline int GameEngine::GetNumPlayers() const {
    return num_of_players_;
}

void GameEngine::SelectMap() const {

    string user_response;
    cout << "Please select  a map file that you would like to load for the game: " << endl;

   string path = "../MapLoader/test-map-files/";
    for (const auto & entry : filesystem::directory_iterator(path)) {

        cout << entry.path() << endl;
    }

    cin >> user_response;
}

void GameEngine::SelectNumOfPlayers() {

}

void GameEngine::LoadSelectedMap() {

}

void GameEngine::CreatePlayers() {

}

void GameEngine::AssignDiceToPlayer(Player* player) {

}

void GameEngine::AssignHandOfCardsToPlayer(Player* player) {

}

void GameEngine::CreateCardsDeck() {

}