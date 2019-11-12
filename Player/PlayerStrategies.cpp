/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */
#include <iostream>

using namespace std;

#include "PlayerStrategies.h"




// HUMAN PLAYER STRATEGIES #############################################################################################
//Strategies for Reinforce ----------------------------------------------------------------------------------------------
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

//Strategies for Attack ------------------------------------------------------------------------------------------------
bool HumanPlayerStrategy::PromptPlayerToAttack(Player* player) {
    string answer;
    cout << "Does " << *player->GetPlayerName() << " want attack an opponent's country ? (enter 'y' to attack and any other character otherwise)" << endl;
    while(!(cin >> answer)) {
        cout << "Your answer is not correct, please choose a valid answer" << endl;
        cin.clear();
        cin.ignore(132, '\n');
    }
    return answer == "y";
}

bool HumanPlayerStrategy::SelectCountryToAttack(Player* player) {

}

bool HumanPlayerStrategy::SelectCountryToAttackFrom(Player* player) {
    player->GetAttackPhase()->SetAttackingCountry(nullptr);

    cout << "Please choose which country you would like to attack from (enter by numerical id):\n";

    //ask the player to select the country the wish to attack with
    AttackPhase* phase = player->GetAttackPhase();

    if(!phase) {
        cout << "Something went wrong! Aborting" << endl;
        return false;
    }

    phase->SetAttackingCountry(player->PromptPlayerToSelectCountry());

    if(phase->GetAttackingCountry()) {
        //keep looping until select the country with 2 or more armies
        while(phase->GetAttackingCountry()->GetNumberOfArmies() < 2) {
            cout << "You do not have enough armies in country " << *phase->GetAttackingCountry()->GetCountryName() << ". Please Try Again." << endl;
            phase->SetAttackingCountry(player->PromptPlayerToSelectCountry());
        }
        return true;
    } else {
        return false;
    }
}

void HumanPlayerStrategy::RollDiceToAttack(Player* player) {

}

//Strategies for Fortify -----------------------------------------------------------------------------------------------
void HumanPlayerStrategy::FortifyStrategy() {

}





// AGGRESSIVE PLAYER STRATEGIES ########################################################################################

//Strategies for Reinforce ----------------------------------------------------------------------------------------------
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

    country_num_army_to_add_pairs.insert({country_id_with_most_armies, num_bonus_army});
    num_bonus_army = 0;
}

//Strategies for Attack ------------------------------------------------------------------------------------------------
bool AggressiveComputerPlayerStrategy::PromptPlayerToAttack(Player* player) {
    //aggressive player always chooses to attack
    cout << *player->GetPlayerName() << " wants to attack " << endl;
    return true;
}

bool AggressiveComputerPlayerStrategy::SelectCountryToAttack(Player* player) {

}

bool AggressiveComputerPlayerStrategy::SelectCountryToAttackFrom(Player* player) {
    player->GetAttackPhase()->SetAttackingCountry(nullptr);

    //ask the player to select the country the wish to attack with
    AttackPhase* phase = player->GetAttackPhase();

    if(!phase) {
        cout << "Something went wrong! Aborting" << endl;
        return false;
    }

    int country_id = -1;
    int max_num_armies = 0;
    vector<Country*>& countries = *player->GetPlayersCountries();

   for(Country* country : countries) {

       if(country->GetNumberOfArmies() > max_num_armies) {
           vector<Country*>* neighbours = player->GetGameMap()->GetNeighbouringCountriesWithArmies(country);
            for(int i = 0; i < neighbours->size(); ++i) {
                if(player->DoesPlayerOwnCountry(country->GetCountryID())) {
                    neighbours->erase(neighbours->begin() + i);
                }
            }

            if(!neighbours->empty()) {
                max_num_armies = country->GetNumberOfArmies();
                country_id = country->GetCountryID();
            }
       }
   }

   if(country_id > 0) {
       Country* attacker = player->GetCountryById(country_id);
       if(attacker) {
           player->GetAttackPhase()->SetAttackingCountry(attacker);
       }
   }

   return player->GetAttackPhase()->GetAttackingCountry() != nullptr;
}

void AggressiveComputerPlayerStrategy::RollDiceToAttack(Player* player) {

}

//Strategies for Fortify -----------------------------------------------------------------------------------------------
void AggressiveComputerPlayerStrategy::FortifyStrategy() {

}




//BENEVOLANT PLAYER STRATEGIES #########################################################################################

//Strategies for Reinforce ----------------------------------------------------------------------------------------------
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
        country_num_army_to_add_pairs.insert({entry.second, 1});
        ++counter;
    }
}

//Strategies for Attack ------------------------------------------------------------------------------------------------
bool BenevolantComputerPlayerStrategy::PromptPlayerToAttack(Player* player) {
    //benevolant player never chooses to attack
    cout << *player->GetPlayerName() << " never wants to attack! Aborting" << endl;
    return false;
}

bool BenevolantComputerPlayerStrategy::SelectCountryToAttack(Player* player) {
    cout << "benevolant players never attack! Aborting" << endl;
    return false;
}

bool BenevolantComputerPlayerStrategy::SelectCountryToAttackFrom(Player* player) {
    cout << "benevolant players never attack! Aborting" << endl;
    return false;
}

void BenevolantComputerPlayerStrategy::RollDiceToAttack(Player* player) {
    cout << "benevolant players never attack! Aborting" << endl;
}

//Strategies for Fortify -----------------------------------------------------------------------------------------------
void BenevolantComputerPlayerStrategy::FortifyStrategy() {

}