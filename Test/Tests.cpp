//
// Created by Giselle Martel on 2019-11-17.
//
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

#include "../GameEngine/GameObservers.h"
#include "../GameEngine/GameEngine.h"
#include "../MapLoader/Adapter.h"

class Tester {

public:

    static void TestDynamicBehaviours() {

        cout << "\nTesting Dynamic Player Behaviour with Phase Observer...\n";

        GameEngine* new_game = new GameEngine();
        Observer* observer = new PhaseObserver();
        new_game->Register(observer);

        //test with 1 human players and an aggressive player
        new_game->TestAutoLoadMapAndCreateGame("../MapLoader/domination-map-files/generaltest.map", 1, 0 ,0, 1, 0);

        Player* human = nullptr;
        Player* bot = nullptr;

        for(Player* player : *new_game->GetPlayers()) {
            if(player->IsHuman()) {
                human = player;
            } else {
                bot = player;
            }
        }

        if(!human || !bot) {
            return;
        }

        cout<< "\n\nTesting human player with reinforce...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        human->Reinforce();
        cout << "\n\n\nDynamically changing behaviour of "  << *human->GetPlayerName() << " to random player. Will execute Reinforce phase again ... \n\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        ConcreteStrategies* strategies1 = new RandomComputerPlayerStrategy;
        human->SetPlayerStrategy(strategies1);
        human->Reinforce();

        cout<< "\n\nTesting Random player with reinforce...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        bot->Reinforce();
        cout << "\n\n\nDynamically changing behaviour of " << *bot->GetPlayerName() << " to human player, Will execute Reinforce phase again... \n\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        ConcreteStrategies* strategies2 = new HumanPlayerStrategy;
        bot->SetPlayerStrategy(strategies2);
        bot->Reinforce();

        new_game->Unregister(observer);


        // test with human and benevolant player
        new_game = new GameEngine();
        observer = new PhaseObserver();
        new_game->Register(observer);

        //test with 1 human players and an aggressive player
        new_game->TestAutoLoadMapAndCreateGame("../MapLoader/domination-map-files/generaltest.map", 1, 0 ,0, 0, 1);

        human = nullptr;
        Player* cheater = nullptr;

        for(Player* player : *new_game->GetPlayers()) {
            if(player->IsHuman()) {
                human = player;
            } else {
                bot = player;
            }
        }

        if(!human || !bot) {
            return;
        }

        cout<< "\n\nTesting human player with reinforce...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        human->Reinforce();
        cout << "\n\n\nDynamically changing behaviour of "  << *human->GetPlayerName() << " to Cheater player. Will execute Reinforce phase again ...\n\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        strategies1 = new CheaterComputerPlayerStrategy;
        human->SetPlayerStrategy(strategies1);
        human->Reinforce();


        cout<< "\n\nTesting Cheater player with reinforce...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        bot->Reinforce();
        cout << "\n\n\nDynamically changing behaviour of " << *bot->GetPlayerName() << " to benevolant player. Will execute Reinforce phase again ...\n\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        strategies2 = new BenevolantComputerPlayerStrategy;
        bot->SetPlayerStrategy(strategies2);
        bot->Reinforce();

        new_game->Unregister(observer);

        observer = nullptr;
        strategies1 = nullptr;
        strategies2 = nullptr;
        new_game = nullptr;

        delete strategies1;
        delete strategies2;
        delete observer;
        delete new_game;

        cout << "\n\nFinished Testing dynamic behaviours...\n\n";
        Utility::ClearScreen();
    }

    static void TestPlayerStrategiesWithPhaseObserver() {
        cout << "\n\nTesting Player Strategies with Phase Observer...\n\n";
        GameEngine* new_game = new GameEngine();
        Observer* observer = new PhaseObserver();
        new_game->Register(observer);

        new_game->TestAutoLoadMapAndCreateGame("../MapLoader/domination-map-files/kosova.map", 1, 1 ,1, 1, 1);

        new_game->GetLoadedMap()->GetParsedMap()->DisplayAdjacencyMatrix();
        for(Player* player : *new_game->GetPlayers()) {
            cout << *player->GetPlayerName() << endl;
            player->DisplayCountries();
        }

        for(Player* player : *new_game->GetPlayers()) {
            player->DisplayCountries();
            player->Reinforce();
            player->DisplayCountries();
            player->Attack();
            player->DisplayCountries();
            player->Fortify();
        }

        new_game->Unregister(observer);

        observer = nullptr;
        new_game = nullptr;
        delete observer;
        delete new_game;
    }

    static void TestGameStatisticsObserver() {
        cout << "\nTesting GameStatistics Observer...\n";

        GameEngine* new_game = new GameEngine;

        Observer* observer = new GameStatisticObserver(new_game->GetPlayers());

        new_game->Register(observer);

        new_game->TestAutoLoadMapAndCreateGame("../MapLoader/domination-map-files/kosova.map", 0, 0, 0, 1, 1);

        new_game->StartGameLoop();

        //Should pass message to notify: "as soon as a player owns all the countries, the game statistics view updates itself and displays a celebratory message"
        new_game->Notify("Game Test Over");

        new_game->Unregister(observer);

        new_game = nullptr;
        observer = nullptr;

        delete new_game;
        delete observer;
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

    static void TestGameTournament() {
        cout << "\n\nTesting Game Tournament...\n\n";
        GameEngine* new_game = new GameEngine();

        new_game->CreateNewGame();

        cout << "\n\nFinished Testing Game Tournament...\n\n";

        new_game = nullptr;
        delete new_game;
    }

};

int main() {

    string do_test = "";
    do {
        Utility::ClearScreen();
        int user_response;
        cout << endl;
        cout << "Test Game Tournament w/ Phase Observer      |  0\n";
        cout << "Test Dynamic Strategies w/ Phase Observer   |  1\n";
        cout << "Test Different Strategies w/ Phase Observer |  2\n";
        cout << "Test GameLoop with Game Statistic Observer  |  3\n";
        cout << "Test Conquest Map Loader                    |  4\n\n";


        cout << "Please Select what you would like to test (enter the corresponding number):\n";

        while (!(cin >> user_response) || user_response < 0 || user_response > 4) {
            cin.clear();
            cin.ignore(132, '\n');
            cout << "Invalid selection. Please try again: ";
        }

        switch (user_response) {
            case 0 :
                Tester::TestGameTournament();
                break;
            case 1 :
                Tester::TestDynamicBehaviours();
                break;
            case 2:
                Tester::TestPlayerStrategiesWithPhaseObserver();
                break;
            case 3:
                Tester::TestGameStatisticsObserver();
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