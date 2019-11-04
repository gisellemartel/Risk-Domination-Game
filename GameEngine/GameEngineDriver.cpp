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

    //DEBUG TEST CODE PART 4, 5, 6
    game_engine->LoadMapDebugTest();


//
//    while(!game_engine->ExitGameSelected()) {
//        if( game_engine->SelectMap() && game_engine->LoadSelectedMap()) {
//            cout << endl;
//            game_engine->SelectNumOfPlayers();
//
//            game_engine->CreatePlayers();
//
//            game_engine->CreateCardsDeck();
//            game_engine->AssignHandOfCardsToPlayers();
//            game_engine->AssignDiceToPlayers();
//
//            cout << endl;
//
//            //game_engine->DisplayCurrentGame();
//
//            game_engine->GetGameStart()->RandomlyDeterminePlayerOrder(game_engine->GetPlayers());
//            game_engine->GetGameStart()->AssignCountriesToAllPlayers(game_engine->GetPlayers(), game_engine->GetGameMap()->GetParsedMap()->GetCountries());
//            game_engine->GetGameStart()->AssignArmiesToAllPlayers(game_engine->GetPlayers());
//
//            game_engine->DisplayCurrentGame();
//            break;
//        } else if (game_engine->ExitGameSelected()) {
//            return 0;
//        }
//    }

    game_engine = nullptr;
    delete game_engine;

    return 0;
}