/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include "PlayerStrategies.h"

ConcreteStrategies::ConcreteStrategies(const ConcreteStrategies &strategy) {
    player_ = strategy.player_;
}

ConcreteStrategies& ConcreteStrategies::operator=(const ConcreteStrategies &concrete_strategies) {
    player_ = concrete_strategies.player_;
    return *this;
}

HumanPlayerStrategy::~HumanPlayerStrategy() {
    player_ = nullptr;
    delete player_;
}

void HumanPlayerStrategy::ReinforceStrategy(map<int, int>& country_indices, int& num_bonus_army) {

    int country_index = 0;
    int reinforce_value = 0;

    while(num_bonus_army > 0) {

        Country* current_country = player_->GetPlayersCountries()->at(country_index);

        if(!current_country) {
            ++country_index;
            continue;
        }

        cout << "Currently on Country " << endl;
        current_country->DisplayInfo();

        cout << "Armies to assign: " << num_bonus_army << "\nArmies to add to current country: ";

        cin >> reinforce_value;
        while (cin.fail() || reinforce_value > num_bonus_army || reinforce_value < 0) {
            cout << "Invalid input. Pick a valid number: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> reinforce_value;
        }

        int country_id = current_country->GetCountryID();

        if(!country_indices[country_id]) {
            country_indices.insert({country_id, reinforce_value});
        }

        cout << reinforce_value << " armies added to current country" << endl;

        num_bonus_army -= reinforce_value;
        ++country_index;
        country_index = country_index % (int)player_->GetPlayersCountries()->size();
    }
}


void HumanPlayerStrategy::AttackStrategy() {
    //ask for input
}

void HumanPlayerStrategy::FortifyStrategy() {

}



AggressiveComputerPlayerStrategy::~AggressiveComputerPlayerStrategy() {

}

void AggressiveComputerPlayerStrategy::ReinforceStrategy(map<int, int>& country_indices, int& num_bonus_army) {

    int max_num_armies = 0;
    int country_id_with_most_armies = 1;

    for(Country* country : *player_->GetPlayersCountries()) {
        int num_armies = country->GetNumberOfArmies();

        if(num_armies > max_num_armies) {
            max_num_armies = num_armies;
            country_id_with_most_armies = country->GetCountryID();
        }
    }

    country_indices.insert({country_id_with_most_armies, max_num_armies});
}

void AggressiveComputerPlayerStrategy::AttackStrategy() {

}

void AggressiveComputerPlayerStrategy::FortifyStrategy() {

}



BenevolantComputerPlayerStrategy::~BenevolantComputerPlayerStrategy() {

}

void BenevolantComputerPlayerStrategy::ReinforceStrategy(map<int, int>& country_indices, int& num_bonus_army) {

    //use a sorted map to arrange the countries from weakest to strongest
    multimap<int, int> country_num_army_pairs;

    //populate the map in order of weakest to strongest
    for(Country* country : *player_->GetPlayersCountries()) {
        int num_armies = country->GetNumberOfArmies();
        country_num_army_pairs.insert({num_armies, country->GetCountryID()});
    }

    //give 1 army to each of the weakest countries (number of weakest countries == num_bonus_army)
    int counter = 0;
    for(auto& entry : country_num_army_pairs) {
        if(counter == num_bonus_army) {
            break;
        }
        country_indices.insert({entry.second, entry.first});
        ++counter;
    }
}

void BenevolantComputerPlayerStrategy::AttackStrategy() {

}

void BenevolantComputerPlayerStrategy::FortifyStrategy() {

}