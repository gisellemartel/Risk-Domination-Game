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
#include "../GameEngine/GameEngine.h"


// HUMAN PLAYER STRATEGIES #############################################################################################
//Strategies for Reinforce ----------------------------------------------------------------------------------------------
void HumanPlayerStrategy::ReinforceStrategy(Player* player) {
    ReinforcePhase* reinforce_phase = player->GetReinforcePhase();
    if(!reinforce_phase) {
        return;
    }

    int num_bonus_army = reinforce_phase->TotalReinforceArmy();
    int country_index = 0;
    int reinforce_value = 0;
    vector<Country*>* countries = player->GetPlayersCountries();

    if(!countries || countries->empty()) {
        return;
    }

    while(num_bonus_army > 0) {

        Country* current_country = countries->at(country_index);

        if(!current_country) {
            ++country_index;
            continue;
        }

        string msg = "Currently on Country\n" + current_country->GetDisplayInfo() + "Armies to assign: " + to_string(num_bonus_army) + "\nArmies to add to current country: ";
        player->Notify(player, GamePhase::Reinforce, msg, false, false);

        cin >> reinforce_value;
        while (cin.fail() || reinforce_value > num_bonus_army || reinforce_value < 0) {
            cout << "Invalid input. Pick a valid number: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> reinforce_value;
        }

        int country_id = current_country->GetCountryID();


        reinforce_phase->GetReinforceValues()->push_back(reinforce_value);
        reinforce_phase->GetCountriesToReinforce()->push_back(country_id);


        num_bonus_army -= reinforce_value;
        reinforce_phase->SetTotalReinforcementArmy(num_bonus_army);
        ++country_index;
        country_index = country_index % (int)countries->size();
    }
}

//Strategies for Attack ------------------------------------------------------------------------------------------------
bool HumanPlayerStrategy::PromptPlayerToAttack(Player* player) {

    string msg = "Does " + *player->GetPlayerName() + " want attack an opponent's country ? (enter 'y' to attack and any other character otherwise)\n";
    player->Notify(player, GamePhase::Attack, msg, false, false);

    string answer;
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

    player->GetAttackPhase()->SetDefendingCountry(nullptr);
    Country* defending_country = attack_phase->GetDefendingCountry();

    //Display neighboring countries
    cout << "\n\nHere are the neighbouring opponent countries to " + *attack_phase->GetAttackingCountry()->GetCountryName() + "\n";
    cout << endl << setw(25)  << left << "Country ID" << setw(25)  << "Name" << setw(25) <<  "Number of Armies" << setw(10) << right << "Neighbours" << endl;
    for (Country *country : *attack_phase->GetOpponentNeighbours()) {
        string neighbours_list = player->GetGameMap()->GenerateListOfNeighboringCountries(country);

        cout << setw(25)  << left << country->GetCountryID() <<
        setw(25) <<  *country->GetCountryName()
        << setw(25) << country->GetNumberOfArmies()  << setw(10) << right << neighbours_list << endl;
        cout << endl;
    }


    //prompt player to select country to attack from list of neighbours
    while(!defending_country) {
        string msg = "Please choose which country you would like to attack (enter by numerical id):\n";
        player->Notify(player, GamePhase::Attack, msg, false, false);

        int defender_id = -1;
        Country* defender = nullptr;

        while(!(cin >> defender_id) || defender_id < 1 || !(defending_country = player->GetCountryInVectorById(attack_phase->GetOpponentNeighbours(), defender_id)) || player->Find(defender) != -1) {
            cin.clear();
            cin.ignore(132, '\n');
            cout << "Invalid entry entered! Please try again: ";
        }
    }

    attack_phase->SetDefendingCountry(defending_country);
    attack_phase->SetDefender(defending_country->GetCountryOwner());

    return defending_country != nullptr;
}

bool HumanPlayerStrategy::SelectCountryToAttackFrom(Player* player) {
    cout << "The Countries that you own are\n";
    player->DisplayCountries();

    player->GetAttackPhase()->SetAttackingCountry(nullptr);

    cout << "Please choose which country you would like to attack from (enter by numerical id):\n";

    //ask the player to select the country the wish to attack with
    AttackPhase* phase = player->GetAttackPhase();

    if(!phase) {
        string msg = "Something went wrong! Aborting\n";
        player->Notify(player, GamePhase::Attack, msg, false, false);
        return false;
    }

    phase->SetAttackingCountry(player->PromptPlayerToSelectCountry());


    //if nothing was selected somehow fatal error return false
    if(!phase->GetAttackingCountry()) {
        return false;
    }

    //keep looping until select the country with 2 or more armies
    while(phase->GetAttackingCountry()->GetNumberOfArmies() < 2) {
        cout << "You do not have enough armies in country " + *phase->GetAttackingCountry()->GetCountryName() + ". Please Try Again.\n";
        phase->SetAttackingCountry(player->PromptPlayerToSelectCountry());
    }

    return true;
}

void HumanPlayerStrategy::AttackerSelectNumberOfDice(Player* player, const int MAX_NUM_OF_DICE_ATTACKER,  int& attacker_num_dice) {
    AttackPhase* attack_phase = player->GetAttackPhase();
    if(!attack_phase) {
        return;
    }

    //prompt each player to enter the num of dice they wish to roll
    string msg = "\nIt is " + *player->GetPlayerName() + "'s turn to enter the number of dice they wish to roll (can roll max " + to_string(MAX_NUM_OF_DICE_ATTACKER) + ") dice: ";
    player->Notify(player, GamePhase::Attack, msg, false, false);

    while( !(cin >> attacker_num_dice) || attacker_num_dice < 1 || attacker_num_dice > MAX_NUM_OF_DICE_ATTACKER) {
        cout << "\nYou have entered an invalid number of dice to roll. Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }
}

void HumanPlayerStrategy::MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) {
    //prompt attacker if they would like to assign armies from their newly acquired country to their other countries

    string msg = *player->GetPlayerName() + " would you like to move armies from " + *attacking_country->GetCountryName() + " to " + *defending_country->GetCountryName() + "? (enter 'y' if so and any other character otherwise)\n";

    player->GetGameEngine()->Notify(player, GamePhase::Attack, msg, false, false );
    string user_response;
    while(!(cin >> user_response)) {
        cout << "\nInvalid input given! Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    if(user_response == "y") {
        msg = "How many armies would you like to assign to " + *defending_country->GetCountryName() + " from " + *attacking_country->GetCountryName() + "? (you can assign a max of " + to_string(attacking_country->GetNumberOfArmies()) + "): ";
        player->GetGameEngine()->Notify(player, GamePhase::Attack, msg, false, false );

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

bool HumanPlayerStrategy::PromptPlayerToFortify(Player *player) {
    string answer;

    string msg = "Does " + *player->GetPlayerName() + " wish to fortify a country? (Enter y, any other char otherwise):\n";
    player->GetGameEngine()->Notify(player, GamePhase::Fortify, msg, false, false );

    while(!(cin >> answer)) {
        cout << "Your answer is not correct, please choose a valid answer" << endl;
        cin.clear();
        cin.ignore(132, '\n');
    }
    return answer == "y";
}

bool HumanPlayerStrategy::SelectSourceCountry(Player *player) {
    FortifyPhase* fortify_phase = player->GetFortifyPhase();
    if(!fortify_phase) {
        return false;
    }

    player->DisplayCountries();

    string msg = "Please choose your source country \n";
    player->GetGameEngine()->Notify(player, GamePhase::Fortify, msg, false, false );

    Country* selected_country = player->PromptPlayerToSelectCountry();

    while(!selected_country || (selected_country && selected_country->GetNumberOfArmies() < 1) ) {
        cout << "You do not have enough armies in selected country. Please Try Again." << endl;
        selected_country = player->PromptPlayerToSelectCountry();
    }

    fortify_phase->SetSourceCountry(selected_country);
    return fortify_phase->GetSourceCountry() != nullptr;
}

bool HumanPlayerStrategy::SelectTargetCountry(Player *player) {
    FortifyPhase* fortify_phase = player->GetFortifyPhase();
    if(!fortify_phase) {
        return false;
    }

    string msg = "Please choose which country you would like to fortify (enter by numerical id):\n";
    player->GetGameEngine()->Notify(player, GamePhase::Fortify, msg, false, false );

    int fortify_id;

    Country* target = nullptr;
    while(!(cin >> fortify_id) || fortify_id < 1 || !(target = player->GetCountryInVectorById(fortify_phase->GetNeighboursToFortify(), fortify_id))) {
        cout << "Invalid entry entered! Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    fortify_phase->SetTargetCountry(target);

    return fortify_phase->GetTargetCountry() != nullptr;
}

void HumanPlayerStrategy::FortifyStrategy(Player* player, int& num_of_armies) {
    FortifyPhase* fortify_phase = player->GetFortifyPhase();
    if(!fortify_phase) {
        return;
    }

    string msg = "How many armies do you wish to move.(Enter a number):\n";
    player->GetGameEngine()->Notify(player, GamePhase::Fortify, msg, false, false );


    while (!(cin >> num_of_armies) || num_of_armies < 1 || num_of_armies > fortify_phase->GetSourceCountry()->GetNumberOfArmies()) {
        cout << "Invalid number of armies selected! Please try again\n";
        cin.clear();
        cin.ignore(132, '\n');
    }
}





// AGGRESSIVE PLAYER STRATEGIES ########################################################################################

//Strategies for Reinforce ----------------------------------------------------------------------------------------------
void AggressiveComputerPlayerStrategy::ReinforceStrategy(Player* player) {
    ReinforcePhase* reinforce_phase = player->GetReinforcePhase();
    if(!reinforce_phase) {
        return;
    }
    vector<Country*>* countries = player->GetPlayersCountries();
    int num_bonus_army = reinforce_phase->TotalReinforceArmy();
    int max_num_armies = 0;
    int country_id_with_most_armies = 1;

    for(Country* country : *countries) {
        int num_armies = country->GetNumberOfArmies();

        if(num_armies > max_num_armies) {
            max_num_armies = num_armies;
            country_id_with_most_armies = country->GetCountryID();
        }
    }

    //aggressive player will reinforce the strongest country will all the available reinforcements
    reinforce_phase->GetReinforceValues()->push_back(num_bonus_army);
    reinforce_phase->GetCountriesToReinforce()->push_back(country_id_with_most_armies);
    reinforce_phase->SetTotalReinforcementArmy(0);
}

//Strategies for Attack ------------------------------------------------------------------------------------------------
bool AggressiveComputerPlayerStrategy::PromptPlayerToAttack(Player* player) {
    //aggressive player always chooses to attack
    return true;
}

bool AggressiveComputerPlayerStrategy::SelectCountryToAttack(Player* player) {
    AttackPhase* attack_phase = player->GetAttackPhase();
    if(!attack_phase) {
        return false;
    }

    Country* defending_country = nullptr;

    //Display neighboring countries
   string msg = "\n\nHere are the neighbouring opponent countries to " + *attack_phase->GetAttackingCountry()->GetCountryName() + "\n";

   player->Notify(player, GamePhase::Attack, msg, false, false);

    cout << endl << setw(25)  << left << "Country ID" << setw(25)  << "Name" << setw(25) <<  "Number of Armies" << setw(10) << right << "Neighbours" << endl;
    for (Country *country : *attack_phase->GetOpponentNeighbours()) {
        string neighbours_list =  player->GetGameMap()->GenerateListOfNeighboringCountries(country);
        cout << setw(25)  << left << country->GetCountryID() << setw(25) <<  *country->GetCountryName() << setw(25)
        << country->GetNumberOfArmies()  << setw(10) << right << neighbours_list << endl;
        cout << endl;
    }

    //iterate over all opponents until one is found
    for(Country* opponent : *attack_phase->GetOpponentNeighbours()) {
        defending_country = opponent;
        msg = *player->GetPlayerName() + " chooses to attack " + *opponent->GetCountryName() + "\n";
        player->Notify(player, GamePhase::Attack, msg, false, false);
        break;
    }


    if(defending_country) {
        attack_phase->SetDefendingCountry(defending_country);
        attack_phase->SetDefender(defending_country->GetCountryOwner());
    }

    return defending_country != nullptr;
}

bool AggressiveComputerPlayerStrategy::SelectCountryToAttackFrom(Player* player) {

    //ask the player to select the country the wish to attack with
    AttackPhase* phase = player->GetAttackPhase();

    if(!phase) {
        string msg = "Something went wrong! Aborting\n";
        player->Notify(player, GamePhase::Attack, msg, false, false);
        return false;
    }

    player->GetAttackPhase()->SetAttackingCountry(nullptr);
    multimap<int, Country*> countries_sorted_by_strength;
    vector<Country*>& countries = *player->GetPlayersCountries();

    //sort countries by number of armies.
   for(Country* country : countries) {
       if(country->GetNumberOfArmies() < 2) {
           continue;
       }

       vector<Country*>* neighbours = player->GetGameMap()->GetNeighbouringCountries(country);

       //make sure current country has at least one neighbour opponent to attack
        for(int i = 0; i < neighbours->size(); ++i) {
            if(player->DoesPlayerOwnCountry(country->GetCountryID())) {
                neighbours->erase(neighbours->begin() + i);
            }
        }

        //as long as the current country has opposing countries with armies
        if(!neighbours->empty()) {
            countries_sorted_by_strength.insert({country->GetNumberOfArmies(), country});
        }
   }

   if(countries_sorted_by_strength.empty()) {
       string msg = "Currently no country exists that can attack right now\n";
       player->Notify(player, GamePhase::Attack, msg, false, false);
       return false;
   }

   for(auto attacker : countries_sorted_by_strength) {
       if(!attacker.second) {
           continue;
       } else {
           player->GetAttackPhase()->SetAttackingCountry(attacker.second);
           break;
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
    string msg = "\nIt is " + *player->GetPlayerName() + "'s turn to enter the number of dice they wish to roll (can roll max " + to_string(MAX_NUM_OF_DICE_ATTACKER) + ") dice: ";
    player->Notify(player, GamePhase::Attack, msg, false, false);

    attacker_num_dice = Utility::GenerateRandomNumInRange(1, MAX_NUM_OF_DICE_ATTACKER);
}

void AggressiveComputerPlayerStrategy::MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) {

    string msg = *player->GetPlayerName() + " is moving armies from " + *attacking_country->GetCountryName() + " to " + *defending_country->GetCountryName() + "\n";
    player->Notify(player, GamePhase::Attack, msg, false, false);

    //Aggressive player will move all armies to their strongest country
    int num_armies_to_assign = attacking_country->GetNumberOfArmies();
    Country* newly_acquired_country = player->GetCountryById(defending_country->GetCountryID());

    if(newly_acquired_country) {
        newly_acquired_country->SetNumberOfArmies(num_armies_to_assign);
        attacking_country->RemoveArmiesFromCountry(num_armies_to_assign);
    }

}

//Strategies for Fortify -----------------------------------------------------------------------------------------------

bool AggressiveComputerPlayerStrategy::PromptPlayerToFortify(Player *player) {
    // Aggressive player always wants to fortify
    return true;
}

bool AggressiveComputerPlayerStrategy::SelectSourceCountry(Player *player) {
    FortifyPhase* fortify_phase = player->GetFortifyPhase();
    if(!fortify_phase) {
        return false;
    }

    fortify_phase->SetSourceCountry(nullptr);

    int max_num_armies = 0;
    int country_id = 1;

    for(Country* country : *player->GetPlayersCountries()) {
        if(country->GetNumberOfArmies() > max_num_armies) {
            country_id = country->GetCountryID();
            max_num_armies = country->GetNumberOfArmies();
        }
    }
    Country* strongest_country = player->GetCountryById(country_id);

    vector<Country*>* neighbours_of_stongest_country = player->GetGameMap()->GetNeighbouringCountries(strongest_country);

    if(neighbours_of_stongest_country->empty()) {
        return false;
    }

    //there needs to be at least one neighbour to the strongest country that has armies and belongs to current player
    for(Country* country : *neighbours_of_stongest_country) {
        if(player->DoesPlayerOwnCountry(country->GetCountryID()) && country->GetNumberOfArmies() > 0) {
            fortify_phase->SetSourceCountry(country);
        }
    }

    if(!fortify_phase->GetSourceCountry()) {
        string msg = "Only one country has armies right now. Aggressive player prefers to keep all their armies in strongest country\n";
        player->Notify(player, GamePhase::Fortify, msg, false, false);
    }

    return fortify_phase->GetSourceCountry() != nullptr;
}

bool AggressiveComputerPlayerStrategy::SelectTargetCountry(Player *player) {
    FortifyPhase* fortify_phase = player->GetFortifyPhase();
    if(!fortify_phase) {
        return false;
    }

    if(fortify_phase->GetNeighboursToFortify()->empty()) {
        return false;
    }

    fortify_phase->SetTargetCountry(nullptr);


    //fortify the strongest army
    int max_num_armies = 0;
    int country_id = 1;

    for(Country* neighbour : *fortify_phase->GetNeighboursToFortify()) {
        if(neighbour->GetNumberOfArmies() > max_num_armies) {
            max_num_armies = neighbour->GetNumberOfArmies();
            country_id = neighbour->GetCountryID();
        }
    }

    fortify_phase->SetTargetCountry(player->GetCountryById(country_id));

    return fortify_phase->GetTargetCountry() != nullptr;
}

void AggressiveComputerPlayerStrategy::FortifyStrategy(Player* player, int& num_of_armies) {
    FortifyPhase* fortify_phase = player->GetFortifyPhase();
    if(!fortify_phase) {
        return;
    }
    num_of_armies = fortify_phase->GetSourceCountry()->GetNumberOfArmies();
}



//BENEVOLANT PLAYER STRATEGIES #########################################################################################

//Strategies for Reinforce ----------------------------------------------------------------------------------------------
void BenevolantComputerPlayerStrategy::ReinforceStrategy(Player* player) {

    ReinforcePhase* reinforce_phase = player->GetReinforcePhase();
    if(!reinforce_phase) {
        return;
    }
    vector<Country*>* countries = player->GetPlayersCountries();

    //use a sorted map to arrange the countries from weakest to strongest
    multimap<int, int> country_num_army_pairs;

    //populate the map in order of weakest to strongest
    for(Country* country : *countries) {
        int num_armies = country->GetNumberOfArmies();
        country_num_army_pairs.insert({num_armies, country->GetCountryID()});
    }

    //give 1 army to each of the weakest countries (number of weakest countries == num_bonus_army)
    int counter = 0;
    for(auto& entry : country_num_army_pairs) {
        if(counter == reinforce_phase->TotalReinforceArmy()) {
            break;
        }
        reinforce_phase->GetReinforceValues()->push_back(1);
        reinforce_phase->GetCountriesToReinforce()->push_back(entry.second);
        ++counter;
    }
}

//Strategies for Attack ------------------------------------------------------------------------------------------------
bool BenevolantComputerPlayerStrategy::PromptPlayerToAttack(Player* player) {
// benevolant players never attack
    return false;
}

bool BenevolantComputerPlayerStrategy::SelectCountryToAttack(Player* player) {
   // benevolant players never attack
    return false;
}

bool BenevolantComputerPlayerStrategy::SelectCountryToAttackFrom(Player* player) {
   //benevolant players never attack
    return false;
}

void BenevolantComputerPlayerStrategy::AttackerSelectNumberOfDice(Player* player, const int MAX_NUM_OF_DICE_ATTACKER,  int& attacker_num_dice)  {
    // benevolant players never attack
}

void BenevolantComputerPlayerStrategy::MoveArmiesAfterAttack(Player* player, Country* attacking_country, Country* defending_country) {
    // benevolant players never attack
}

//Strategies for Fortify -----------------------------------------------------------------------------------------------

bool BenevolantComputerPlayerStrategy::PromptPlayerToFortify(Player *player) {
    // Benevolant player always wants to fortify
    return true;
}

bool BenevolantComputerPlayerStrategy::SelectSourceCountry(Player *player) {
    FortifyPhase* fortify_phase = player->GetFortifyPhase();
    if(!fortify_phase) {
        return false;
    }

    fortify_phase->SetSourceCountry(nullptr);

    //find the strongest country which will be used to fortify the weaker countries
    int max_num_armies = 0;
    int country_id = 1;

    for(Country* country : *player->GetPlayersCountries()) {
        if(country->GetNumberOfArmies() > max_num_armies) {
            country_id = country->GetCountryID();
            max_num_armies = country->GetNumberOfArmies();
        }
    }

    if(max_num_armies < 1) {
        string msg = "You have no countries with enough armies to fortify others\n";
        player->Notify(player, GamePhase::Fortify, msg, false, false);
        return false;
    }

    fortify_phase->SetSourceCountry(player->GetCountryById(country_id));

    return fortify_phase->GetSourceCountry() != nullptr;
}

bool BenevolantComputerPlayerStrategy::SelectTargetCountry(Player *player) {
    FortifyPhase* fortify_phase = player->GetFortifyPhase();
    if(!fortify_phase) {
        return false;
    }

    if(fortify_phase->GetNeighboursToFortify()->empty()) {
        return false;
    }


    fortify_phase->SetTargetCountry(nullptr);


    int min_num_armies = fortify_phase->GetSourceCountry()->GetNumberOfArmies();
    int weakest_country_id = 1;

    for(Country* country : *fortify_phase->GetNeighboursToFortify()) {
        if(country->GetNumberOfArmies() < min_num_armies) {
            min_num_armies = country->GetNumberOfArmies();
            weakest_country_id = country->GetCountryID();
        }
    }

    fortify_phase->SetTargetCountry(player->GetCountryById(weakest_country_id));

    return fortify_phase->GetTargetCountry() != nullptr;
}

void BenevolantComputerPlayerStrategy::FortifyStrategy(Player* player, int& num_of_armies) {
    FortifyPhase* fortify_phase = player->GetFortifyPhase();
    if(!fortify_phase) {
        return;
    }
    num_of_armies = Utility::GenerateRandomNumInRange(1, fortify_phase->GetSourceCountry()->GetNumberOfArmies());
}