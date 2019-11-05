/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <iostream>

using namespace std;

#include "GameEngine.h"
#include "../Player/Player.h"
#include "../Map/Map.h"

int main() {

    cout << "Game Engine Driver" << endl;


    GameEngine* game_engine = new GameEngine;


    // Testing Game Engine and game Startup  ---------------------------------------------------------------------------
//
//    while(!game_engine->ExitGameSelected()) {
//        if( game_engine->SelectMap() && game_engine->LoadSelectedMap()) {
//            cout << endl;
//
//            //Part 1-----------------------------
//            game_engine->SelectNumOfPlayers();
//            game_engine->CreatePlayers();
//            game_engine->CreateCardsDeck();
//            game_engine->AssignHandOfCardsToPlayers();
//            game_engine->AssignDiceToPlayers();
//
//            cout << endl;
//
//            //Part 2----------------------------------------------------------------------------
//            game_engine->GetGameStart()->RandomlyDeterminePlayerOrder(game_engine->GetPlayers());
//            game_engine->GetGameStart()->AssignCountriesToAllPlayers(game_engine->GetPlayers(), game_engine->GetLoadedMap()->GetParsedMap()->GetCountries());
//            game_engine->GetGameStart()->AssignArmiesToAllPlayers(game_engine->GetPlayers());
//
//            game_engine->DisplayCurrentGame();
//            break;
//        } else if (game_engine->ExitGameSelected()) {
//            return 0;
//        }
//    }

    // -----------------------------------------------------------------------------------------------------------------



    // Testing Player --------------------------------------------------------------------------------------------------

    game_engine->TestAutoLoadMapAndCreateGame("maploader/test-map-files/google.map");

    //Test game loop
    GameLoop* gameloop = new GameLoop(game_engine->GetPlayers());
    gameloop->StartLoop();

//    //Test Reinforce
//    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%-------- Testing the Reinforce phase --------%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
//    for(Player* player : *game_engine->GetPlayers()) {
//        player->Reinforce();
//    }
//
//    cout << endl << endl;
//
//    //Test Attack
//    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%-------- Testing the Attack phase --------%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
//    for(Player* player : *game_engine->GetPlayers()) {
//        player->Attack();
//    }
//
//    cout << endl << endl;
//
//    //Test Fortify
//    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%-------- Testing the Fortify phase --------%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
//    for(Player* player : *game_engine->GetPlayers()) {
//        player->Fortify();
//    }


    game_engine = nullptr;
    delete game_engine;

    return 0;
}