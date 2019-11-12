/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include <map>
#include <iterator>
#include <filesystem>

using namespace std;

#include "Player.h"

// Player class implementation ----------------------------------------------------------------------------

Player::Player(string player_name) {
    player_name_ = new string(player_name);
    is_player_turn_ = false;
    is_human_ = false;
    countries_ = new vector<Country*>;
    risk_cards_ = nullptr;
    dice_roll_ = nullptr;
    game_map_ = nullptr;
    player_strategy_ = nullptr;
    attack_phase_ = nullptr;
}

Player::Player(string player_name, Map *game_map) {
    player_name_ = new string(player_name);
    game_map_ = game_map;
    is_player_turn_ = false;
    is_human_ = false;
    countries_ = new vector<Country*>;
    risk_cards_ = nullptr;
    dice_roll_ = nullptr;
    player_strategy_ = nullptr;
    attack_phase_ = nullptr;
}

Player::Player(string player_name, vector<Country*>* countries_to_assign_to_player, bool is_player_turn) {
    player_name_ = new string(player_name);
    is_player_turn_ = is_player_turn;
    is_human_ = false;
    //countries to be assigned to each player are chosen randomly at start-up phase
    countries_ = countries_to_assign_to_player;
    risk_cards_ = nullptr;
    dice_roll_ = nullptr;
    game_map_ = nullptr;
    player_strategy_ = nullptr;
    attack_phase_ = nullptr;
}

Player::Player(const Player &player) {
    player_name_ = player.player_name_;
    is_player_turn_ = player.is_player_turn_;
    is_human_ = player.is_human_;

    for(size_t i = 0; i < player.countries_->size(); ++i) {
        countries_[i] = player.countries_[i];
    }
    countries_ = player.countries_;
    risk_cards_ = player.risk_cards_;
    dice_roll_ = player.dice_roll_;
    game_map_ = player.game_map_;
    player_strategy_ = player.player_strategy_;
    attack_phase_ = player.attack_phase_;
}

Player::~Player() {

    for(Country* country : *countries_) {
        country = nullptr;
        delete country;
    }
    risk_cards_ = nullptr;
    countries_ = nullptr;
    dice_roll_ = nullptr;
    game_map_ = nullptr;
    player_strategy_ = nullptr;
    attack_phase_ = nullptr;

    delete risk_cards_;
    delete countries_;
    delete dice_roll_;
    delete game_map_;
    delete player_strategy_;
    delete attack_phase_;
}

Player& Player::operator=(const Player &player) {
    player_name_ = player.player_name_;
    is_player_turn_ = player.is_player_turn_;
    is_human_ = player.is_human_;

    for(size_t i = 0; i < player.countries_->size(); ++i) {
        countries_[i] = player.countries_[i];
    }

    risk_cards_ = player.risk_cards_;
    countries_ = player.countries_;
    dice_roll_ = player.dice_roll_;
    game_map_ = player.game_map_;
    player_strategy_ = player.player_strategy_;
    attack_phase_ = player.attack_phase_;
    return *this;
}

bool Player::operator==(const Player& player) {
    return player_name_ == player.player_name_
            && is_player_turn_ == player.is_player_turn_
            && countries_ == player.countries_
            && risk_cards_ == player.risk_cards_
            && dice_roll_ == player.dice_roll_
            && game_map_ == player.game_map_
            && player_strategy_ == player.player_strategy_
            && attack_phase_ == player.attack_phase_;
}

int Player::Find(Country* country) const {
    for(int i = 0; i < countries_->size(); ++i) {
        if((*countries_)[i] == country) {
            return i;
        }
    }
    return -1;
}

bool Player::DoesPlayerOwnCountry(int id) const {
    for(const Country* country : *countries_) {
        int current_id = (country->GetCountryID());
        if (id == current_id) {
            return true;
        }
    }
    return false;
}

bool Player::IsCurrentlyPlayersTurn() const {
    return is_player_turn_;
}

vector<Country*>* Player::GetPlayersCountries() const {
    return countries_;
}

bool Player::IsHuman() const {
    return is_human_;
}

Country* Player::GetCountryById(int id) const {
    for(Country* country : *countries_) {
        int current_id = (country->GetCountryID());
        if (id == current_id) {
            return country;
        }
    }
    return nullptr;
}

Country* Player::GetCountryInVectorById(vector<Country*>* countries, int country_id) {
    for(Country* country : *countries) {
        if(country->GetCountryID() == country_id) {
            return country;
        }
    }
    return nullptr;
}

Country* Player::PromptPlayerToSelectCountry() const {
    int country_id;
    while(!(cin >> country_id) || country_id < 1 || !DoesPlayerOwnCountry(country_id) ) {
        cin.clear();
        cin.ignore(132, '\n');
        cout << "Invalid entry entered! Please try again: ";
    }
    return GetCountryById(country_id);
}

AttackPhase* Player::GetAttackPhase() const {
    return attack_phase_;
}

Dice* Player::GetPlayerDice() const {
    return dice_roll_;
}

Hand* Player::GetPlayersCards() const {
    return risk_cards_;
}

Map* Player::GetGameMap() const {
    return game_map_;
}

string* Player::GetPlayerName() const {
    return player_name_;
}

void Player::SetPlayersTurn(bool is_turn) {
    is_player_turn_ = is_turn;
}

void Player::SetPlayerName(string* player_name) {
    player_name_ = player_name;
}

void Player::SetPlayerDice(Dice *dice) {
    dice_roll_ = dice;
}

void Player::SetPlayerHand(Hand* hand) {
    risk_cards_ = hand;
}

void Player::SetNumberOfArmies(int number_of_armies) {
    number_of_armies_ = number_of_armies;
}

void Player::SetPlayerStrategy(ConcreteStrategies *player_strategy) {
    player_strategy_ = player_strategy;
}

void Player::SetGameMap(Map* map) {
    game_map_ = map;
}

void Player::SetAsHuman() {
    is_human_ = true;
}

void Player::AddCountryToCollection(Country *country) {
    if(!countries_) {
        countries_ = new vector<Country*>;
    }
    countries_->push_back(country);
    country->SetCountryOwner(this);
}

void Player::RemoveCountryFromCollection(Country* country) {
    if(!countries_ || countries_->empty() || Find(country) == -1){
        cout << *country->GetCountryName() << " not found among " << *player_name_ << "'s countries!\n";
        return;
    }
    countries_->erase (countries_->begin() + Find(country));
}

void Player::AddCardToCollection(Cards* card) {
    if(!risk_cards_) {
        risk_cards_ = new Hand;
    }
    risk_cards_->AddCardToHand(card);
}

void Player::DisplayPlayerStats() const {
    cout << "\n===================================================\n" << *player_name_ << endl;
    cout << "Number of countries owned: " << countries_->size();
    cout << endl;

    cout << "Number cards in hand: " << risk_cards_->GetNumberOfCardsInHand();
    risk_cards_->DisplayHand();
    cout << endl;

    cout << "Total dice rolls made: " << dice_roll_->GetTotalRolls();
    cout << endl;

    cout << "Is it " << *player_name_ << "'s turn? ";
    string result = is_player_turn_ ? "true" : "false";

    cout << result << "\n===================================================\n";
}

void Player::DisplayCountries() const {
    cout << endl;
    cout << endl << setw(25)  << left << "Country ID" << setw(25)  << "Name" << setw(25) << "Number of Armies" << setw(10) << right << "Neighbouring Countries" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    for (Country *country : *countries_) {
        cout << setw(25)  << left << country->GetCountryID() << setw(25) <<  *country->GetCountryName() << setw(25) << country->GetNumberOfArmies() << setw(10) << right << game_map_->GenerateListOfNeighboringCountries(country) << endl;
        cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << endl;
    }
    cout << endl;
}

void Player::Reinforce() {
    if(!player_strategy_) {
        cout << "Player strategy undefined! Cannot Reinforce!" << endl;
        return;
    }


    cout << "\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Beginning Reinforce phase for " << *player_name_ << endl << endl;

    ReinforcePhase* reinforce = new ReinforcePhase(this, 0);
    int num_bonus_army = reinforce->TotalReinforceArmy();

    if(num_bonus_army < 1) {
        cout << *player_name_ << " currently has to armies to reinforce a country with. Please try again next round" << endl;
    }

    map<int, int> country_army_map;

    player_strategy_->ReinforceStrategy(*countries_, country_army_map, num_bonus_army);

    for(auto& entry : country_army_map) {
        Country* current_country = GetCountryById(entry.first);

        if(!current_country) {
            continue;
        }

        int num_armies_to_add = entry.second;
        int current_num_armies = current_country->GetNumberOfArmies();

        cout << *current_country->GetCountryName() << " | #armies: " << current_country->GetNumberOfArmies() << endl;
        cout << *player_name_  << " reinforcing " << *current_country->GetCountryName() << " with " << num_armies_to_add << " armies" << endl;
        current_country->SetNumberOfArmies(current_num_armies + num_armies_to_add);
        cout << "Result: " << *current_country->GetCountryName() << " | #armies: " << current_country->GetNumberOfArmies() << endl << endl;
    }

    cout << "\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void Player::Attack() {
    if(!player_strategy_) {
        cout << "Player strategy undefined! Cannot Attack!" << endl;
        return;
    }

    cout << "\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Beginning Attack phase for " << *player_name_ << endl << endl;

    attack_phase_ = new AttackPhase(this);

    while (player_strategy_->PromptPlayerToAttack(this)) {

        //TODO: refactor into function inside attackphase -----------------------------------------------------------------
        //check here to see if there is not a single country that can attack
        bool country_that_can_be_attacked_exists = false;
        for(Country* country : *countries_) {

            if(country->GetNumberOfArmies() > 1) {
                //Get all the neighbouring countries that have armies
                vector<Country*>* neighbouring_countries = game_map_->GetNeighbouringCountriesWithArmies(country);

                if(!neighbouring_countries->empty()) {
                    //if there is a neighbour that has an army, then verify the country belongs to an opponent
                    for(int i = 0; i < neighbouring_countries->size(); ++i) {
                        if(DoesPlayerOwnCountry((*neighbouring_countries)[i]->GetCountryID())) {
                            neighbouring_countries->erase(neighbouring_countries->begin() + i);
                        }
                    }
                }

                //if there is a country remaining in the vector, it means there exists at least one the attacker can attack
                if(!neighbouring_countries->empty()) {
                    country_that_can_be_attacked_exists = true;
                }
            }
        }

        if(!country_that_can_be_attacked_exists) {
            cout << "No opposing neighbour exists that you can attack right now\n";
            return;
        }

        //TODO: END HERE refactor into function inside attackphase -----------------------------------------------------------------

        cout << "The Countries that you own are " << endl;
        DisplayCountries();

        bool can_attack = player_strategy_->SelectCountryToAttackFrom(this);

        attack_phase_->FindOpponentNeighboursToAttackingCountry();

        can_attack &= !attack_phase_->GetOpponentNeighbours()->empty();

        if(can_attack) {
            can_attack &= player_strategy_->SelectCountryToAttack(this);

            while(!can_attack){
                cout << *player_name_ << " cannot attack since no neighbouring countries have armies!\n";
                can_attack = player_strategy_->SelectCountryToAttackFrom(this);
                can_attack &= player_strategy_->SelectCountryToAttack(this);
            }


            Country* attacking_country = attack_phase_->GetAttackingCountry();
            Country* defending_country = attack_phase_->GetDefendingCountry();
            Player* defender = defending_country->GetCountryOwner();
            int attacker_num_dice = 0;
            int defender_num_dice = 0;
            //determine maximum number of rolls for each player based on rules of Risk
            const int MAX_NUM_OF_DICE_ATTACKER = (attacking_country->GetNumberOfArmies() - 1) < 3 ? attacking_country ->GetNumberOfArmies() : 3;
            const int MAX_NUM_OF_DICE_DEFENDER = (defending_country->GetNumberOfArmies()) < 2 ? defending_country ->GetNumberOfArmies() : 2;

            player_strategy_->RollDiceToAttack(this, MAX_NUM_OF_DICE_ATTACKER, MAX_NUM_OF_DICE_DEFENDER, attacker_num_dice, defender_num_dice);


            vector<int> attacker_dice_rolls = dice_roll_->Roll(attacker_num_dice);
            cout << "Attacker dice rolled:\n";
            for(int i : attacker_dice_rolls) {
                cout << i << endl;
            }
            vector<int> defender_dice_rolls = defender->GetPlayerDice()->Roll(defender_num_dice);
            cout << "Defender dice rolled:\n";
            for(int i : defender_dice_rolls) {
                cout << i << endl;
            }
            cout << endl;

            //sort the rolls from highest value to lowest value
            sort(attacker_dice_rolls.begin(), attacker_dice_rolls.end());
            reverse(attacker_dice_rolls.begin(), attacker_dice_rolls.end());
            sort(defender_dice_rolls.begin(), defender_dice_rolls.end());
            reverse(defender_dice_rolls.begin(), defender_dice_rolls.end());

            int num_of_iterations = (attacker_dice_rolls.size() == defender_dice_rolls.size() || attacker_dice_rolls.size() < defender_dice_rolls.size()) ? attacker_dice_rolls.size() : defender_dice_rolls.size();

                cout << "Carrying out attacks...." << endl;

            for(int i = 0; i < num_of_iterations; ++i) {
                //attacker lose an army if the value on the dice is less than or equal to value on the dice of the defender
                if(attacker_dice_rolls[i] <= defender_dice_rolls[i]) {
                    Country* attacking_country = attack_phase_->GetAttackingCountry();
                    cout << "Attacker has lost this roll. Loosing an army\n";
                    attacking_country->RemoveArmiesFromCountry(1);
                    if(attacking_country->GetNumberOfArmies() == 0) {
                        cout << "Attacking country " << *attacking_country->GetCountryName() << " has run out of armies. Attack phase has ended\n";
                        return;
                    }
                    //defender lose an army if attacker's dice has a greater value
                } else if (attacker_dice_rolls[i] > defender_dice_rolls[i]) {
                    cout << "Defender has lost this roll. Loosing an army\n";

                    Country* defending_country = attack_phase_->GetAttackingCountry();
                    Country* attacking_country = attack_phase_->GetAttackingCountry();

                    defending_country->RemoveArmiesFromCountry(1);

                    if(defending_country->GetNumberOfArmies() == 0) {
                        cout << "Defending country " << *defending_country->GetCountryName() << " has run out of armies and has been defeated\n";

                        //defender has lost. Its country will now be transferred to the attacker

                        //store the id and name of country before we transfer ownership
                        string defender_country_name = *defending_country->GetCountryName();
                        int defender_country_id = defending_country->GetCountryID();
                        AddCountryToCollection(defending_country);
                        defender->RemoveCountryFromCollection(defending_country);

                        player_strategy_->MoveArmiesAfterAttack(this, attacking_country, defending_country);
                    }
                }
            }

            cout << "result:" << endl;

            cout << *player_name_ << endl;
            DisplayCountries();


            cout << endl << *defender->GetPlayerName() << endl;
            defender->DisplayCountries();
        }
    }

    cout << *player_name_ << " no longer wishes to attack, going to next phase";
    cout << "\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void Player::Fortify() {
    if(!player_strategy_) {
        cout << "Player strategy undefined! Cannot Fortify!" << endl;
        return;
    }

    cout << "\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Beginning Fortify phase for " << *player_name_ << endl << endl;

    FortifyPhase* fortify_phase = new FortifyPhase(this);

    if (fortify_phase->PromptUserToFortify() && fortify_phase->SelectSourceCountry() && fortify_phase->SelectTargetCountry()) {
        fortify_phase->MoveArmies();
    }

    cout << "Ending Fortify phase\n" << *player_name_ << "'s turn end." << endl;

    fortify_phase = nullptr;
    delete fortify_phase;

    cout << "\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}



// ReinforcePhase class implementation ----------------------------------------------------------------------------

ReinforcePhase::ReinforcePhase() {
    turn_player_ = nullptr;
    num_of_swaps_ = 0;
    divider_ = 3;
    reinforcement_army_ = 0;
}

ReinforcePhase::ReinforcePhase(Player* turn_player, int num_of_swaps){
    turn_player_ = turn_player;
    num_of_swaps_ = num_of_swaps;
    divider_ = 3;
    reinforcement_army_ = 0;
}

ReinforcePhase::~ReinforcePhase(){
    turn_player_ = nullptr;
    delete turn_player_;

}

ReinforcePhase::ReinforcePhase(const ReinforcePhase& reinforce){
    turn_player_ = reinforce.turn_player_;
    num_of_swaps_ = reinforce.num_of_swaps_;
    divider_ = reinforce.divider_;
    reinforcement_army_ = reinforce.reinforcement_army_;
}

ReinforcePhase& ReinforcePhase::operator=(const ReinforcePhase& reinforce){
    turn_player_ = reinforce.turn_player_;
    num_of_swaps_ = reinforce.num_of_swaps_;
    divider_ = reinforce.divider_;
    reinforcement_army_ = reinforce.reinforcement_army_;
    return *this;
}

int ReinforcePhase::TotalReinforceArmy(){

  return PerCountryReinforceArmy() + PerContinentReinforceArmy() + CardSwapReinforceArmy();
}

int ReinforcePhase::PerCountryReinforceArmy(){
    if (turn_player_->GetPlayersCountries()->size() > 9) {
        int num_countries = turn_player_->GetPlayersCountries()->size();
        int rounded_down = num_countries / divider_;
        return rounded_down;
    } else {
        return 3;
    }
}

int ReinforcePhase::PerContinentReinforceArmy(){
    int armies_from_continent_bonus = 0;

    vector<Continent*>* continents = turn_player_->GetGameMap()->GetContinents();
    int num_of_continents =  continents->size();

    for(int i = 0; i < num_of_continents; ++i){

        vector<Country*>* countries = (*continents).at(i)->GetCountriesInContinent();
        int num_countries_in_continent = countries->size();

        for(int j = 0; j < num_countries_in_continent; ++j){
            int current_country_id = countries->at(j)->GetCountryID();

            //if there is a single country in the continent that the player does not own, then it does not control the continent
            if(!turn_player_->DoesPlayerOwnCountry(current_country_id)) {
                return 0;
            }
        }

        int army_value = continents->at(i)->GetContinentArmyValue();
        armies_from_continent_bonus += army_value;
    }
    return armies_from_continent_bonus;
}

int ReinforcePhase::CardSwapReinforceArmy(){
    int army_from_cards = 0;

    while(turn_player_->GetPlayersCards()->GetNumberOfCardsInHand() >= 5) {
        army_from_cards += turn_player_->GetPlayersCards()->Exchange();
    }

    if(turn_player_->GetPlayersCards()->GetNumberOfCardsInHand() < 3) {
        return army_from_cards;
    } else {
        army_from_cards += turn_player_->GetPlayersCards()->Exchange();
        return army_from_cards;
    }
}



// AttackPhase class implementation ------------------------------------------------------------------------------------

AttackPhase::AttackPhase() {
    attacking_country_ = nullptr;
    defending_country_ = nullptr;
    defender_ = nullptr;
    attacker_ = nullptr;
    game_map_ = nullptr;
    opponent_neighbours_ = new vector<Country*>;
}

AttackPhase::AttackPhase(Player* player) {
    attacking_country_ = nullptr;
    defending_country_ = nullptr;
    defender_ = nullptr;
    attacker_ = player;
    game_map_ = player->GetGameMap();
    opponent_neighbours_ = new vector<Country*>;
}

AttackPhase::~AttackPhase() {
    game_map_ = nullptr;
    delete game_map_;

    attacking_country_ = nullptr;
    delete attacking_country_;

    defending_country_ = nullptr;
    delete defending_country_;

    defender_ = nullptr;
    delete defender_;

    attacker_ = nullptr;
    delete attacker_;

    for(Country* country : *opponent_neighbours_) {
        country = nullptr;
        delete country;
    }

    opponent_neighbours_ = nullptr;
    delete [] opponent_neighbours_;
}

AttackPhase::AttackPhase(const AttackPhase& attack) {
    attacking_country_ = attack.attacking_country_;
    defending_country_ = attack.defending_country_;
    defender_ = attack.defender_;
    attacker_ = attack.attacker_;
    game_map_ = attack.game_map_;

    opponent_neighbours_ = attack.opponent_neighbours_;
    for(int i = 0; i < attack.opponent_neighbours_->size(); ++i) {
        opponent_neighbours_[i] = attack.opponent_neighbours_[i];
    }
}

AttackPhase& AttackPhase::operator=(const AttackPhase& attack) {
    attacking_country_ = attack.attacking_country_;
    defending_country_ = attack.defending_country_;
    defender_ = attack.defender_;
    attacker_ = attack.attacker_;
    game_map_ = attack.game_map_;
    opponent_neighbours_ = attack.opponent_neighbours_;
    for(int i = 0; i < attack.opponent_neighbours_->size(); ++i) {
        opponent_neighbours_[i] = attack.opponent_neighbours_[i];
    }

    return *this;
}

Country* AttackPhase::GetAttackingCountry() const {
    return attacking_country_;
}

Country* AttackPhase::GetDefendingCountry() const {
    return defending_country_;
}

vector<Country*>* AttackPhase::GetOpponentNeighbours() const {
    return opponent_neighbours_;
}

void AttackPhase::SetAttackingCountry(Country *attacking_country) {
    attacking_country_ = attacking_country;
}

void AttackPhase::SetDefender(Player* defender) {
    defender_ = defender;
}

void AttackPhase::SetDefendingCountry(Country* defending_country) {
    defending_country_ = defending_country;
}

void AttackPhase::FindOpponentNeighboursToAttackingCountry() {
    opponent_neighbours_ = nullptr;
    opponent_neighbours_= game_map_->GetNeighbouringCountriesWithArmies(attacking_country_);
    defending_country_ = nullptr;

    if(opponent_neighbours_->empty()) {
        cout << endl << *attacking_country_->GetCountryName() << " has no neighbours with armies!\n";
        defending_country_ = nullptr;
    }

    for(int i = 0; i < opponent_neighbours_->size(); ++i) {
        if(attacker_->DoesPlayerOwnCountry((*opponent_neighbours_)[i]->GetCountryID())) {
            opponent_neighbours_->erase(opponent_neighbours_->begin() + i);
        }
    }

    if(opponent_neighbours_->empty()) {
        cout << "No opposing neighbours found!\n";
    }
}

bool AttackPhase::PromptUserToAttack() {
    string answer;
    cout << "Does " << *attacker_->GetPlayerName() << " want attack an opponent's country ? (enter 'y' to attack and any other character otherwise)" << endl;
    while(!(cin >> answer)) {
        cout << "Your answer is not correct, please choose a valid answer" << endl;
        cin.clear();
        cin.ignore(132, '\n');
    }
    return answer == "y";
}

//Select which country Player would like to be the attacker
bool AttackPhase::SelectCountryToAttackFrom() {

    //check here to see if there is not a single country that can attack
    bool country_that_can_be_attacked_exists = false;
    for(Country* country : *attacker_->GetPlayersCountries()) {

        if(country->GetNumberOfArmies() > 1) {
            //Get all the neighbouring countries that have armies
            vector<Country*>* neighbouring_countries = game_map_->GetNeighbouringCountriesWithArmies(country);

            if(!neighbouring_countries->empty()) {
                //if there is a neighbour that has an army, then verify the country belongs to an opponent
                for(int i = 0; i < neighbouring_countries->size(); ++i) {
                    if(attacker_->DoesPlayerOwnCountry((*neighbouring_countries)[i]->GetCountryID())) {
                        neighbouring_countries->erase(neighbouring_countries->begin() + i);
                    }
                }
            }

            //if there is a country remaining in the vector, it means there exists at least one the attacker can attack
            if(!neighbouring_countries->empty()) {
                country_that_can_be_attacked_exists = true;
            }
        }
    }

    if(!country_that_can_be_attacked_exists) {
        cout << "No opposing neighbour exists that you can attack right now\n";
        return false;
    }

    cout << "The Countries that you own are " << endl;
    attacker_->DisplayCountries();
    attacking_country_ = nullptr;

    cout << "Please choose which country you would like to attack from (enter by numerical id):\n";

    //ask the player to select the country the wish to attack with
    attacking_country_ = attacker_->PromptPlayerToSelectCountry();

    if(attacking_country_) {
        //keep looping until select the country with 2 or more armies
        while(attacking_country_->GetNumberOfArmies() < 2) {
            cout << "You do not have enough armies in country " << *attacking_country_->GetCountryName() << ". Please Try Again." << endl;
            attacking_country_ = attacker_->PromptPlayerToSelectCountry();
        }
        return true;
    } else {
        return false;
    }
}

Country* AttackPhase::PromptPlayerToSelectDefender(vector<Country*>* neighbouring_countries) {
    //Display neighboring countries
    cout << "\n\nHere are the neighbouring opponent countries to " << *attacking_country_->GetCountryName() << endl;
    cout << endl << setw(25)  << left << "Country ID" << setw(25)  << "Name" << setw(25) <<  "Number of Armies" << setw(10) << right << endl;
    for (const Country *country : *neighbouring_countries) {
        cout << setw(25)  << left << country->GetCountryID() << setw(25) <<  *country->GetCountryName() << setw(25) << country->GetNumberOfArmies()  << setw(10) << right << game_map_->GenerateListOfNeighboringCountries(attacking_country_) << endl;
        cout << endl;
    }

    cout << "Please choose which country you would like to attack (enter by numerical id):\n";
    int defender_id = -1;
    Country* defender = nullptr;
    while(!(cin >> defender_id) || defender_id < 1 || !(defender = attacker_->GetCountryInVectorById(neighbouring_countries, defender_id)) || attacker_->Find(defender) != -1) {
        cin.clear();
        cin.ignore(132, '\n');
        cout << "Invalid entry entered! Please try again: ";
    }

    return defender;
}

//Prompt user for which country they would like to attack
bool AttackPhase::SelectCountryToAttack() {
    vector<Country*>* neighbouring_countries = game_map_->GetNeighbouringCountriesWithArmies(attacking_country_);
    defending_country_ = nullptr;

    if(neighbouring_countries->empty()) {
        cout << endl << *attacking_country_->GetCountryName() << " has no neighbours with armies!\n";
        defending_country_ = nullptr;
        return false;
    }

    for(int i = 0; i < neighbouring_countries->size(); ++i) {
        if(attacker_->DoesPlayerOwnCountry((*neighbouring_countries)[i]->GetCountryID())) {
            neighbouring_countries->erase(neighbouring_countries->begin() + i);
        }
    }

    if(neighbouring_countries->empty()) {
        cout << "No opposing neighbours found!\n";
        return false;
    }

    //prompt player to select country to attack from list of neighbours
    while(!defending_country_ ) {
        defending_country_ = PromptPlayerToSelectDefender(neighbouring_countries);
    }

    defender_ = defending_country_->GetCountryOwner();

    return !!defender_;
}

void AttackPhase::PerformDiceRoll() {
    //determine maximum number of rolls for each player based on rules of Risk
    const int MAX_NUM_OF_DICE_ATTACKER = (attacking_country_->GetNumberOfArmies() - 1) < 3 ? attacking_country_ ->GetNumberOfArmies() : 3;
    const int MAX_NUM_OF_DICE_DEFENDER = (defending_country_->GetNumberOfArmies()) < 2 ? defending_country_ ->GetNumberOfArmies() : 2;

    //prompt each player to enter the num of dice they wish to roll
    cout << "\nIt is " << *attacker_->GetPlayerName() << "'s turn to enter the number of dice they wish to roll (can roll max " << MAX_NUM_OF_DICE_ATTACKER << ") dice: ";
    int attacker_num_dice;
    while( !(cin >> attacker_num_dice) || attacker_num_dice < 1 || attacker_num_dice > MAX_NUM_OF_DICE_ATTACKER) {
        cout << "\nYou have entered an invalid number of dice to roll. Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    cout << "\nIt is " << *defender_->GetPlayerName() << "'s turn to enter the number of dice they wish to roll (can roll max " << MAX_NUM_OF_DICE_DEFENDER << ") dice: ";
    int defender_num_dice;
    while( !(cin >> defender_num_dice) || defender_num_dice < 1 || defender_num_dice > MAX_NUM_OF_DICE_DEFENDER) {
        cout << "You have entered an invalid number of dice to roll. Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    vector<int> attacker_dice_rolls = attacker_->GetPlayerDice()->Roll(attacker_num_dice);
    cout << "Attacker dice rolled:\n";
    for(int i : attacker_dice_rolls) {
        cout << i << endl;
    }
    vector<int> defender_dice_rolls = defender_->GetPlayerDice()->Roll(defender_num_dice);
    cout << "Defender dice rolled:\n";
    for(int i : defender_dice_rolls) {
        cout << i << endl;
    }
    cout << endl;

    //sort the rolls from highest value to lowest value
    sort(attacker_dice_rolls.begin(), attacker_dice_rolls.end());
    reverse(attacker_dice_rolls.begin(), attacker_dice_rolls.end());
    sort(defender_dice_rolls.begin(), defender_dice_rolls.end());
    reverse(defender_dice_rolls.begin(), defender_dice_rolls.end());

    int num_of_iterations = (attacker_dice_rolls.size() == defender_dice_rolls.size() || attacker_dice_rolls.size() < defender_dice_rolls.size()) ? attacker_dice_rolls.size() : defender_dice_rolls.size();

    cout << "Carrying out attacks...." << endl;

    for(int i = 0; i < num_of_iterations; ++i) {
        //attacker lose an army if the value on the dice is less than or equal to value on the dice of the defender
        if(attacker_dice_rolls[i] <= defender_dice_rolls[i]) {

            cout << "Attacker has lost this roll. Loosing an army\n";
            attacking_country_->RemoveArmiesFromCountry(1);
            if(attacking_country_->GetNumberOfArmies() == 0) {
                cout << "Attacking country " << *attacking_country_->GetCountryName() << " has run out of armies. Attack phase has ended\n";
                return;
            }
        //defender lose an army if attacker's dice has a greater value
        } else if (attacker_dice_rolls[i] > defender_dice_rolls[i]) {
            cout << "Defender has lost this roll. Loosing an army\n";
            defending_country_->RemoveArmiesFromCountry(1);

            if(defending_country_->GetNumberOfArmies() == 0) {
                cout << "Defending country " << *defending_country_->GetCountryName() << " has run out of armies and has been defeated\n";

                //defender has lost. Its country will now be transferred to the attacker

                //store the id and name of country before we transfer ownership
                string defender_country_name = *defending_country_->GetCountryName();
                int defender_country_id = defending_country_->GetCountryID();
                attacker_->AddCountryToCollection(defending_country_);
                defender_->RemoveCountryFromCollection(defending_country_);

                //prompt attacker if they would like to assign armies from their newly acquired country to their other countries
                cout << *attacker_->GetPlayerName() << " would you like to move armies from " << *attacking_country_->GetCountryName() << " to " << defender_country_name << "? (enter 'y' if so and any other character otherwise\n";


                string user_response;

                while(!(cin >> user_response)) {
                    cout << "\nInvalid input given! Please try again: ";
                    cin.clear();
                    cin.ignore(132, '\n');
                }

                if(user_response == "y") {
                    cout << "How many armies would you like to assign to " << defender_country_name << " from " << *attacking_country_->GetCountryName() << "? (you can assign a max of " << attacking_country_->GetNumberOfArmies() << "): ";
                    int num_armies_to_assign;

                    while(!(cin >> num_armies_to_assign) || num_armies_to_assign < 1 || num_armies_to_assign > attacking_country_->GetNumberOfArmies()) {
                        cout << "\nInvalid input given! Please try again: ";
                        cin.clear();
                        cin.ignore(132, '\n');
                    }

                    Country* newly_acquired_country = attacker_->GetCountryById(defender_country_id);

                    if(newly_acquired_country) {
                        newly_acquired_country->SetNumberOfArmies(num_armies_to_assign);
                        attacking_country_->RemoveArmiesFromCountry(num_armies_to_assign);
                    }

                } else {
                    return;
                }

            }
        }
    }

    cout << "result:" << endl;

    cout << *attacker_->GetPlayerName() << endl;
    attacker_->DisplayCountries();

    cout << endl << *defender_->GetPlayerName() << endl;
    defender_->DisplayCountries();
}



// FortifyPhase class implementation -----------------------------------------------------------------------------------

FortifyPhase::FortifyPhase() {
    player_= nullptr;
    game_map_ = nullptr;
    source_country_ = nullptr;
    target_country_ = nullptr;
}

FortifyPhase::FortifyPhase(Player* player) {
    player_= player;
    game_map_ = player->GetGameMap();
    source_country_ = nullptr;
    target_country_ = nullptr;
}

FortifyPhase::FortifyPhase(const FortifyPhase& fortify) {
    player_ = fortify.player_;
    game_map_ = fortify.game_map_;
    source_country_ = fortify.source_country_;
    target_country_ = fortify.target_country_;
}

FortifyPhase::~FortifyPhase() {
    player_ = nullptr;
    game_map_ = nullptr;
    source_country_ = nullptr;
    target_country_ = nullptr;

    delete player_;
    delete game_map_;
    delete source_country_;
    delete target_country_;
}

FortifyPhase& FortifyPhase::operator=(const FortifyPhase &fortify) {
    player_ = fortify.player_;
    game_map_ = fortify.game_map_;
    source_country_ = fortify.source_country_;
    target_country_ = fortify.target_country_;
    return *this;
}

bool FortifyPhase::PromptUserToFortify() {
    string answer;
    cout << "Does " << *player_->GetPlayerName() << " wish to fortify a country? (Enter y, any other char otherwise):" << endl;
    while(!(cin >> answer)) {
        cout << "Your answer is not correct, please choose a valid answer" << endl;
        cin.clear();
        cin.ignore(132, '\n');
    }
    return answer == "y";
}

bool FortifyPhase::SelectSourceCountry() {
    player_->DisplayCountries();
    cout << "Please choose your source country \n";

    vector<Country*> neighbouring_countries;

    int count = 0;
    for(Country* country : *player_->GetPlayersCountries()) {
        if(country->GetNumberOfArmies() < 1) {
            ++count;
        }
    }

    if(count == player_->GetPlayersCountries()->size()) {
        cout << "No countries with enough armies to assign to another country!\n";
        return false;
    }

    Country* selected_country = player_->PromptPlayerToSelectCountry();

    while(!selected_country || (selected_country && selected_country->GetNumberOfArmies() < 1) ) {
        cout << "You do not have enough armies in selected country. Please Try Again." << endl;
        selected_country = player_->PromptPlayerToSelectCountry();
    }

    source_country_ = selected_country;
    return source_country_ != nullptr;
}

bool FortifyPhase::SelectTargetCountry() {
    cout << "Please select which target country you wish to fortify:\n";

    if(!source_country_) {
        cout << "No source country seleted!\n";
        return false;
    }

    vector<Country*>* neighbours = game_map_->GetNeighbouringCountries(source_country_);

    if(!neighbours || neighbours->empty()) {
        cout << *source_country_->GetCountryName() << " has no neighbours!\n";
        return false;
    }

    vector<Country*> neighbouring_countries;

    for(Country* country : *neighbours) {
        if(player_->DoesPlayerOwnCountry(country->GetCountryID())) {
            neighbouring_countries.push_back(country);
        }
    }

    if(neighbouring_countries.empty()) {
        cout << *source_country_->GetCountryName() << " has no neighbours to assign armies to!\n";
        return false;
    }

    //prompt player to select country to attack from list of neighbours
    //Display neighboring countries
    cout << "\nHere are the neighbouring countries to " << *source_country_->GetCountryName() << endl << endl;
    cout << endl << setw(25)  << left << "Country ID" << setw(25)  << "Name" << setw(25) << right <<  "Number of Armies" << endl;
    for (const Country *country : neighbouring_countries) {
        cout << setw(25)  << left << country->GetCountryID() << setw(25) <<  *country->GetCountryName() << setw(25) << right  << country->GetNumberOfArmies() << endl;
        cout << endl;
    }

    cout << "Please choose which country you would like to fortify (enter by numerical id):\n";
    int fortify_id;


    //USE FORTIFY STRATEGY HERE
    while(!(cin >> fortify_id) || fortify_id < 1 || !(target_country_ = player_->GetCountryInVectorById(&neighbouring_countries, fortify_id) )) {
        cout << "Invalid entry entered! Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    return true;
}

void FortifyPhase::MoveArmies() {
    cout << "There are " << source_country_->GetNumberOfArmies() << " armies in " << *source_country_->GetCountryName() << "." << endl;
    cout << "There are " << target_country_->GetNumberOfArmies() << " armies in " << *target_country_->GetCountryName() << "." << endl;


    //USE FORTIFY STRATEGY HERE
    int num_of_armies;
    cout << "How many armies do you wish to move.(Enter a number):" << endl;

    while (!(cin >> num_of_armies) || num_of_armies < 1 || num_of_armies > source_country_->GetNumberOfArmies()) {
        cout << "Invalid number of armies selected! Please try again\n";
        cin.clear();
        cin.ignore(132, '\n');
    }
    //

    cout << "Fortifying " << *target_country_->GetCountryName() << " with " << num_of_armies << " armies." << endl;

    source_country_->RemoveArmiesFromCountry(num_of_armies);
    target_country_->SetNumberOfArmies(target_country_->GetNumberOfArmies() + num_of_armies);

    cout << "\nHere is the result after fortification: " << endl;

    cout << "There are " << source_country_->GetNumberOfArmies() << " armies in " << *source_country_->GetCountryName() << "." << endl;
    cout << "There are " << target_country_->GetNumberOfArmies() << " armies in " << *target_country_->GetCountryName() << "." << endl;
}
