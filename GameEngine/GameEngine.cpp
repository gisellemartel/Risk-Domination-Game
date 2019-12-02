

#include "GameEngine.h"

// GAME ENGINE CLASS --------------------------------------------------------------------------------------------------

//Function purely for testing purposes
void GameEngine::TestAutoLoadMapAndCreateGame(string file_path, int num_human_players, int num_aggressive_players, int num_benevolant_players, int num_random_players, int num_cheater_players) {
    exit_game_ = false;
    loaded_map_ = new MapLoader(file_path);
    if(loaded_map_->ParseMap()) {
        num_of_players_ = num_human_players + num_aggressive_players + num_benevolant_players + num_random_players + num_cheater_players;
        num_of_human_players_ = num_human_players;
        num_aggressive_players_ = num_aggressive_players;
        num_benevolant_players_ = num_benevolant_players;
        num_random_players_ = num_random_players;
        num_cheater_players_ = num_cheater_players;
        CreatePlayersForMap(loaded_map_);
        CreateCardsDeck(loaded_map_);
        AssignHandOfCardsToPlayers();
        AssignDiceToPlayers();
        game_start_->RandomlyDeterminePlayerOrder(players_);
        game_start_->AssignCountriesToAllPlayers(players_, loaded_map_->GetParsedMap()->GetCountries());
        game_start_->AutoAssignArmiesToAllPlayers(players_);
    }

    for(Player* player : *players_) {
        player->SetGameMap(loaded_map_->GetParsedMap());
    }

    Notify("Starting New Game...\n", *players_);
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

string GameEngine::SelectFileForTournament() {
    cout << "\nTo select a file, enter its corresponding number here:";
    int user_selection = Utility::PromptUserNumericalInput(1, file_paths_->size());

    string file_to_load = (*file_paths_)[user_selection - 1].string();
    cout << "Selected map file: " << file_to_load << "..." << endl;

    return file_to_load;
}

void GameEngine::PromptUserToSelectStrategiesForTournament() {

    vector<int> chosen_strategies;
    cout << "\nHere all the available strategies:\n";
    cout << "Aggressive: 1\n";
    cout << "Benevolant: 2\n";
    cout << "Random: 3\n";
    cout << "Cheater: 4\n";
    for(int i = 0; i < num_strategies_; ++i) {
        cout << "\nPlease specify the desired strategy for player " << (i+1) << ".\n";
        int result = Utility::PromptUserNumericalInput(1, 4);

        while(Utility::HasValue(chosen_strategies, result)) {
            cout << "You have already chosen this strategy! Please try again";
            result = Utility::PromptUserNumericalInput(1, 4);
        }

        switch(result) {
            case 1:
                num_aggressive_players_ = 1;
                cout << "You have chosen Aggressive strategy\n";
                chosen_strategies.push_back(1);
                break;
            case 2:
                num_benevolant_players_ = 1;
                chosen_strategies.push_back(2);
                cout << "You have chosen Benevolant strategy\n";
                break;
            case 3:
                num_random_players_ = 1;
                chosen_strategies.push_back(3);
                cout << "You have chosen Random strategy\n";
                break;
            case 4:
                num_cheater_players_ = 1;
                chosen_strategies.push_back(4);
                cout << "You have chosen Cheater strategy\n";
                break;
            default:
                break;
        }


    }
}

void GameEngine::SetUpSingleGame() {
    game_start_ = new StartupPhase;

    string map_file_name = AutoSelectMap("../MapLoader/domination-map-files");
    loaded_map_ = new MapLoader(map_file_name);

    if(!loaded_map_) {
        cout << "Failed to load selected map! Aborting\n";
        return;
    }

    if(loaded_map_->ParseMap()) {

        cout << "Please enter the number of human players joining the game (between 2 and 6 players per game): ";
        num_of_players_ = Utility::PromptUserNumericalInput(2, 6);

        while(num_of_human_players_ + num_aggressive_players_ + num_benevolant_players_ + num_random_players_ + num_cheater_players_ < num_of_players_) {
            PromptUserToSelectNumPlayers(PlayerType::Human);
            PromptUserToSelectNumPlayers(PlayerType::Aggressive);
            PromptUserToSelectNumPlayers(PlayerType::Benevolant);
            PromptUserToSelectNumPlayers(PlayerType::Random);
            PromptUserToSelectNumPlayers(PlayerType::Cheater);
        }

        CreatePlayersForMap(loaded_map_);
        CreateCardsDeck(loaded_map_);
        AssignHandOfCardsToPlayers();
        AssignDiceToPlayers();
        game_start_->RandomlyDeterminePlayerOrder(players_);
        game_start_->AssignCountriesToAllPlayers(players_, loaded_map_->GetParsedMap()->GetCountries());
        game_start_->AutoAssignArmiesToAllPlayers(players_);

        for(Player* player : *players_) {
            player->SetGameMap(loaded_map_->GetParsedMap());
        }

        StartGameLoop();
    }
}

void GameEngine::SetUpTournament() {

    // Ask the user to specify and load the maps they wish to use
    cout << "\nHow many maps would you like to include in the tournament? You may choose between 1-5: ";
    num_unqiue_maps_ = Utility::PromptUserNumericalInput(1, 5);
    cout << "\nYou have chosen " << num_unqiue_maps_ << " maps for the tournament" << endl;

    //prompt the user to select the map files to be loaded
    for(int i = 0; i < num_unqiue_maps_; ++i) {
        string map_file_name = AutoSelectMap("../MapLoader/domination-map-files");
        if(!map_file_name.empty()) {
            tournament_maps_->push_back(new string(map_file_name));
        }
    }

    //prompt the user to specify the number of games to be played for each map
    cout << "\nPlease enter the number of games you like to player per Map (between 1-5): ";
    num_games_tournament_ = Utility::PromptUserNumericalInput(1, 5);


    //prompt the user to specify the max number of turns for each game
    cout << "\nPlease enter the maximum number of turns allowed per game (between 10-50): ";
    max_num_turns_per_game_ = Utility::PromptUserNumericalInput(10, 50);


    // prompt the user for the number of different strategies they would like to include
    cout << "\nPlease enter the number of different computer strategies you would like to include in the game (between 2-4): " << endl;
    num_strategies_ = Utility::PromptUserNumericalInput(2, 4);

    //Create the games
    num_of_human_players_ = 0;
    num_of_players_ = num_strategies_;

    //prompt the user to select the number of players for each strategy type
    while((num_aggressive_players_ + num_benevolant_players_ + num_random_players_ + num_cheater_players_) < num_of_players_) {
        PromptUserToSelectStrategiesForTournament();
    }

    //start playing the tournament!
    StartTournament();
}

void GameEngine::StartTournament() {
    // iterate through all the chosen game maps and execute the game M number of times
    for (string* map_file_name : *tournament_maps_) {
        MapLoader *current_map = new MapLoader(*map_file_name);

        if(current_map->ParseMap()) {
            string map_name = *current_map->GetParsedMap()->GetMapName();
            loaded_map_ = current_map;

            vector<GameResult> game_results;
            //current map will be played for num_games
            for (int i = 0; i < num_games_tournament_; ++i) {
                if(!current_map) {
                    current_map = new MapLoader(*map_file_name);
                    current_map->ParseMap();
                    loaded_map_ = current_map;
                    game_start_ = new StartupPhase;
                }
                CreatePlayersForMap(current_map);
                CreateCardsDeck(current_map);
                AssignHandOfCardsToPlayers();
                AssignDiceToPlayers();
                game_start_->RandomlyDeterminePlayerOrder(players_);
                game_start_->AssignCountriesToAllPlayers(players_, current_map->GetParsedMap()->GetCountries());
                game_start_->AutoAssignArmiesToAllPlayers(players_);


                int current_turn = 0;
                int current_index = game_start_->current_player_index_;

                Player *current_player = players_->at(current_index);


                if (!current_player) {
                    return;
                }

                //flag that will track when game is a draw.
                bool is_draw = false;

                //start the game loop for current game
                while (!PlayerHasWon(current_player) && num_of_players_ > 1) {
                    Notify("\nCurrent Map: " + *current_map->GetParsedMap()->GetMapName()  + "\nCurrent game: " + to_string(i + 1) + "\nCurrent turn: " + to_string(current_turn + 1) + "\n", *players_);
                    current_player = players_->at(current_index);
                    if (!current_player) {
                        break;
                    }
                    cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Currently "
                         << *current_player->GetPlayerName()
                         << "'s turn * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";

                    if(!current_player->GetPlayersCountries()->empty()){

                        current_player->Reinforce();
                        current_player->Attack();
                        if(num_of_players_ < 2) {
                            break;
                        }
                        current_player->Fortify();
                    }

                    current_index = (current_index + 1) % players_->size();
                    current_player = players_->at(current_index);
                    //each time the game is played by all players, increment the counter
                    ++current_turn;
                    if(current_turn == max_num_turns_per_game_) {
                        is_draw = true;
                        break;
                    }
                }

                string game_over = "############################################################################# GAME OVER #############################################################################\n";

                game_over.append("\n\n* * * * * * * * * * * * * * * Here are the final results of the current game * * * * * * * * * * * * * * * \n\n");

                if(current_player && !is_draw) {
                    if(current_player->IsRandom()) {
                        game_results.push_back(GameResult::RandomWin);
                    } else if (current_player->IsCheater()) {
                        game_results.push_back(GameResult::CheaterWin);
                    } else if(current_player->IsAggressive()) {
                        game_results.push_back(GameResult::AggressiveWin);
                    }
                    game_over.append(*current_player->GetPlayerName() + " has won!!\n\n");
                } else {
                    game_over.append("The game was a draw!!\n\n");
                    game_results.push_back(GameResult::Draw);
                }

                Notify(game_over, *players_);

                for(Player* player : *players_) {
                    RemovePlayer(player);
                }

                delete loaded_map_;
                delete game_start_;
                game_start_ = nullptr;
                loaded_map_ = nullptr;
                current_map = nullptr;
            }

            //store the map and the results of each game
            tournament_results_.insert({map_name, game_results});
        } else {
            Notify("\nMap file " + Utility::StripString(*map_file_name, "/", "") + " failed to load! Skipping this map...\n", *players_);
        }
    }

    PrintFinalTournamentResult();
}

void GameEngine::PrintFinalTournamentResult() {
    //print the final result of the tournament
    string result = "\"############################################################################# TOURNAMENT OVER #############################################################################\n\n";
    result.append("\n\n* * * * * * * * * * * * * * * Here are the final results of the Tournament  * * * * * * * * * * * * * * * \n\n");

    //Maps
    result.append("M: ");
    if(tournament_results_.empty()) {
        result.append("none");
    } else {
        for(auto& entry : tournament_results_){
            string game_map = entry.first;

            result.append(game_map + ", ");

        }
        result.pop_back();
        result.pop_back();
    }

    //Strategies
    result.append("\nP: ");
    if(tournament_strategies_->empty()) {
        result.append("none");
    } else {
        for(PlayerType strategy : *tournament_strategies_) {
            switch(strategy) {
                case PlayerType::Aggressive :
                    result.append("Aggressive, ");
                    break;
                case PlayerType::Random :
                    result.append("Random, ");
                    break;
                case PlayerType::Cheater :
                    result.append("Cheater, ");
                    break;
                case PlayerType::Benevolant :
                    result.append("Benevolant, ");
                    break;
                default:
                    break;
            }
        }
        result.pop_back();
        result.pop_back();
    }

    //# games per map
    result.append("\nG: " + to_string(num_games_tournament_));

    //# num turns per game
    result.append("\nD: " + to_string(max_num_turns_per_game_) + "\n\n");


    for(auto& entry : tournament_results_) {
        string map_name = entry.first;

        map_name.append(":\n\n");

        vector<GameResult> game_results = entry.second;
        int game_ctr = 0;
        for(GameResult game_result : game_results) {
            map_name.append("Game " + to_string(++game_ctr) + ": ");
            switch(game_result) {
                case GameResult::AggressiveWin :
                    map_name.append("Aggressive\t\t");
                    break;
                case GameResult ::CheaterWin :
                    map_name.append("Cheater\t\t");
                    break;
                case GameResult::RandomWin :
                    map_name.append( "Random\t\t");
                    break;
                case GameResult::Draw :
                    map_name.append("Draw\t\t");
                    break;
                default:
                    break;
            }

            map_name.append("\n");
        }
        result.append(map_name +  "\n\n");
    }

    Utility::ClearScreen();
    cout << result;
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

    num_unqiue_maps_ = 0;
    num_games_tournament_ = 0;
    max_num_turns_per_game_ = 0;
    num_strategies_ = 2;
    tournament_strategies_ = new vector<PlayerType>;
    tournament_maps_ = new vector<string*>;
}

GameEngine::GameEngine(const GameEngine& game_engine) {

    *loaded_map_ = *game_engine.loaded_map_;
    *cards_deck_ = *game_engine.cards_deck_;

    *players_ = *game_engine.players_;
    for (size_t i = 0; i < game_engine.players_->size(); ++i) {
        (*players_)[i] = (*game_engine.players_)[i];
        (*game_engine.players_)[i] = nullptr;
    }

    *file_paths_ = *game_engine.file_paths_;
    for (size_t i = 0; i < game_engine.file_paths_->size(); ++i) {
        (*file_paths_)[i] = (*game_engine.file_paths_)[i];
        (*game_engine.file_paths_)[i] = nullptr;
    }

    *observers_ = *game_engine.observers_;
    for(int i = 0; i < game_engine.observers_->size(); ++i) {
        (*observers_)[i] = (*game_engine.observers_)[i];
        delete (*game_engine.observers_)[i];
        (*game_engine.observers_)[i] = nullptr;
    }

    *game_start_ = *game_engine.game_start_;

    tournament_results_.clear();
    for(auto& entry : game_engine.tournament_results_) {
        tournament_results_.insert({entry.first, entry.second});
    }

    tournament_strategies_ = new vector<PlayerType>;
    *tournament_strategies_ = *game_engine.tournament_strategies_;
    for(int i = 0; i < game_engine.tournament_strategies_->size(); ++i) {
        (*tournament_strategies_)[i] = (*game_engine.tournament_strategies_)[i];
    }

    tournament_maps_ = new vector<string*>;
    *tournament_maps_ = *game_engine.tournament_maps_;
    for(int i = 0; i < game_engine.tournament_maps_->size(); ++i) {
        (*tournament_maps_)[i] = (*game_engine.tournament_maps_)[i];
        delete (*game_engine.tournament_maps_)[i];
        (*game_engine.tournament_maps_)[i] = nullptr;
    }

    num_strategies_ = game_engine.num_strategies_;
    num_unqiue_maps_ = game_engine.max_num_turns_per_game_;
    max_num_turns_per_game_ = game_engine.max_num_turns_per_game_;
    num_games_tournament_ = game_engine.num_games_tournament_;


    delete game_engine.tournament_strategies_;
    delete game_engine.tournament_maps_;
    delete game_engine.loaded_map_;
    delete game_engine.cards_deck_;
    delete game_engine.game_start_;
    delete game_engine.players_;
    delete game_engine.file_paths_;
    delete game_engine.observers_;

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

    for (Observer* observer : *observers_) {
        delete observer;
        observer = nullptr;
    }

    for(string* tournament_map : *tournament_maps_) {
        delete tournament_map;
        tournament_map = nullptr;
    }

    delete tournament_maps_;
    delete tournament_strategies_;
    delete players_;
    delete file_paths_;
    delete cards_deck_;
    delete game_start_;
    delete observers_;
    delete loaded_map_;

    tournament_maps_ = nullptr;
    tournament_strategies_ = nullptr;
    loaded_map_ = nullptr;
    cards_deck_ = nullptr;
    players_ = nullptr;
    file_paths_ = nullptr;
    game_start_ = nullptr;
    observers_ = nullptr;
}

//operator overloader
GameEngine& GameEngine::operator=(const GameEngine& game_engine) {

    if(this != &game_engine) {
        *loaded_map_ = *game_engine.loaded_map_;
        *cards_deck_ = *game_engine.cards_deck_;

        *players_ = *game_engine.players_;
        for (size_t i = 0; i < game_engine.players_->size(); ++i) {
            (*players_)[i] = (*game_engine.players_)[i];
            (*game_engine.players_)[i] = nullptr;
        }

        *file_paths_ = *game_engine.file_paths_;
        for (size_t i = 0; i < game_engine.file_paths_->size(); ++i) {
            (*file_paths_)[i] = (*game_engine.file_paths_)[i];
            (*game_engine.file_paths_)[i] = nullptr;
        }

        *observers_ = *game_engine.observers_;
        for(int i = 0; i < game_engine.observers_->size(); ++i) {
            (*observers_)[i] = (*game_engine.observers_)[i];
            delete (*game_engine.observers_)[i];
            (*game_engine.observers_)[i] = nullptr;
        }

        *game_start_ = *game_engine.game_start_;

        tournament_results_.clear();
        for(auto& entry : game_engine.tournament_results_) {
            tournament_results_.insert({entry.first, entry.second});
        }

        tournament_strategies_ = new vector<PlayerType>;
        *tournament_strategies_ = *game_engine.tournament_strategies_;
        for(int i = 0; i < game_engine.tournament_strategies_->size(); ++i) {
            (*tournament_strategies_)[i] = (*game_engine.tournament_strategies_)[i];
        }

        tournament_maps_ = new vector<string*>;
        *tournament_maps_ = *game_engine.tournament_maps_;
        for(int i = 0; i < game_engine.tournament_maps_->size(); ++i) {
            (*tournament_maps_)[i] = (*game_engine.tournament_maps_)[i];
            delete (*game_engine.tournament_maps_)[i];
            (*game_engine.tournament_maps_)[i] = nullptr;
        }

        num_strategies_ = game_engine.num_strategies_;
        num_unqiue_maps_ = game_engine.max_num_turns_per_game_;
        max_num_turns_per_game_ = game_engine.max_num_turns_per_game_;
        num_games_tournament_ = game_engine.num_games_tournament_;


        delete game_engine.tournament_strategies_;
        delete game_engine.tournament_maps_;
        delete game_engine.loaded_map_;
        delete game_engine.cards_deck_;
        delete game_engine.game_start_;
        delete game_engine.players_;
        delete game_engine.file_paths_;
        delete game_engine.observers_;

        num_of_players_ = game_engine.num_of_players_;
        num_of_human_players_ = game_engine.num_of_human_players_;
        num_aggressive_players_ = game_engine.num_aggressive_players_;
        num_benevolant_players_ = game_engine.num_benevolant_players_;
        num_random_players_ = game_engine.num_random_players_;
        num_cheater_players_ = game_engine.num_cheater_players_;
        exit_game_ = game_engine.exit_game_;
        current_phase_ = game_engine.current_phase_;
    }

    return *this;
}

//getters
Player* GameEngine::GetPlayerByID(int id) const {
    for(Player* player : *players_) {
        if(id == player->GetPlayerID()) {
            return player;
        }
    }
    return nullptr;
}

MapLoader* GameEngine::GetLoadedMap() const {
    return loaded_map_;
}

Deck* GameEngine::GetCardsDeck() const {
    return cards_deck_;
}

vector<Player*>* GameEngine::GetPlayers() const {
    return players_;
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

string GameEngine::AutoSelectMap(const string& dir) {
    string path;
    string map_file_name;
    filesystem::directory_iterator iterator;

    try {
        if(file_paths_->empty()) {
            iterator = filesystem::directory_iterator(dir);
            for (const auto& entry : iterator) {
                if (entry.path().extension() == ".map") {
                    file_paths_->push_back(entry.path());
                }
            }
        }
    }
    catch (filesystem::filesystem_error& error) {
        cout << "Error. Invalid directory.\n";
    }


    if(file_paths_->empty()) {
        cout << "No files of .map type found in directory! Invalid directory.\n\n";
        return "";
    } else {
        cout << "\n\nHere are the entries found in directory \"" << dir << "\"\n\n";
        int counter = 1;
        for(const auto& map_filepath : *file_paths_) {
            cout << "File " << counter << ": " << map_filepath.filename().string() << endl;
            ++counter;
        }
        //Load the map file
        map_file_name = SelectFileForTournament();
        return map_file_name;
    }
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
   return current_player->GetPlayersCountries()->size() == current_player->GetGameMap()->GetNumCountries();
}

void GameEngine::CreatePlayersForMap(MapLoader *loaded_map) {
    if(!loaded_map) {
        cout << "Error! Cannot create players for game until valid Map has been selected and loaded\n";
        return;
    }

    players_ = new vector<Player*>;
    int current_id = 0;

    if(num_of_players_ < 2 || num_of_players_ > 6) {
        //something went wrong. Set number of players to default value of 2
        num_of_players_ = 2;
    }

    int player_counter = 1;

    cout << "Creating " << num_of_players_ << " players for new game...\n";
    for(size_t i = 0; i < num_of_human_players_; ++i) {
        string player_name = "Human Player " + std::to_string(player_counter++);

        ConcreteStrategies* strategy = new HumanPlayerStrategy();

        Player* player = (new Player(player_name, ++current_id, loaded_map->GetParsedMap(), this));
        player->SetPlayerStrategy(strategy);
        player->SetAsHuman();
        players_->push_back(player);
    }

    for(size_t i = 0; i < num_aggressive_players_; ++i) {
        string player_name = "Aggressive Player " + std::to_string(player_counter++);

        ConcreteStrategies* strategy = new AggressiveComputerPlayerStrategy();
        Player* player = (new Player(player_name, ++current_id, loaded_map->GetParsedMap(), this));
        player->SetPlayerStrategy(strategy);
        player->SetAsAggressive();
        players_->push_back(player);
    }

    for(size_t i = 0; i < num_benevolant_players_; ++i) {
        string player_name = "Benevolant Player " + std::to_string(player_counter++);

        ConcreteStrategies* strategy = new BenevolantComputerPlayerStrategy();
        Player* player = (new Player(player_name, ++current_id, loaded_map->GetParsedMap(), this));
        player->SetPlayerStrategy(strategy);
        player->SetAsBenevolent();
        players_->push_back((new Player(player_name, ++current_id, loaded_map->GetParsedMap(), this)));
    }

    for(size_t i = 0; i < num_random_players_; ++i) {
        string player_name = "Random Player " + std::to_string(player_counter++);

        ConcreteStrategies* strategy = new RandomComputerPlayerStrategy();
        Player* player = (new Player(player_name, ++current_id, loaded_map->GetParsedMap(), this));
        player->SetPlayerStrategy(strategy);
        player->SetAsRandom();
        players_->push_back(player);
    }

    for(size_t i = 0; i < num_cheater_players_; ++i) {
        string player_name = "Cheater Player " + std::to_string(player_counter++);

        ConcreteStrategies* strategy = new CheaterComputerPlayerStrategy();
        Player* player = (new Player(player_name, ++current_id, loaded_map->GetParsedMap(), this));
        player->SetPlayerStrategy(strategy);
        player->SetAsCheater();
        players_->push_back(player);
    }

    if(tournament_strategies_->empty()) {
        if(num_benevolant_players_ > 0) {
            tournament_strategies_->push_back(PlayerType::Benevolant);
        }

        if(num_cheater_players_ > 0) {
            tournament_strategies_->push_back(PlayerType::Cheater);
        }

        if(num_aggressive_players_ > 0) {
            tournament_strategies_->push_back(PlayerType::Aggressive);
        }

        if(num_random_players_ > 0) {
            tournament_strategies_->push_back(PlayerType::Random);
        }
    }

    num_of_players_ = num_benevolant_players_ + num_random_players_ + num_cheater_players_ + num_aggressive_players_;
    if(!game_start_) {
        game_start_ = new StartupPhase;
    }
    game_start_->SetNumberOfArmies(num_of_players_);
}

void GameEngine::AssignDiceToPlayers() {
    if(players_->empty()) {

        cout << "No Player created to assign dice to! Please try again\n";
        return;
    }

    cout << "Assigning dice rolling mechanism for each player...\n";

    for(Player* player : *players_) {
        player->SetPlayerDice(new Dice);
    }

}

void GameEngine::AssignHandOfCardsToPlayers() {

    if(players_->empty()) {
        cout << "No Player created to assign hand of cards to! Please try again\n";
        return;
    }

    cout << "Assigning empty hand of cards for each player...\n";

    for(Player* player: *players_) {
        player->SetPlayerHand(new Hand);
    }
}

void GameEngine::CreateCardsDeck(MapLoader* loaded_map) {
    if(!loaded_map) {
        cout << "Error! Cannot create players for game until valid Map has been selected and loaded\n";
        return;
    }

    cout << "Creating deck of cards for new game...\n";
    cards_deck_ = new Deck();
    int num_cards = loaded_map->GetParsedMap()->GetNumCountries();
    cards_deck_ ->CreateDeck(num_cards);
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

    while(!PlayerHasWon(current_player) && num_of_players_ > 1){
        current_player = players_->at(current_index);
        if(!current_player) {
            break;
        }
        cout << "\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Currently " << *current_player->GetPlayerName() << "'s turn * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";

        if(!current_player->GetPlayersCountries()->empty()){

            current_player->Reinforce();
            current_player->Attack();
            if(num_of_players_ < 2) {
                break;
            }
            current_player->Fortify();
        }

        current_index = (current_index + 1) % players_->size();
        current_player = players_->at(current_index);

        //each time the game is played by all players, increment the counter
        ++num_iterations;
    }

    string game_over = "############################################################################# GAME OVER #############################################################################\n";

    game_over.append("\n\n* * * * * * * * * * * * * * * Here are the final results of the game * * * * * * * * * * * * * * * \n\n");

    if(current_player) {
        game_over.append(*current_player->GetPlayerName() + " has won!!\n\n");
    }

    Notify(game_over, *players_);

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
             << num_players_remaining_to_assign << " ): " << endl;
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
    cout << "Please enter 0 to play single game, or 1 to play tournament" << endl;
    int is_tournament = Utility::PromptUserNumericalInput(0,1);

    if(is_tournament) {
        cout << "You have chosen tournament mode!" << endl;
        SetUpTournament();

    } else {
        cout << "You have chosen single game mode!" << endl;
        SetUpSingleGame();
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

//PhaseObserver
void GameEngine::Notify(Player* current_player, int current_phase, string current_phase_action_description, bool phase_start, bool phase_over) {
    for (Observer *observer : *observers_) {
        observer->Update(current_player, current_phase, current_phase_action_description, phase_start, phase_over);
    }
}

//GameStatisticObserver
void GameEngine::Notify(string msg, const vector<Player*>& players){
    for(Observer* observer : *observers_){
        observer->Update(msg, players);
    }
}

void GameEngine::RemovePlayer(Player *player) {
    int idx_to_remove = -1;
    for(int i = 0; i < players_->size(); ++i) {
        if(*(*players_)[i] == *player) {
            idx_to_remove = i;
            break;
        }
    }

    //remove the deleted player from the game
    if(idx_to_remove > -1 && idx_to_remove < players_->size() - 1) {
        if((*players_)[idx_to_remove]) {
            delete (*players_)[idx_to_remove];
            (*players_)[idx_to_remove] = nullptr;
        }
        players_->erase(players_->begin() + idx_to_remove);
    }
}
