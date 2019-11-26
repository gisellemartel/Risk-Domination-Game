/**
 * Assignment #4 COMP345, FALL 2019
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

    Notify("Starting New Game...\n");
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
    num_of_human_players_ = 0;
    num_aggressive_players_ = 0;
    num_benevolant_players_ = 0;
    num_random_players_ = 0;
    num_cheater_players_ = 0;
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
    num_of_human_players_ = game_engine.num_of_human_players_;
    num_aggressive_players_ = game_engine.num_aggressive_players_;
    num_benevolant_players_ = game_engine.num_benevolant_players_;
    num_random_players_ = game_engine.num_random_players_;
    num_cheater_players_ = game_engine.num_cheater_players_;
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
    num_of_human_players_ = game_engine.num_of_human_players_;
    num_aggressive_players_ = game_engine.num_aggressive_players_;
    num_benevolant_players_ = game_engine.num_benevolant_players_;
    num_random_players_ = game_engine.num_random_players_;
    num_cheater_players_ = game_engine.num_cheater_players_;
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

    while(!PlayerHasWon(current_player)){
        current_player = players_->at(current_index);
        if(!current_player) {
            break;
        }
        cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Currently " << *current_player->GetPlayerName() << "'s turn * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";

        if(!current_player->GetPlayersCountries()->empty()){

            current_player->Reinforce();
            current_player->Attack();
            current_player->Fortify();
            ++num_iterations;
        }

        current_index = (current_index + 1) % num_of_players_;
        current_player = players_->at(game_start_->current_player_index_);
    }

    string game_over = "############################################################################# GAME OVER #############################################################################\n";

    game_over.append("\n\n* * * * * * * * * * * * * * * Here are the final results of the game * * * * * * * * * * * * * * * \n\n");

    if(current_player) {
        game_over.append(*current_player->GetPlayerName() + " has won!!\n\n");
    }

    Notify(game_over);

    for(Player* player : *players_) {
        cout << *player->GetPlayerName() << "'s countries: ";
        player->DisplayCountries();
    }


}

void GameEngine::PromptUserToSelectNumPlayers(PlayerType player_type) {
    int num_players_remaining_to_assign = num_of_players_ - (num_of_human_players_ + num_aggressive_players_ + num_benevolant_players_ + num_random_players_ + num_cheater_players_);
    if(num_players_remaining_to_assign < 1 || num_players_remaining_to_assign > num_of_players_) {
        return;
    }

    string player_type_str;
    switch(player_type) {
        case PlayerType::Human :
            player_type_str = "Human";
            break;
        case PlayerType::Aggressive :
            player_type_str = "Aggressive";
            break;
        case PlayerType::Benevolant :
            player_type_str = "Benevolant";
            break;
        case PlayerType::Random :
            player_type_str = "Random";
            break;
        case PlayerType::Cheater :
            player_type_str = "Cheater";
            break;
        default:
            player_type_str = "";
            break;
    }

    int num_players = 0;

    if(num_players_remaining_to_assign > 0) {
        cout << "How many " << player_type_str << " opponents would you like to battle? (choose between 0 - "
             << num_players_remaining_to_assign << " ): ";
        while (!(cin >> num_players) || num_players < 0 || num_players > num_players_remaining_to_assign) {
            cout << "Invalid selection! Please try again:";
            cin.clear();
            cin.ignore(132, '\n');
        }
    }

    switch(player_type) {
        case PlayerType::Human :
            num_of_human_players_ += num_players;
            break;
        case PlayerType::Aggressive :
            num_aggressive_players_ += num_players;
            break;
        case PlayerType::Benevolant :
            num_benevolant_players_ += num_players;
            break;
        case PlayerType::Random :
            num_random_players_ += num_players;
            break;
        case PlayerType::Cheater :
            num_cheater_players_ += num_players;
            break;
        default:
            break;
    }
}

void GameEngine::CreateNewGame() {
    bool is_tournament;
    cout << "Please enter 0 to play single game, or 1 to play tournament" << endl;

    while(!(cin >> is_tournament)) {
        cout << "Invalid entry! Please try again" << endl;
    }

    if(is_tournament) {
        cout << "You have chosen to do a tournament!" << endl;

        //TODO: implementation of the tournament

    } else {
        game_start_ = new StartupPhase;

        SelectMap();
        LoadSelectedMap();
        if(loaded_map_->ParseMap()) {

            cout << "Please enter the number of human players joining the game (between 2 and 6 players per game): ";
            while(!(cin >> num_of_players_) || num_of_players_ < 2 || num_of_players_ > 6) {
                cout << "Invalid number of players entered. Please try again: ";
                cin.clear();
                cin.ignore(132, '\n');
            }

            while(num_of_human_players_ + num_aggressive_players_ + num_benevolant_players_ + num_random_players_ + num_cheater_players_ < num_of_players_) {
                PromptUserToSelectNumPlayers(PlayerType::Human);
                PromptUserToSelectNumPlayers(PlayerType::Aggressive);
                PromptUserToSelectNumPlayers(PlayerType::Benevolant);
                PromptUserToSelectNumPlayers(PlayerType::Random);
                PromptUserToSelectNumPlayers(PlayerType::Cheater);
            }

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
        Notify("Starting New Game...\n");
        Observer* observer = new PhaseObserver;
        Register(observer);

        //repeat game loop 2 times
        for(int i = 0; i < 2; ++i) {
            for(Player* player : *players_) {
                player->Reinforce();
                player->Attack();
                player->Fortify();
            }
        }

        Unregister(observer);
    }


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
void GameEngine::Notify(string msg){
    for(Observer* observer : *observers_){
        observer->Update(msg);
    }
}

void GameEngine::RemovePlayer(Player *player) {
    int idx_to_remove = -1;
    for(int i = 0; i < players_->size(); ++i) {
        if((*players_)[i] == player) {
            idx_to_remove = i;
            break;
        }
    }

    //remove the deleted player from the game
    if(idx_to_remove > -1) {
        players_->erase(players_->begin() + idx_to_remove);
    }
}


