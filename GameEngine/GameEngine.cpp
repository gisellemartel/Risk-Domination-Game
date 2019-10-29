/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <iostream>
#include <string>
#include <filesystem>
#include <type_traits>

using namespace std;

#include "GameEngine.h"

GameEngine::GameEngine() {
    game_map_ = nullptr;
    cards_deck_ = nullptr;
    players_ = nullptr;
    //2 players by default
    num_of_players_ = 2;
}

GameEngine::GameEngine(const GameEngine& game_engine) {
    game_map_ = game_engine.game_map_;

    cards_deck_ = game_engine.cards_deck_;
    for (size_t i = 0; i < game_engine.cards_deck_->size(); ++i) {
        cards_deck_[i] = game_engine.cards_deck_[i];
    }

    players_ = game_engine.players_;
    for (size_t i = 0; i < game_engine.players_->size(); ++i) {
        players_[i] = game_engine.players_[i];
    }

    num_of_players_ = game_engine.num_of_players_;
}

GameEngine::~GameEngine() {

    for (auto& card : *cards_deck_) {
        card = nullptr;
        delete card;
    }

    for (auto& player : *players_) {
        player = nullptr;
        delete player;
    }

    game_map_ = nullptr;
    cards_deck_ = nullptr;
    players_ = nullptr;

    delete players_;
    delete cards_deck_;
    delete game_map_;
}

GameEngine& GameEngine::operator=(const GameEngine& game_engine) {
    game_map_ = game_engine.game_map_;

    cards_deck_ = game_engine.cards_deck_;
    for (size_t i = 0; i < game_engine.cards_deck_->size(); ++i) {
        cards_deck_[i] = game_engine.cards_deck_[i];
    }

    players_ = game_engine.players_;
    for (size_t i = 0; i < game_engine.players_->size(); ++i) {
        players_[i] = game_engine.players_[i];
    }

    num_of_players_ = game_engine.num_of_players_;

    return *this;
}

inline MapLoader* GameEngine::GetGameMap() const {
    return game_map_;
}

inline vector<Cards*>* GameEngine::GetCardsDeck() const {
    return cards_deck_;
}

inline vector<Player*>* GameEngine::GetPlayers() const {
    return players_;
}

inline int GameEngine::GetNumPlayers() const {
    return num_of_players_;
}

bool GameEngine::SelectMap() {

    string user_response;

    do {
        string path;

        cout << "Please enter the name of the directory you would like to load a map file from: ";
        cin >> path;
        filesystem::directory_iterator iterator;
        vector<filesystem::path> map_filepaths;

        try {
            iterator = filesystem::directory_iterator(path);

            for (const auto& entry : iterator) {
                if (entry.path().extension() == ".map") {
                    map_filepaths.push_back(entry.path());
                }
            }

            if(map_filepaths.empty()) {
                cout << "No files of .map type found in directory! Would you like to retry? Enter 'y' to continue: ";
                cin >> user_response;
            } else {
                cout << "\n\nHere are the entries found in directory " << path << "\"\n\n";

                int user_selection = -1;
                int counter = 1;
                for(const auto& map_filepath : map_filepaths) {
                    cout << "File " << counter << ": " << map_filepath.filename().string() << endl;
                    ++counter;
                }

                cout << "\nTo select a file, enter its corresponding number here: ";

                while(!(cin >> user_selection) || user_selection < 1 || user_selection > map_filepaths.size()) {
                    cin.clear();
                    cin.ignore(132, '\n');
                    cout << "Error! Please enter a valid file number: ";
                }

                string file_to_load = map_filepaths[user_selection - 1].string();

                cout << "Now loading map file: " << file_to_load << "..." << endl;
                //Load the map file
                game_map_ = new MapLoader(file_to_load);

                if(game_map_) {
                    return true;
                } else {
                    return false;
                }
            }
        }
        catch (filesystem::filesystem_error& error) {
            cout << "invalid directory. Would you like to try again? enter 'y': ";
            cin >> user_response;
        }
        cout << endl << endl;
    } while (user_response == "y");

    return false;
}

bool GameEngine::LoadSelectedMap() {
    if(game_map_) {
        return game_map_->ParseMap();
    } else {
        return false;
    }
}

void GameEngine::SelectNumOfPlayers() {
    int num_players = -1;

    cout << "Please enter the number of players joining the game (between 2 and 6 players per game)";
    while(!(cin >> num_players) || num_players < 2 || num_players > 6) {
        cout << "Invalid number of players entered. Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    num_of_players_ = num_players;
}

void GameEngine::CreatePlayers() {

    if(!game_map_) {
        cout << "Error! Cannot create players for game until valid Map has been selected and loaded\n\n";
        return;
    }

    if(num_of_players_ < 2 || num_of_players_ > 6) {
        //something went wrong. Set number of players to default value of 2
        num_of_players_ = 2;
    }

    vector<Player*> players;

    for(size_t i = 0; i < num_of_players_; ++i) {
        string player_name = "Player " + std::to_string(i + 1);
        Player player = Player(player_name);

        players.push_back(new Player(player_name));
    }

    players_ = &players;
}

void GameEngine::AssignDiceToPlayers() {
    if(!game_map_) {
        cout << "Error! Cannot create players for game until valid Map has been selected and loaded\n\n";
        return;
    }

    if(players_->empty()) {

        cout << "No Player created to assign dice to! Please try again\n\n";
        return;
    }

    for(Player* player: *players_) {
        player->SetPlayerDice(new Dice());
    }

}

void GameEngine::AssignHandOfCardsToPlayers() {
    if(!game_map_) {
        cout << "Error! Cannot create players for game until valid Map has been selected and loaded\n\n";
        return;
    }

    if(players_->empty()) {

        cout << "No Player created to assign hand of cards to! Please try again\n\n";
        return;
    }

    for(Player* player: *players_) {
       // player->AddCardToCollection(new Cards());
    }
}

void GameEngine::CreateCardsDeck() {
    if(!game_map_) {
        cout << "Error! Cannot create players for game until valid Map has been selected and loaded\n\n";
        return;
    }

}