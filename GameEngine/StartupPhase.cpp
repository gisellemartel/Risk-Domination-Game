//
// Created by Giselle Martel on 2019-11-26.
//

#include "StartupPhase.h"


// STARTUP PHASE CLASS ------------------------------------------------------------------------------------------------

// generic function which randomized order of passed vector.
// used to randomize both order of players, order in which countries are assigned
template<class V>
vector<int> StartupPhase::GenerateRandomizedIndicesForVector(const vector<V*>& vector_to_randomize) {
    int random = Utility::GenerateRandomNumInRange(0, vector_to_randomize.size()-1);
    vector<int> random_order;
    //randomize the order for the indices in the players vector
    while(!Utility::HasValue(random_order, random) || random_order.size() < vector_to_randomize.size()) {
        random = Utility::GenerateRandomNumInRange(0, vector_to_randomize.size()-1);
        if(!Utility::HasValue(random_order, random)) {
            random_order.push_back(random);
        }
    }
    return random_order;
}

// class constructors
StartupPhase::StartupPhase() {
    current_player_index_ = 0;
}

StartupPhase::StartupPhase(const StartupPhase& startup_phase) {
    player_order_ = startup_phase.player_order_;

    for(const auto& it : startup_phase.player_order_) {
        player_order_.insert(it);
    }
    current_player_index_ = startup_phase.current_player_index_;
}

StartupPhase::~StartupPhase() = default;

//operator overloader
StartupPhase& StartupPhase::operator=(const StartupPhase& startup_phase) {

    if(this != &startup_phase) {
        player_order_ = startup_phase.player_order_;

        for(const auto& it : startup_phase.player_order_) {
            player_order_.insert(it);
        }
        current_player_index_ = startup_phase.current_player_index_;
    }

    return *this;
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
        player_order_.insert(std::pair<Player*, int>((*players)[random_order[i]], i));
    }

    //print the players in the generated order
    for(auto it = player_order_.begin(); it != player_order_.end(); ++it) {
        Player*  player = it->first;

        for(int i = 0; i < players->size(); ++i ) {
            if(player && *player == *(*players)[i]) {
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

    vector<Country*>* countries = new vector<Country*>;

    for(Country* country : *countries_to_assign) {
        countries->push_back(country);
    }
    //generate vector of indices which will contain randomized order of countries
    vector<int> random_order = GenerateRandomizedIndicesForVector(*countries);
    //index used to track current position within countries vector after each loop iteration
    size_t current_index = 0;
    //assign countries to each player in round robin fashion
    while(num_countries > 0) {

        //debug string
        cout << "Current turn: " << (current_player_index_ + 1) << ".\n";

        for (auto &it : player_order_) {
            //find the player whose is currently to be assigned countries
            if (it.second == current_player_index_) {
                int current_random_index = random_order[current_index];

                //debug string
                cout << "Assigning " << *(*countries_to_assign)[current_random_index]->GetCountryName() << " to " << *(it.first->GetPlayerName()) << endl;

                it.first->AddCountryToCollection(countries_to_assign->at(current_random_index));
                //update position of current index
                current_index = (current_index + 1) % random_order.size();
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
        for (auto &it : player_order_) {
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
    num_armies.reserve(players->size());

    for(int i = 0; i < players->size(); ++i) {
        num_armies.push_back(number_of_armies_);
    }

    //assign countries to each player in round robin fashion
    while(!Utility::ContainsAllZeros(num_armies)) {
        for (auto &it : player_order_) {
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
                int country_id = Utility::GenerateRandomNumInRange(1, it.first->GetGameMap()->GetCountries()->size());
                while(!it.first->DoesPlayerOwnCountry(country_id)) {
                    country_id = Utility::GenerateRandomNumInRange(1, it.first->GetGameMap()->GetCountries()->size());
                }

                Country* current_country = it.first->GetCountryById(country_id);

                if(current_country) {
                    string name_country = *current_country->GetCountryName();
                    cout << "Auto selected " << name_country << " to assign armies to" << endl;

                    cout << "Auto selecting number of armign to assign to " << name_country  << " (you currently have " << num_armies[it.second] << " armies remaining to assign)..." << endl;

                    int num_armies_to_assign;
                    if(num_armies[it.second] == 0) {
                        num_armies_to_assign = 0;
                    } else {
                        num_armies_to_assign = Utility::GenerateRandomNumInRange(1, num_armies[it.second]) / num_armies[it.second] ;
                        while(num_armies_to_assign < 1 || num_armies_to_assign > num_armies[it.second]) {
                            num_armies_to_assign = Utility::GenerateRandomNumInRange(1, num_armies[it.second]) / num_armies[it.second] ;
                        }
                    }


                    //debug string
                    cout << "Assigning " << country_id << " armies to " << name_country << "...\n";

                    current_country->SetNumberOfArmies(num_armies_to_assign + current_country->GetNumberOfArmies());

                    //update number of armies for current player after assignment
                    num_armies[it.second] = num_armies[it.second] - num_armies_to_assign;
                }
            }
        }

        //get the current players turn
        current_player_index_ = (int)((current_player_index_ + 1) % players->size());
    }
    cout << endl;

}
