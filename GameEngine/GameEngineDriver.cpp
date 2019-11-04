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

    //DEBUG TEST CODE
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

    vector<Player*>* playerlist = new vector<Player*>;
    Player* player1 = new Player("player1");
    Player* player2 = new Player("player2");
    Player* player3 = new Player("player3");
    playerlist->push_back(player1);
    playerlist->push_back(player2);
    playerlist->push_back(player3);

    //Player has Countries
    player1->AddCountryToCollection(new Country(1, new string("Canada"), 1));
    player1->AddCountryToCollection(new Country(2, new string("US"), 1));
    player1->AddCountryToCollection(new Country(3, new string("Mexico"), 1));
    cout << "\nPlayer " << *player1->GetPlayerName() << " owns collection of following countries: " << endl;
    for(Country* country : *player1->GetPlayersCountries()) {
        cout << *country->GetCountryName() << endl;
    }

    //Player has Cards
    player1->AddCardToCollection(new Cards("calvary"));
    player1->AddCardToCollection(new Cards("infantry"));
    player1->AddCardToCollection(new Cards("artillery"));
    cout << "\nPlayer owns collection of following cards: " << endl;

    player1->GetPlayersCards()->DisplayHand();
    GameLoop* gameloop = new GameLoop(playerlist);
    gameloop->StartLoop();
    return 0;
}