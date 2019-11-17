/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <iterator>
#include <filesystem>
#include <random>

using namespace std;

#include "GameEngine.h"


// STARTUP PHASE CLASS ------------------------------------------------------------------------------------------------

// generic function which randomized order of passed vector.
// used to randomize both order of players, order in which countries are assigned
template<class V>
vector<int> StartupPhase::GenerateRandomizedIndicesForVector(const vector<V*>& vector_to_randomize) {
    int random = Utility::GenerateRandomNumInRange(0, vector_to_randomize.size());
    vector<int> random_order;
    //randomize the order for the indices in the players vector
    while(!Utility::HasValue(random_order, random) || random_order.size() < vector_to_randomize.size()) {
        random = Utility::GenerateRandomNumInRange(0, vector_to_randomize.size());
        if(!Utility::HasValue(random_order, random)) {
            random_order.push_back(random);
        }
    }
    return random_order;
}

// class constructors
StartupPhase::StartupPhase() {
    player_order_ = new map<Player*, int>;
    current_player_index_ = 0;
}

StartupPhase::StartupPhase(const StartupPhase& startup_phase) {
    player_order_ = startup_phase.player_order_;

    for(map<Player*, int>::iterator it = startup_phase.player_order_->begin(); it != startup_phase.player_order_->end(); ++it) {
        player_order_->insert(*it);
    }
    current_player_index_ = startup_phase.current_player_index_;
}

StartupPhase::~StartupPhase() {
    delete [] player_order_;
}


//operator overloader
StartupPhase& StartupPhase::operator=(const StartupPhase& startup_phase) {
    player_order_ = startup_phase.player_order_;

    for(const auto& it : *startup_phase.player_order_) {
        player_order_->insert(it);
    }
    current_player_index_ = startup_phase.current_player_index_;
    return *this;
}


//Getters
map<Player*, int>* StartupPhase::GetPlayerOrderMap() const {
    return player_order_;
}


//Setters
void StartupPhase::SetNumberOfArmies(int number_of_players) {
    switch(number_of_players) {
        case -1: number_of_armies_ = 5; //for testing only
            break;
        case 2: number_of_armies_ = 40;
            break;
        case 3: number_of_armies_ = 35;
            break;
        case 4: number_of_armies_ = 30;
            break;
        case 5: number_of_armies_ = 25;
            break;
        case 6: number_of_armies_ = 20;
            break;
        default:
            number_of_armies_ = 40;
    }
}


//class methods
void StartupPhase::RandomlyDeterminePlayerOrder(vector<Player*>* players) {
    cout << "Assigning random order to determine turn of each player at game start:\n";
    //generate vector of indices which will contain randomized order of players
    vector<int> random_order = GenerateRandomizedIndicesForVector(*players);

    //assign the generated random order to each player
    for (int i = 0; i < players->size(); ++i) {
        player_order_->insert(std::pair<Player*, int>((*players)[random_order[i]], i));
    }

    //print the players in the generated order
    for(map<Player*, int>::iterator it = player_order_->begin(); it != player_order_->end(); ++it) {
        Player* player = dynamic_cast<Player*>(it->first);

        for(int i = 0; i < players->size(); ++i ) {
            if(player && player == (*players)[i]) {
                //set the turn for the current player
                (*players)[i]->SetPlayersTurn(it->second == current_player_index_);
                //display order for current player
                cout << *player->GetPlayerName() << ": " << (it->second + 1) << "\n";
            }
        }
    }

    cout << endl;
}

void StartupPhase::AssignCountriesToAllPlayers(vector<Player*>* players, vector<Country*>* countries_to_assign) {
    if(players->empty() || countries_to_assign->empty()) {
        return;
    }

    cout << "Assigning random countries to each player in round-robin fashion:\n";

    int num_countries = countries_to_assign->size();

    //generate vector of indices which will contain randomized order of countries
    vector<int> random_order = GenerateRandomizedIndicesForVector(*countries_to_assign);
    //index used to track current position within countries vector after each loop iteration
    size_t current_index = 0;
    //assign countries to each player in round robin fashion
    while(num_countries > 0) {

        //debug string
        cout << "Current turn: " << (current_player_index_ + 1) << ".\n";

        for (auto &it : *player_order_) {
            //find the player whose is currently to be assigned countries
            if (it.second == current_player_index_) {
                it.first->SetPlayersTurn(true);
                int current_random_index = random_order[current_index];

                //debug string
                cout << "Assigning " << *(*countries_to_assign)[current_random_index]->GetCountryName() << " to " << *(it.first->GetPlayerName()) << endl;

                it.first->AddCountryToCollection((*countries_to_assign)[current_random_index]);
                it.first->SetPlayersTurn(false);
                //update position of current index
                ++current_index;
                --num_countries;
            }
        }

        //get the current players turn
        current_player_index_ = (int)((current_player_index_ + 1) % players->size());
    }
    cout << endl;
}

void StartupPhase::AssignArmiesToAllPlayers(vector<Player*>* players) {

    if(players->empty()) {
        return;
    }

    cout << "* * * * * * * Assigning " << number_of_armies_ << " armies to each player in round-robin fashion... * * * * * * *\n";

    //create vector to track number of armies left to assign for each player
    vector<int> num_armies;
    for(int i = 0; i < players->size(); ++i) {
        num_armies.push_back(number_of_armies_);
    }

    //assign countries to each player in round robin fashion
    while(!Utility::ContainsAllZeros(num_armies)) {
        for (auto &it : *player_order_) {
            //find the player whose is currently to be assigned countries
            if (it.second == current_player_index_) {
                //debug string
                cout << "\nCurrent turn is " << (current_player_index_ + 1) << ". " << *it.first->GetPlayerName() << " can proceed to assign their armies:\n";

                vector<Country*>& players_countries = *it.first->GetPlayersCountries();

                if(players_countries.empty()) {
                    cout << *it.first->GetPlayerName() << " does not own any countries. Going to next turn\n\n";
                    break;
                } else if (num_armies[it.second] == 0) {
                    cout << *it.first->GetPlayerName() << " has no more countries left to assign. Going to next turn\n\n";
                    break;
                }

                it.first->SetPlayersTurn(true);
              //  int random_country_index = GenerateRandomNumInRange(0, it.first->GetPlayersCountries()->size());

                it.first->DisplayCountries();
                cout << "Please choose which country you would like to assign armies to (enter by numerical id):\n";

                int user_selection;
                while(!(cin >> user_selection) || !it.first->DoesPlayerOwnCountry(user_selection)) {
                  cin.clear();
                  cin.ignore(132, '\n');
                  cout << "Invalid entry entered! Please try again: ";
                }

                Country* current_country = it.first->GetCountryById(user_selection);


                if(current_country) {
                    string name_country = *current_country->GetCountryName();
                    cin.clear();
                    cout << "Please enter the number of armies you would like to assign to " << name_country  << " (you currently have " << num_armies[it.second] << " armies remaining to assign)" << endl;
                    while(!(cin >> user_selection) || user_selection < 1 || user_selection > num_armies[it.second]) {
                        cin.clear();
                        cin.ignore(132, '\n');
                        cout << "Invalid value given! Please try again: ";
                    }

                    //debug string
                    cout << "\nAssigning " << user_selection << " armies to " << name_country << "...\n";

                    current_country->SetNumberOfArmies(user_selection + current_country->GetNumberOfArmies());
                    current_country->DisplayInfo();

                    //update number of armies for current player after assignment
                    num_armies[it.second] = num_armies[it.second] - user_selection;

                    it.first->SetPlayersTurn(false);
                }
            }
        }

        //get the current players turn
        current_player_index_ = (int)((current_player_index_ + 1) % players->size());
    }
    cout << endl;
}

void StartupPhase::AutoAssignArmiesToAllPlayers(vector<Player*>* players) {

    if(players->empty()) {
        return;
    }

    cout << "* * * * * * * Assigning " << number_of_armies_ << " armies to each player in round-robin fashion... * * * * * * *\n";

    //create vector to track number of armies left to assign for each player
    vector<int> num_armies;
    for(int i = 0; i < players->size(); ++i) {
        num_armies.push_back(number_of_armies_);
    }

    //assign countries to each player in round robin fashion
    while(!Utility::ContainsAllZeros(num_armies)) {
        for (auto &it : *player_order_) {
            //find the player whose is currently to be assigned countries
            if (it.second == current_player_index_) {
                //debug string
                cout << "\nCurrent turn is " << (current_player_index_ + 1) << ". " << *it.first->GetPlayerName() << " can proceed to assign their armies:\n";

                vector<Country*>& players_countries = *it.first->GetPlayersCountries();

                if(players_countries.empty()) {
                    cout << *it.first->GetPlayerName() << " does not own any countries. Going to next turn\n\n";
                    break;
                } else if (num_armies[it.second] == 0) {
                    cout << *it.first->GetPlayerName() << " has no more countries left to assign. Going to next turn\n\n";
                    break;
                }

                it.first->SetPlayersTurn(true);

                int country_id = Utility::GenerateRandomNumInRange(1, it.first->GetGameMap()->GetCountries()->size());
                while(!it.first->DoesPlayerOwnCountry(country_id)) {
                    country_id = Utility::GenerateRandomNumInRange(1, it.first->GetGameMap()->GetCountries()->size());
                }

                Country* current_country = it.first->GetCountryById(country_id);

                if(current_country) {
                    string name_country = *current_country->GetCountryName();
                    cout << "Auto selected " << name_country << " to assign armies to" << endl;

                    cout << "Auto selecting number of armign to assign to " << name_country  << " (you currently have " << num_armies[it.second] << " armies remaining to assign)..." << endl;

                    int num_armies_to_assign = Utility::GenerateRandomNumInRange(1, num_armies[it.second]);
                    while(num_armies_to_assign < 1 || num_armies_to_assign > num_armies[it.second]) {
                        num_armies_to_assign = Utility::GenerateRandomNumInRange(1, num_armies[it.second]);
                    }

                    //debug string
                    cout << "Assigning " << country_id << " armies to " << name_country << "...\n";

                    current_country->SetNumberOfArmies(num_armies_to_assign + current_country->GetNumberOfArmies());

                    //update number of armies for current player after assignment
                    num_armies[it.second] = num_armies[it.second] - num_armies_to_assign;

                    it.first->SetPlayersTurn(false);
                }
            }
        }

        //get the current players turn
        current_player_index_ = (int)((current_player_index_ + 1) % players->size());
    }
    cout << endl;

}



// GAME ENGINE CLASS --------------------------------------------------------------------------------------------------

//Function purely for testing purposes
void GameEngine::TestAutoLoadMapAndCreateGame(string file_path, int num_human_players, int num_aggressive_players, int num_benevolant_players) {
    exit_game_ = false;
    loaded_map_ = new MapLoader(file_path);
    if(loaded_map_->ParseMap()) {
        num_of_players_ = num_human_players + num_aggressive_players + num_benevolant_players;
        num_of_human_players_ = num_human_players;
        num_aggressive_players_ = num_aggressive_players;
        num_benevolant_players_ = num_benevolant_players;
        CreatePlayers();
        CreateCardsDeck();
        AssignHandOfCardsToPlayers();
        AssignDiceToPlayers();
        game_start_->RandomlyDeterminePlayerOrder(players_);
        game_start_->AssignCountriesToAllPlayers(players_, loaded_map_->GetParsedMap()->GetCountries());
        game_start_->AutoAssignArmiesToAllPlayers(players_);
    }

    for(Player* player : *players_) {
        player->SetGameMap(loaded_map_->GetParsedMap());
    }
}

//private helper methods
MapLoader* GameEngine::SelectFile() {

    cout << "\nTo select a file, enter its corresponding number here: (enter -1 to exit) ";
    int user_selection = 0;
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


//constructors
GameEngine::GameEngine() {
    loaded_map_ = nullptr;
    cards_deck_ = nullptr;
    players_ = new vector<Player*>;
    //2 players by default
    num_of_players_ = 2;
    exit_game_ = false;
    file_paths_ = new vector<filesystem::path>;
    game_start_ = new StartupPhase;
    current_phase_ = GamePhase::Startup;
    observers_ = new vector<Observer*>;
}

GameEngine::GameEngine(const GameEngine& game_engine) {
    loaded_map_ = game_engine.loaded_map_;

    cards_deck_ = game_engine.cards_deck_;

    players_ = game_engine.players_;
    for (size_t i = 0; i < game_engine.players_->size(); ++i) {
        players_[i] = game_engine.players_[i];
    }

    file_paths_ = game_engine.file_paths_;
    for (size_t i = 0; i < game_engine.file_paths_->size(); ++i) {
        file_paths_[i] = game_engine.file_paths_[i];
    }

    observers_ = game_engine.observers_;

    for(int i = 0; i < game_engine.observers_->size(); ++i) {
        observers_[i] = game_engine.observers_[i];
    }

    game_start_ = game_engine.game_start_;
    num_of_players_ = game_engine.num_of_players_;
    exit_game_ = game_engine.exit_game_;
    current_phase_ = game_engine.current_phase_;
}

GameEngine::~GameEngine() {

    for (auto& player : *players_) {
        player = nullptr;
        delete player;
    }

    for (auto& filepath : *file_paths_) {
        filepath = nullptr;
    }

    for (Observer* observer : *observers_) {
        observer = nullptr;
        delete observer;
    }

    loaded_map_ = nullptr;
    cards_deck_ = nullptr;
    players_ = nullptr;
    file_paths_ = nullptr;
    game_start_ = nullptr;
    observers_ = nullptr;

    delete players_;
    delete file_paths_;
    delete cards_deck_;
    delete loaded_map_;
    delete game_start_;
    delete observers_;
}


//operator overloader
GameEngine& GameEngine::operator=(const GameEngine& game_engine) {
    loaded_map_ = game_engine.loaded_map_;

    cards_deck_ = game_engine.cards_deck_;

    players_ = game_engine.players_;
    for (size_t i = 0; i < game_engine.players_->size(); ++i) {
        players_[i] = game_engine.players_[i];
    }

    file_paths_ = game_engine.file_paths_;
    for (size_t i = 0; i < game_engine.file_paths_->size(); ++i) {
        file_paths_[i] = game_engine.file_paths_[i];
    }

    observers_ = game_engine.observers_;
    for(int i = 0; i < game_engine.observers_->size(); ++i) {
        observers_[i] = game_engine.observers_[i];
    }

    num_of_players_ = game_engine.num_of_players_;
    game_start_ = game_engine.game_start_;
    exit_game_ = game_engine.exit_game_;
    current_phase_ = game_engine.current_phase_;

    return *this;
}


//getters
MapLoader* GameEngine::GetLoadedMap() const {
    return loaded_map_;
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

StartupPhase* GameEngine::GetGameStart() const {
    return game_start_;
}

bool GameEngine::ExitGameSelected() const {
    return exit_game_;
}

GamePhase GameEngine::GetCurrentPhase() const {
    return current_phase_;
}


//class methods
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

                int counter = 1;
                for(const auto& map_filepath : *file_paths_) {
                    cout << "File " << counter << ": " << map_filepath.filename().string() << endl;
                    ++counter;
                }

                //Load the map file
                loaded_map_ = SelectFile();

                return loaded_map_ != nullptr;
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

bool GameEngine::LoadSelectedMap() {
    if(loaded_map_) {
        while(!loaded_map_->ParseMap() && !exit_game_) {
            cout << "Failed to parse map, please select another one!\n";
            loaded_map_ = SelectFile();

            if(!loaded_map_) {
                return false;
            }
        }
        cout << "Success! Loaded map " << *loaded_map_->GetParsedMap()->GetMapName() << endl;
        return true;
    } else {
        return false;
    }
}

bool GameEngine::PlayerHasWon(Player *current_player) {

    Map* game_map_ = current_player->GetGameMap();
    vector<Country*>* all_countries;

    if(game_map_) {
        all_countries = game_map_->GetCountries();
    }

    for(Country* country : *all_countries){
        int id = country->GetCountryID();
        if(!current_player->DoesPlayerOwnCountry(id)) {
            return false;
        }
    }
    cout << "Game Over" << endl;
    cout << "Winner: " << *current_player->GetPlayerName();

    return true;
}


void GameEngine::SelectNumOfHumanPlayers() {
    int num_players = -1;

    cout << "Please enter the number of human players joining the game (between 2 and 6 players per game): ";
    while(!(cin >> num_players) || num_players < 2 || num_players > 6) {
        cout << "Invalid number of players entered. Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    num_of_human_players_ = num_players;
    num_of_players_ += num_of_human_players_;
}

void GameEngine::SelectNumOfAggressivePlayers() {

    if(num_of_players_ == 6) {
        return;
    }

    int num_players = 0;
    int num_players_remaining = 6 - num_of_players_;

    cout << "Please enter the number of aggressive computer players joining the game. You have " << num_players_remaining << " left to assign" ;
    while(!(cin >> num_players) || num_players < 1 || num_players > num_players_remaining) {
        cout << "Invalid number of players entered. Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    num_aggressive_players_ = num_players_remaining;
    num_of_players_ += num_players_remaining;
}

void GameEngine::SelectNumOfBenevolantPlayers() {
    if(num_of_players_ == 6) {
        return;
    }

    int num_players = 0;
    int num_players_remaining = 6 - num_of_players_;

    cout << "Please enter the number of benevolant computer players joining the game. You have " << num_players_remaining << " left to assign" ;
    while(!(cin >> num_players) || num_players < 1 || num_players > num_players_remaining) {
        cout << "Invalid number of players entered. Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    num_benevolant_players_ = num_players_remaining;
    num_of_players_ += num_players_remaining;
}


void GameEngine::CreatePlayers() {

    if(!loaded_map_) {
        cout << "Error! Cannot create players for game until valid Map has been selected and loaded\n";
        return;
    }

    if(num_of_players_ < 2 || num_of_players_ > 6) {
        //something went wrong. Set number of players to default value of 2
        num_of_players_ = 2;
    }

    int player_counter = 1;

    cout << "Creating " << num_of_players_ << " players for new game...\n";
    for(size_t i = 0; i < num_of_human_players_; ++i) {
        string player_name = "Human Player " + std::to_string(player_counter++);

        ConcreteStrategies* strategy = new HumanPlayerStrategy();
        Player* player = new Player(player_name, loaded_map_->GetParsedMap(), this);
        player->SetPlayerStrategy(strategy);
        player->SetAsHuman();
        players_->push_back(player);
    }

    for(size_t i = 0; i < num_aggressive_players_; ++i) {
        string player_name = "Aggressive Player " + std::to_string(player_counter++);

        ConcreteStrategies* strategy = new AggressiveComputerPlayerStrategy();
        Player* player = new Player(player_name, loaded_map_->GetParsedMap(), this);
        player->SetPlayerStrategy(strategy);
        players_->push_back(player);
    }

    for(size_t i = 0; i < num_benevolant_players_; ++i) {
        string player_name = "Benevolant Player " + std::to_string(player_counter++);

        ConcreteStrategies* strategy = new BenevolantComputerPlayerStrategy();
        Player* player = new Player(player_name, loaded_map_->GetParsedMap(), this);
        player->SetPlayerStrategy(strategy);
        players_->push_back(player);
    }

    game_start_->SetNumberOfArmies(num_of_players_);
}

void GameEngine::AssignDiceToPlayers() {
    if(!loaded_map_) {
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
    if(!loaded_map_) {
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
    if(!loaded_map_) {
        cout << "Error! Cannot create players for game until valid Map has been selected and loaded\n";
        return;
    }

    cout << "Creating deck of cards for new game...\n";
    cards_deck_ = new Deck();
    int num_cards = loaded_map_->GetParsedMap()->GetNumCountries();
    cards_deck_ ->CreateDeck(num_cards);
}

void GameEngine::DisplayCurrentGame() {
    cout << "There are " << num_of_players_ << " players participating in this game. Here are their stats:\n";
    for(const Player* player : *players_) {
        player->DisplayPlayerStats();
        cout << endl;
    }

    cout << "There are " << loaded_map_->GetParsedMap()->GetNumCountries() << " countries in the loaded map and " << cards_deck_->GetNumberOfCardsInDeck() << " cards in the created deck\n\n";

    cout << "Verifying that each country only has one single owner\n";
    cout << setw(20) << left <<  "Country" << setw(30) << right << "Owner"<< endl;

    for(const Country* country : *loaded_map_->GetParsedMap()->GetCountries()) {
        string country_name = *country->GetCountryName();
        string owner_name = (country->GetCountryOwner()) ? *country->GetCountryOwner()->GetPlayerName() : "";

        if(!owner_name.empty() && !country_name.empty()) {
            cout << setw(20) << left <<country_name << setw(30) << right << owner_name << endl;
        }
    }

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

void GameEngine::StartGameLoop() {
    if(!players_ || players_->empty() || num_of_players_ == 0){
        cout << "Something went wrong! aborting game loop" << endl;
    }

    for(Player* player : *players_) {
        cout << *player->GetPlayerName() << endl;
        player->DisplayCountries();
    }
    cout << "############################################################################# GAME START #############################################################################" << endl;


    int num_iterations = 0;
    int current_index = game_start_->current_player_index_;

    Player* current_player = players_->at(current_index);

    if(!current_player) {
        return;
    }

    while(!PlayerHasWon(current_player) && num_iterations < 1000){
        current_player = players_->at(current_index);
        if(!current_player) {
            break;
        }
        cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Currently " << *current_player->GetPlayerName() << "'s turn * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";

        if(!current_player->GetPlayersCountries()->empty()){

            Notify();
            current_player->Reinforce();
            Notify();
            current_player->Attack();
            Notify();
            current_player->Fortify();
            Notify();
            ++num_iterations;
        }

        current_index = (current_index + 1) % num_of_players_;
        current_player = players_->at(game_start_->current_player_index_);
    }

    cout << "############################################################################# GAME OVER #############################################################################" << endl;
}

void GameEngine::Register(Observer *observer) {
    observers_->push_back(observer);
}

void GameEngine::Unregister(Observer *observer) {
    // find the observer
    auto iterator = std::find(observers_->begin(), observers_->end(), observer);

    if (iterator != observers_->end()) {
        observers_->erase(iterator); // unregister the observer
    }
}

void GameEngine::Notify(Player* current_player, int current_phase, string current_phase_action_description, bool phase_start, bool phase_over) {
    for (Observer *observer : *observers_) {
        observer->Update(current_player, current_phase, current_phase_action_description, phase_start, phase_over);
    }
}
//GameStatisticObserver
void GameEngine::Notify(){
        for(Observer* observer : *observers_){
            observer->Update();
        }
    }
