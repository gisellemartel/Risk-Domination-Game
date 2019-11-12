/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */
#include <iostream>
#include <string>
#include <random>
#include <filesystem>

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
    AttackPhase* attack_phase = player->GetAttackPhase();
    if(!attack_phase) {
        return false;
    }

    Country* defending_country = attack_phase->GetDefendingCountry();
    //prompt player to select country to attack from list of neighbours
    while(!defending_country) {
       // defending_country = PromptPlayerToSelectDefender(attack_phase->GetOpponentNeighbours());

        //Display neighboring countries
        cout << "\n\nHere are the neighbouring opponent countries to " << *attack_phase->GetAttackingCountry()->GetCountryName() << endl;
        cout << endl << setw(25)  << left << "Country ID" << setw(25)  << "Name" << setw(25) <<  "Number of Armies" << setw(10) << right << endl;
        for (const Country *country : *attack_phase->GetOpponentNeighbours()) {
            cout << setw(25)  << left << country->GetCountryID() << setw(25) <<  *country->GetCountryName() << setw(25) << country->GetNumberOfArmies()  << setw(10) << right << player->GetGameMap()->GenerateListOfNeighboringCountries(attack_phase->GetAttackingCountry()) << endl;
            cout << endl;
        }

        cout << "Please choose which country you would like to attack (enter by numerical id):\n";
        int defender_id = -1;
        Country* defender = nullptr;

        while(!(cin >> defender_id) || defender_id < 1 || !(defending_country = player->GetCountryInVectorById(attack_phase->GetOpponentNeighbours(), defender_id)) || player->Find(defender) != -1) {
            cin.clear();
            cin.ignore(132, '\n');
            cout << "Invalid entry entered! Please try again: ";
        }
    }

    if(defending_country) {
        attack_phase->SetDefendingCountry(defending_country);
        attack_phase->SetDefender(defending_country->GetCountryOwner());
    }

    return defending_country != nullptr;
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

void HumanPlayerStrategy::AttackerSelectNumberOfDice(Player* player, const int MAX_NUM_OF_DICE_ATTACKER,  int& attacker_num_dice) {
    AttackPhase* attack_phase = player->GetAttackPhase();
    if(!attack_phase) {
        return;
    }

    //prompt each player to enter the num of dice they wish to roll
    cout << "\nIt is " << *player->GetPlayerName() << "'s turn to enter the number of dice they wish to roll (can roll max " << MAX_NUM_OF_DICE_ATTACKER << ") dice: ";

    while( !(cin >> attacker_num_dice) || attacker_num_dice < 1 || attacker_num_dice > MAX_NUM_OF_DICE_ATTACKER) {
        cout << "\nYou have entered an invalid number of dice to roll. Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }
}

void HumanPlayerStrategy::MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) {
    //prompt attacker if they would like to assign armies from their newly acquired country to their other countries
    cout << *player->GetPlayerName() << " would you like to move armies from " << *attacking_country->GetCountryName() << " to " << *defending_country->GetCountryName() << "? (enter 'y' if so and any other character otherwise\n";

    string user_response;
    while(!(cin >> user_response)) {
        cout << "\nInvalid input given! Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    if(user_response == "y") {
        cout << "How many armies would you like to assign to " << *defending_country->GetCountryName() << " from " << *attacking_country->GetCountryName() << "? (you can assign a max of " << attacking_country->GetNumberOfArmies() << "): ";
        int num_armies_to_assign;

        while(!(cin >> num_armies_to_assign) || num_armies_to_assign < 1 || num_armies_to_assign > attacking_country->GetNumberOfArmies()) {
            cout << "\nInvalid input given! Please try again: ";
            cin.clear();
            cin.ignore(132, '\n');
        }

        Country* newly_acquired_country = player->GetCountryById(defending_country->GetCountryID());

        if(newly_acquired_country) {
            newly_acquired_country->SetNumberOfArmies(num_armies_to_assign);
            attacking_country->RemoveArmiesFromCountry(num_armies_to_assign);
        }

    } else {
        return;
    }
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
    AttackPhase* attack_phase = player->GetAttackPhase();
    if(!attack_phase) {
        return false;
    }

    Country* defending_country = nullptr;

    //Display neighboring countries
    cout << "\n\nHere are the neighbouring opponent countries to " << *attack_phase->GetAttackingCountry()->GetCountryName() << endl;
    cout << endl << setw(25)  << left << "Country ID" << setw(25)  << "Name" << setw(25) <<  "Number of Armies" << setw(10) << right << endl;
    for (const Country *country : *attack_phase->GetOpponentNeighbours()) {
        cout << setw(25)  << left << country->GetCountryID() << setw(25) <<  *country->GetCountryName() << setw(25) << country->GetNumberOfArmies()  << setw(10) << right << player->GetGameMap()->GenerateListOfNeighboringCountries(attack_phase->GetAttackingCountry()) << endl;
        cout << endl;
    }

    //iterate over all opponents until one is found with at least 2 armies
    for(Country* opponent : *attack_phase->GetOpponentNeighbours()) {
        if(opponent->GetNumberOfArmies() > 2) {
            defending_country = opponent;
            cout << *player->GetPlayerName() << "chooses to attack " << *opponent->GetCountryName() << "\n";
            break;
        }
    }


    if(defending_country) {
        attack_phase->SetDefendingCountry(defending_country);
        attack_phase->SetDefender(defending_country->GetCountryOwner());
    }

    return defending_country != nullptr;
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

void AggressiveComputerPlayerStrategy::AttackerSelectNumberOfDice(Player* player, const int MAX_NUM_OF_DICE_ATTACKER,  int& attacker_num_dice)  {
    AttackPhase* attack_phase = player->GetAttackPhase();
    if(!attack_phase) {
        return;
    }

    //prompt each player to enter the num of dice they wish to roll
    cout << "\nIt is " << *player->GetPlayerName() << "'s turn to enter the number of dice they wish to roll (can roll max " << MAX_NUM_OF_DICE_ATTACKER << ") dice: ";

    attacker_num_dice = Utility::GenerateRandomNumInRange(1, MAX_NUM_OF_DICE_ATTACKER);
}

void AggressiveComputerPlayerStrategy::MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) {

    cout << *player->GetPlayerName() << " is moving armies from " << *attacking_country->GetCountryName() << " to " << *defending_country->GetCountryName() << endl;

    //Aggressive player will move all armies to their strongest country
    int num_armies_to_assign = attacking_country->GetNumberOfArmies();
    Country* newly_acquired_country = player->GetCountryById(defending_country->GetCountryID());

    if(newly_acquired_country) {
        newly_acquired_country->SetNumberOfArmies(num_armies_to_assign);
        attacking_country->RemoveArmiesFromCountry(num_armies_to_assign);
    }

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

void BenevolantComputerPlayerStrategy::AttackerSelectNumberOfDice(Player* player, const int MAX_NUM_OF_DICE_ATTACKER,  int& attacker_num_dice)  {
    cout << "benevolant players never attack! Aborting" << endl;
}

void BenevolantComputerPlayerStrategy::MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) {
    cout << "benevolant players never attack! Aborting" << endl;
}

//Strategies for Fortify -----------------------------------------------------------------------------------------------
void BenevolantComputerPlayerStrategy::FortifyStrategy() {

}