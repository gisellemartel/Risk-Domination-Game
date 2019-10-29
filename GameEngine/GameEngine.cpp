/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <algorithm>
#include <iterator>
#include <filesystem>
#include <random>

using namespace std;

#include "GameEngine.h"

// STARTUP PHASE CLASS ------------------------------------------------------------------------------------------------

StartupPhase::StartupPhase() {
    player_order_ = new map<Player*, int>;
}

StartupPhase::StartupPhase(const StartupPhase& startup_phase) {
    player_order_ = startup_phase.player_order_;

    for(map<Player*, int>::iterator it = startup_phase.player_order_->begin(); it != startup_phase.player_order_->end(); ++it) {
        player_order_->insert(*it);
    }
}

StartupPhase::~StartupPhase() {
    delete player_order_;
}

StartupPhase& StartupPhase::operator=(const StartupPhase& startup_phase) {
    player_order_ = startup_phase.player_order_;

    for(const auto& it : *startup_phase.player_order_) {
        player_order_->insert(it);
    }

    return *this;
}

map<Player*, int>* StartupPhase::GetPlayerOrderMap() const {
    return player_order_;
}

void StartupPhase::RandomlyDeterminePlayerOrder(vector<Player*>* players) {
    cout << "Assigning random order to determine turn of each player at game start:\n";
    vector<int> random_order;
    int random = GenerateRandomNumInRange(0, players->size());

    while(!HasValue(random_order, random) || random_order.size() < players->size()) {
        random = GenerateRandomNumInRange(0, players->size());
        if(!HasValue(random_order, random)) {
            random_order.push_back(random);
        }
    }

    for (int i = 0; i < players->size(); ++i) {
        player_order_->insert(std::pair<Player*, int>((*players)[random_order[i]], i));
    }


    //print the players in the generated order
    for(map<Player*, int>::iterator it = player_order_->begin(); it != player_order_->end(); ++it) {
        Player* player = dynamic_cast<Player*>(it->first);

        for(int i = 0; i < players->size(); ++i ) {
            if(player && player == (*players)[i]) {
                cout << *player->GetPlayerName() << ": " << (it->second + 1) << "\n";
            }
        }
    }

    cout << endl;
}


void StartupPhase::AssignCountriesToAllPlayer(vector<Player*>* players, vector<Country*>* countries_to_assign) {
    if(players->empty() || countries_to_assign->empty()) {
        return;
    }

    cout << "Assigning random countries to each player in round-robin fashion:\n";

    int num_countries = countries_to_assign->size();
    int current_turn = 0;

    //assign countries to each player in round robin fashion
    while(num_countries > 0) {

        cout << "Current turn: " << (current_turn + 1) << ". ";

        for (auto &it : *player_order_) {
            //find the player whose is currently to be assigned countries
            if (it.second == current_turn) {
                //calculate the number of countries to assign to current player
                int num_countries_to_assign = (int) (num_countries / (players->size() - current_turn));
                num_countries -= num_countries_to_assign;

                //assign countries to the player
                cout << "Assigning " << num_countries_to_assign << " countries to " << *it.first->GetPlayerName() << endl;

                //TODO countries should be assigned in random and not in order
                for (int i = 0; i < num_countries_to_assign; ++i) {
                    it.first->AddCountryToCollection((*countries_to_assign)[i]);
                }
            }

        }

        //get the current players turn
        current_turn = (int)((current_turn + 1) % players->size());
    }
    cout << endl;
}

//static helper methods --------------------------------------------------------
int StartupPhase::GenerateRandomNumInRange(int lower_bound, int upper_bound) {
    std::uniform_real_distribution<double> distribution(lower_bound, upper_bound);
    std::random_device rd;
    std::default_random_engine generator( rd() );
    return distribution(generator);
}

bool StartupPhase::HasValue(const vector<int>& values, const int value) {
    for(int i : values) {
        if(i == value) {
            return true;
        }
    }
    return false;
}

// GAME ENGINE CLASS --------------------------------------------------------------------------------------------------
GameEngine::GameEngine() {
    game_map_ = nullptr;
    cards_deck_ = nullptr;
    players_ = new vector<Player*>;
    //2 players by default
    num_of_players_ = 2;
    exit_game_ = false;
    file_paths_ = new vector<filesystem::path>;
}

GameEngine::GameEngine(const GameEngine& game_engine) {
    game_map_ = game_engine.game_map_;

    cards_deck_ = game_engine.cards_deck_;

    players_ = game_engine.players_;
    for (size_t i = 0; i < game_engine.players_->size(); ++i) {
        players_[i] = game_engine.players_[i];
    }

    file_paths_ = game_engine.file_paths_;
    for (size_t i = 0; i < game_engine.file_paths_->size(); ++i) {
        file_paths_[i] = game_engine.file_paths_[i];
    }


    num_of_players_ = game_engine.num_of_players_;
    exit_game_ = game_engine.exit_game_;
}

GameEngine::~GameEngine() {

    for (auto& player : *players_) {
        player = nullptr;
        delete player;
    }

    for (auto& filepath : *file_paths_) {
        filepath = nullptr;
    }

    game_map_ = nullptr;
    cards_deck_ = nullptr;
    players_ = nullptr;
    file_paths_ = nullptr;

    delete players_;
    delete file_paths_;
    delete cards_deck_;
    delete game_map_;
}

GameEngine& GameEngine::operator=(const GameEngine& game_engine) {
    game_map_ = game_engine.game_map_;

    cards_deck_ = game_engine.cards_deck_;

    players_ = game_engine.players_;
    for (size_t i = 0; i < game_engine.players_->size(); ++i) {
        players_[i] = game_engine.players_[i];
    }

    file_paths_ = game_engine.file_paths_;
    for (size_t i = 0; i < game_engine.file_paths_->size(); ++i) {
        file_paths_[i] = game_engine.file_paths_[i];
    }

    num_of_players_ = game_engine.num_of_players_;

    exit_game_ = game_engine.exit_game_;

    return *this;
}

MapLoader* GameEngine::GetGameMap() const {
    return game_map_;
}

Deck* GameEngine::GetCardsDeck() const {
    return cards_deck_;
}

vector<Player*>* GameEngine::GetPlayers() const {
    return players_;
}

int GameEngine::GetNumPlayers() const {
    return num_of_players_;
}

bool GameEngine::ExitGameSelected() const {
    return exit_game_;
}

bool GameEngine::SelectMap() {

    exit_game_ = false;
    string path;

    do {
        cout << "Please enter the name of the directory you would like to load a map file from (enter 'exit' to leave): ";
        cin >> path;

        if(path == "exit") {
            exit_game_ = true;
            break;
        }
        filesystem::directory_iterator iterator;

        try {
            iterator = filesystem::directory_iterator(path);

            for (const auto& entry : iterator) {
                if (entry.path().extension() == ".map") {
                    file_paths_->push_back(entry.path());
                }
            }

            if(file_paths_->empty()) {
                cout << "No files of .map type found in directory! Invalid directory.";
                cin.clear();
                cin.ignore(132,'\n');
            } else {
                cout << "\n\nHere are the entries found in directory \"" << path << "\"\n\n";
                //Load the map file
                game_map_ = SelectFile();

                return game_map_ != nullptr;
            }
        }
        catch (filesystem::filesystem_error& error) {
            cout << "Invalid directory.";
            cin.clear();
            cin.ignore(132,'\n');
        }
        cout << endl << endl;
    } while (!exit_game_);

    return false;
}

MapLoader* GameEngine::SelectFile() {
    int user_selection = 0;
    int counter = 1;
    for(const auto& map_filepath : *file_paths_) {
        cout << "File " << counter << ": " << map_filepath.filename().string() << endl;
        ++counter;
    }

    cout << "\nTo select a file, enter its corresponding number here: (enter -1 to exit) ";

    while(!(cin >> user_selection) || user_selection < 1 || user_selection > file_paths_->size()) {
        if(user_selection == -1) {
            exit_game_ = true;
            return nullptr;
        }
        cin.clear();
        cin.ignore(132, '\n');
        cout << "Error! Please enter a valid file number: ";
    }

    string file_to_load = (*file_paths_)[user_selection - 1].string();

    cout << "Now loading map file: " << file_to_load << "..." << endl;
    //Load the map file
    return new MapLoader(file_to_load);
}

bool GameEngine::LoadSelectedMap() {
    if(game_map_) {
        while(!game_map_->ParseMap() && !exit_game_) {
            game_map_ = SelectFile();

            if(!game_map_) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

void GameEngine::SelectNumOfPlayers() {
    int num_players = -1;

    cout << "Please enter the number of players joining the game (between 2 and 6 players per game): ";
    while(!(cin >> num_players) || num_players < 2 || num_players > 6) {
        cout << "Invalid number of players entered. Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    num_of_players_ = num_players;
}

void GameEngine::CreatePlayers() {

    if(!game_map_) {
        cout << "Error! Cannot create players for game until valid Map has been selected and loaded\n";
        return;
    }

    if(num_of_players_ < 2 || num_of_players_ > 6) {
        //something went wrong. Set number of players to default value of 2
        num_of_players_ = 2;
    }

    cout << "Creating " << num_of_players_ << " players for new game...\n";
    for(size_t i = 0; i < num_of_players_; ++i) {
        string player_name = "Player " + std::to_string(i + 1);

        players_->push_back(new Player(player_name));
    }
}

void GameEngine::AssignDiceToPlayers() {
    if(!game_map_) {
        cout << "Error! Cannot create players for game until valid Map has been selected and loaded\n";
        return;
    }

    if(players_->empty()) {

        cout << "No Player created to assign dice to! Please try again\n";
        return;
    }

    cout << "Assigning dice rolling mechanism for each player...\n";
    for(Player* player: *players_) {
        player->SetPlayerDice(new Dice);
    }

}

void GameEngine::AssignHandOfCardsToPlayers() {
    if(!game_map_) {
        cout << "Error! Cannot create players for game until valid Map has been selected and loaded\n";
        return;
    }

    if(players_->empty()) {
        cout << "No Player created to assign hand of cards to! Please try again\n";
        return;
    }

    cout << "Assigning empty hand of cards for each player...\n";
    for(Player* player: *players_) {
        player->SetPlayerHand(new Hand);
    }
}

void GameEngine::CreateCardsDeck() {
    if(!game_map_) {
        cout << "Error! Cannot create players for game until valid Map has been selected and loaded\n";
        return;
    }

    cout << "Creating deck of cards for new game...\n";
    cards_deck_ = new Deck();
    int num_cards = game_map_->GetParsedMap()->GetNumCountries();
    cards_deck_ ->CreateDeck(num_cards);
}

void GameEngine::DisplayCurrentGame() {
    cout << "There are " << num_of_players_ << " players participating in this game. Here are their stats:\n";
    for(const Player* player : *players_) {
        player->DisplayPlayerStats();
        cout << endl;
    }

    cout << "There are " << game_map_->GetParsedMap()->GetNumCountries() << " countries in the loaded map and " << cards_deck_->GetNumberOfCardsInDeck() << " cards in the created deck\n\n";

//    cout << "Displaying generated deck of cards:\n";
//    cards_deck_->DisplayDeck();
//
//    cout << endl;
//
//    cout << "\nDisplaying Countries of map:" << endl;
//    game_map_->GetParsedMap()->DisplayCountries();
//
//    cout << "\n\nDisplaying Continents of map:" << endl;
//    game_map_->GetParsedMap()->DisplayContinents();
    cout << endl;
}