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
        new_game->TestAutoLoadMapAndCreateGame("../MapLoader/domination-map-files/generaltest.map", 1, 1 ,0);

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

    static void TestConquestMapLoader(string file_name, bool display_adjacency_matrix) {
        cout << "\nTesting Conquest Map Loader...\n";
        // create conquest map loader object (adaptee)
        ConquestMapLoader* conquest_map_loader = new ConquestMapLoader(file_name);

        // create an adapter object
        cout << "Creating adapter object to load map file .... \n";
        MapLoader* adapter = new Adapter(conquest_map_loader);

        // implicitly call ParseConquestMap from the adapter
        cout << "Parsing the conquest map file by implicitly through ParseMap() of adapter object\n";
        bool is_success = adapter->ParseMap();

        if(!is_success) {
            cout << "* * * * * * * Failed to read map file! * * * * * * * \n";
            return;
        }

        Map* parsed_map = conquest_map_loader->GetParsedConquestMap();

        if(!parsed_map) {
            cout << "Something went wrong! Parsed map file is empty\n";
            return;
        }

        if(display_adjacency_matrix) {
            cout << "Here is the resulting adjacency matrix: " << endl;
            parsed_map->DisplayAdjacencyMatrix();
        } else {
            cout << "Map file was successfully read!\n";
        }

        cout <<  endl;
        cout <<  endl;
    }

    static void TestMapFiles() {
        //Testing various files to verify Conquest Map Loader functionality
        Tester::TestConquestMapLoader("../MapLoader/conquest-map-files/Alberta.map", false);
        Tester::TestConquestMapLoader("../MapLoader/conquest-map-files/Canada.map", false);
        Tester::TestConquestMapLoader("../MapLoader/conquest-map-files/Africa.map", false);
        Tester::TestConquestMapLoader("../MapLoader/conquest-map-files/GeneralTest.map", false);

        //Display Adjancency matrix for one of the valid files to ensure map was properly parsed
        Tester::TestConquestMapLoader("../MapLoader/conquest-map-files/Asia.map", true);

        //Testing bad files to make sure they fail to load:
        Tester::TestConquestMapLoader("../MapLoader/conquest-map-files/empty.map", false);
        Tester::TestConquestMapLoader("../MapLoader/conquest-map-files/missing-continents.map", false);
        Tester::TestConquestMapLoader("../MapLoader/conquest-map-files/missing-territories.map", false);
        Tester::TestConquestMapLoader("../MapLoader/conquest-map-files/too-many-connected-territories.map", false);
        Tester::TestConquestMapLoader("../MapLoader/conquest-map-files/too-many-continents.map", false);
        Tester::TestConquestMapLoader("../MapLoader/conquest-map-files/too-many-territories.map", false);
    }

};

int main() {

    string do_test = "";
    do {
        Utility::ClearScreen();
        int user_response;
        cout << endl;
        cout << "Test Player Strategies       |  1\n";
        cout << "Test Phase Observer          |  2\n";
        cout << "Test Game Statistic Observer |  3\n";
        cout << "Test Conquest Map Loader     |  4\n\n";


        cout << "Please Select what you would like to test (enter the corresponding number):\n";

        while (!(cin >> user_response) || user_response < 1 || user_response > 4) {
            cin.clear();
            cin.ignore(132, '\n');
            cout << "Invalid selection. Please try again: ";
        }

        switch (user_response) {
            case 1 :
                Tester::TestComputerPlayers();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                Tester::TestMapFiles();
                break;
            default:
                break;
        }

        cout << "\nWould you like to conduct another test? enter 'y' (enter any other key to quit): ";


        while(!(cin >> do_test)) {
            cin.clear();
            cin.ignore(132, '\n');
            cout << "Invalid input give. Please try again: ";
        }

    } while(do_test == "y");

    return 0;
}