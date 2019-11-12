/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include "PlayerStrategies.h"


void HumanPlayerStrategy::ReinforceStrategy(const vector<Country*>& countries, map<int, int>& country_num_army_to_add_pairs, int& num_bonus_army) {

    int country_index = 0;
    int reinforce_value = 0;

    while(num_bonus_army > 0) {

        Country* current_country = countries.at(country_index);

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

        if(!country_num_army_to_add_pairs[country_id]) {
            country_num_army_to_add_pairs.insert({country_id, reinforce_value});
        }

        cout << reinforce_value << " armies added to current country" << endl;

        num_bonus_army -= reinforce_value;
        ++country_index;
        country_index = country_index % (int)countries.size();
    }
}

void HumanPlayerStrategy::AttackStrategy() {
    //ask for input
}

void HumanPlayerStrategy::FortifyStrategy() {

}



void AggressiveComputerPlayerStrategy::ReinforceStrategy(const vector<Country*>& countries, map<int, int>& country_num_army_to_add_pairs, int& num_bonus_army) {

    int max_num_armies = 0;
    int country_id_with_most_armies = 1;

    for(Country* country : countries) {
        int num_armies = country->GetNumberOfArmies();

        if(num_armies > max_num_armies) {
            max_num_armies = num_armies;
            country_id_with_most_armies = country->GetCountryID();
        }
    }

    country_num_army_to_add_pairs.insert({country_id_with_most_armies, max_num_armies});
}

void AggressiveComputerPlayerStrategy::AttackStrategy() {

}

void AggressiveComputerPlayerStrategy::FortifyStrategy() {

}



void BenevolantComputerPlayerStrategy::ReinforceStrategy(const vector<Country*>& countries, map<int, int>& country_num_army_to_add_pairs, int& num_bonus_army) {

    //use a sorted map to arrange the countries from weakest to strongest
    multimap<int, int> country_num_army_pairs;

    //populate the map in order of weakest to strongest
    for(Country* country : countries) {
        int num_armies = country->GetNumberOfArmies();
        country_num_army_pairs.insert({num_armies, country->GetCountryID()});
    }

    //give 1 army to each of the weakest countries (number of weakest countries == num_bonus_army)
    int counter = 0;
    for(auto& entry : country_num_army_pairs) {
        if(counter == num_bonus_army) {
            break;
        }
        country_num_army_to_add_pairs.insert({entry.second, entry.first});
        ++counter;
    }
}

void BenevolantComputerPlayerStrategy::AttackStrategy() {

}

void BenevolantComputerPlayerStrategy::FortifyStrategy() {

}