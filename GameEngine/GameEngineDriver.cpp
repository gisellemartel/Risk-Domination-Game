/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <iostream>

using namespace std;

#include "GameEngine.h"

int main() {

    cout << "Game Engine Driver" << endl;

    GameEngine* game_engine = new GameEngine;

    if( game_engine->SelectMap() && game_engine->LoadSelectedMap()) {
        game_engine->SelectNumOfPlayers();

        game_engine->CreatePlayers();

        game_engine->CreateCardsDeck();
        game_engine->AssignHandOfCardsToPlayers();
        game_engine->AssignDiceToPlayers();
        game_engine->DisplayCurrentGame();
    }

    game_engine = nullptr;
    delete game_engine;

    return 0;
}