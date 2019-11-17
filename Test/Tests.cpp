//
// Created by Giselle Martel on 2019-11-17.
//
#include <iostream>

using namespace std;

#include "../GameObservers/GameObservers.h"
#include "../GameEngine/GameEngine.h"

class Tester {

public:

    static void TestComputerPlayers() {

        GameEngine* new_game = new GameEngine();
        PhaseObserver* observer = new PhaseObserver();
        new_game->Register(observer);

        //test with 1 human players and an aggressive player
        new_game->TestAutoLoadMapAndCreateGame("../MapLoader/test-map-files/generaltest.map", 1, 1 ,0);

        //repeat game 10 times
        for(int i = 0; i < 10; ++i) {
            for(Player* player : *new_game->GetPlayers()) {
                player->Reinforce();
                player->Attack();
                player->Fortify();
            }
        }

//    // test with 2 aggressive and 1 benevolant player


//    new_game->TestAutoLoadMapAndCreateGame("../MapLoader/test-map-files/generaltest.map", 0, 2,1);
//    new_game->StartGameLoop();

//    //test with 2 human players
//    new_game->TestAutoLoadMapAndCreateGame("../MapLoader/test-map-files/generaltest.map", 2, 0 ,0);
//    new_game->StartGameLoop();



//
//    // test with one of each
//    new_game->TestAutoLoadMapAndCreateGame("../MapLoader/test-map-files/generaltest.map", 1, 1,1);
//    new_game->StartGameLoop();
//
//    //test with 2 aggressive players
//    new_game->TestAutoLoadMapAndCreateGame("../MapLoader/test-map-files/generaltest.map", 0, 2,0);
//    new_game->StartGameLoop();
//
//    // test with 2 benevolant players
//    new_game->TestAutoLoadMapAndCreateGame("../MapLoader/test-map-files/generaltest.map", 0, 0,2);
//    new_game->StartGameLoop();
//
//    // test that behaviour of a give player can be changed dynamically at runtime
//    new_game->TestAutoLoadMapAndCreateGame("../MapLoader/test-map-files/generaltest.map", 1, 1,1);
//    new_game->StartGameLoop();

        new_game->Unregister(observer);
        new_game = nullptr;
        delete new_game;

    }

    static void TestPhaseObserver() {

        GameEngine* new_game = new GameEngine();
        PhaseObserver* observer = new PhaseObserver();
        new_game->Register(observer);

        //test with 1 human players and an aggressive player
        new_game->TestAutoLoadMapAndCreateGame("../MapLoader/test-map-files/generaltest.map", 1, 1 ,0);

        //repeat game 10 times
        for(int i = 0; i < 10; ++i) {
            for(Player* player : *new_game->GetPlayers()) {
                player->Reinforce();
                player->Attack();
                player->Fortify();
            }
        }

        new_game->Unregister(observer);

    }
};

int main() {

    Tester::TestComputerPlayers();

    return 0;
}