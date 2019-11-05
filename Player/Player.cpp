/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <vector>
#include <iostream>
#include <cmath>
#include <utility>
#include <string>
#include <map>
#include <iterator>
#include <filesystem>

using namespace std;

#include "Player.h"

Player::Player(string player_name) {
    player_name_ = new string(player_name);
    is_player_turn_ = false;
    countries_ = new vector<Country*>;
    risk_cards_ = nullptr;
    dice_roll_ = nullptr;
    game_map_ = nullptr;
}

Player::Player(string player_name, Map *game_map) {
    player_name_ = new string(player_name);
    game_map_ = game_map;
    is_player_turn_ = false;
    countries_ = new vector<Country*>;
    risk_cards_ = nullptr;
    dice_roll_ = nullptr;
}

Player::Player(string player_name, vector<Country*>* countries_to_assign_to_player, bool is_player_turn) {
    player_name_ = new string(player_name);
    is_player_turn_ = is_player_turn;
    //countries to be assigned to each player are chosen randomly at start-up phase
    countries_ = countries_to_assign_to_player;
    risk_cards_ = nullptr;
    dice_roll_ = nullptr;
    game_map_ = nullptr;
}

Player::Player(const Player &player) {
    player_name_ = player.player_name_;
    is_player_turn_ = player.is_player_turn_;

    for(size_t i = 0; i < player.countries_->size(); ++i) {
        countries_[i] = player.countries_[i];
    }
    countries_ = player.countries_;
    risk_cards_ = player.risk_cards_;
    dice_roll_ = player.dice_roll_;
    game_map_ = player.game_map_;
}

Player::~Player() {

    for(Country* country : *countries_) {
        delete country;
    }

    delete risk_cards_;
    delete countries_;
    delete dice_roll_;
    delete game_map_;
}

Player& Player::operator=(const Player &player) {
    player_name_ = player.player_name_;
    is_player_turn_ = player.is_player_turn_;


    for(size_t i = 0; i < player.countries_->size(); ++i) {
        countries_[i] = player.countries_[i];
    }

    risk_cards_ = player.risk_cards_;
    countries_ = player.countries_;
    dice_roll_ = player.dice_roll_;
    game_map_ = player.game_map_;
    return *this;
}

bool Player::operator==(const Player& player) {
    return player_name_ == player.player_name_
            && is_player_turn_ == player.is_player_turn_
            && countries_ == player.countries_
            && risk_cards_ == player.risk_cards_
            && dice_roll_ == player.dice_roll_
            && game_map_ == player.game_map_;
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

void Player::SetGameMap(Map* map) {
    game_map_ = map;
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

Dice* Player::GetPlayerDice() const {
    return dice_roll_;
}

string* Player::GetPlayerName() const {
    return player_name_;
}

vector<Country*>* Player::GetPlayersCountries() const {
    return countries_;
}

Hand* Player::GetPlayersCards() const {
    return risk_cards_;
}

Map* Player::GetGameMap() const {
    return game_map_;
}

int Player::Find(Country* country) const {
    for(int i = 0; i < countries_->size(); ++i) {
        if((*countries_)[i] == country) {
            return i;
        }
    }
    return -1;
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
//    debug string:
//    cout << endl;
//    for(const Country* country : *countries_) {
//        cout << *country->GetCountryName() << endl;
//    }
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
    cout << "In reinforce method" << endl;

    Reinforcement* reinforce = new Reinforcement(this, 0);
    int bonus_army = reinforce->TotalReinforceArmy();
    int looping_counter = 0;
    int reinforce_value = 0;
    while(bonus_army > 0){
        cout<<"Currently on Country "<<endl;
        countries_->at(looping_counter)->DisplayInfo();
        while(true){

            cout<<"Armies to assign: "<<bonus_army<<"\nArmies to add to current country: ";
            cin >> reinforce_value;
            while (cin.fail() || reinforce_value > bonus_army || reinforce_value < 0) {
                cout<<"Invalid input. Pick a valid number: ";
                cin.clear();
                cin.ignore(256, '\n');
                cin >> reinforce_value;
            }
            break;
        }

        cout<<reinforce_value<<" armies added to current country"<<endl;

        countries_->at(looping_counter)->SetNumberOfArmies(countries_->at(looping_counter)->GetNumberOfArmies() + reinforce_value);
        bonus_army -= reinforce_value;
        looping_counter +=1;
        looping_counter = looping_counter % countries_->size();
    }
}


void Player::Attack() {

    cout << "\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Beginning Attack phase for " << *player_name_ << endl << endl;

    AttackPhase* attack_phase = new AttackPhase(this);

    //ask player if they wish to carry-out an attack
    while (attack_phase->PromptUserToAttack()) {
        attack_phase->SelectCountryToAttackFrom();
        bool can_attack = attack_phase->SelectCountryToAttack();

        if(can_attack){
            attack_phase->PerformDiceRoll();
        } else {
            cout << *player_name_ << " cannot attack since no neighbouring countries have armies!\n";
            return;
        }
    }

    cout << *player_name_ << "no longer wishes to attack, going to next phase";

    attack_phase = nullptr;
    delete attack_phase;

    cout << "\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void Player::Fortify() {

    cout << "\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Beginning Fortify phase for " << *player_name_ << endl << endl;

    FortifyPhase* fortify_phase = new FortifyPhase(this);

    if (fortify_phase->PromptUserToFortify()) {
        fortify_phase->SelectSourceCountry();
        fortify_phase->SelectTargetCountry();
        fortify_phase->MoveArmies();
    }

    cout << "Ending Fortify phase\n" << *player_name_ << "'s turn end." << endl;

    fortify_phase = nullptr;
    delete fortify_phase;

    cout << "\n\n-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
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



// Reinforcement phase class implementation ----------------------------------------------------------------------------

Reinforcement::Reinforcement() {
    turn_player_ = nullptr;
    num_of_swaps_ = 0;
    divider_ = 3;
    reinforcement_army_ = 0;
}

Reinforcement::Reinforcement(Player* turn_player, int num_of_swaps){
    turn_player_ = turn_player;
    num_of_swaps_ = num_of_swaps;
    divider_ = 3;
    reinforcement_army_ = 0;
}

Reinforcement::~Reinforcement(){
    turn_player_ = nullptr;
    delete turn_player_;

}

Reinforcement::Reinforcement(const Reinforcement& reinforce){
    turn_player_ = reinforce.turn_player_;
    num_of_swaps_ = reinforce.num_of_swaps_;
    divider_ = reinforce.divider_;
    reinforcement_army_ = reinforce.reinforcement_army_;
}

Reinforcement& Reinforcement::operator=(const Reinforcement& reinforce){
    turn_player_ = reinforce.turn_player_;
    num_of_swaps_ = reinforce.num_of_swaps_;
    divider_ = reinforce.divider_;
    reinforcement_army_ = reinforce.reinforcement_army_;
    return *this;
}

int Reinforcement::TotalReinforceArmy(){

  return PerCountryReinforceArmy() + PerContinentReinforceArmy() + CardSwapReinforceArmy();
}

int Reinforcement::PerCountryReinforceArmy(){
    if (turn_player_->GetPlayersCountries()->size()>9)
        return ((int)floor(turn_player_->GetPlayersCountries()->size() / divider_));
    return 3;
}

int Reinforcement::PerContinentReinforceArmy(){
    int armies_from_continent_bonus = 0;
    for(int i = 0; i<turn_player_->GetGameMap()->GetContinents()->size();i++){
        for(int j = 0; i<turn_player_->GetGameMap()->GetContinents()->at(i)->GetCountriesInContinent()->size();i++){
            if(!turn_player_->DoesPlayerOwnCountry(turn_player_->GetGameMap()->GetContinents()->at(i)->GetCountriesInContinent()->at(j)->GetCountryID()))
                return 0;
        }
        armies_from_continent_bonus += turn_player_->GetGameMap()->GetContinents()->at(i)->GetContinentArmyValue();
    }
    return armies_from_continent_bonus;
}

int Reinforcement::CardSwapReinforceArmy(){
    int army_from_cards = 0;
    while(turn_player_->GetPlayersCards()->GetNumberOfCardsInHand() >= 5)
        army_from_cards =+ turn_player_->GetPlayersCards()->Exchange();
    if(turn_player_->GetPlayersCards()->GetNumberOfCardsInHand() <3)
        return army_from_cards;
    army_from_cards =+ turn_player_->GetPlayersCards()->Exchange();
    return army_from_cards;
}

// AttackPhase class implementation ------------------------------------------------------------------------------------

AttackPhase::AttackPhase() {
    attacking_country_ = nullptr;
    defending_country_ = nullptr;
    defender_ = nullptr;
    attacker_ = nullptr;
    game_map_ = nullptr;
}

AttackPhase::AttackPhase(Player* player) {
    attacking_country_ = nullptr;
    defending_country_ = nullptr;
    defender_ = nullptr;
    attacker_ = player;
    game_map_ = player->GetGameMap();
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
}

AttackPhase::AttackPhase(const AttackPhase& attack) {
    attacking_country_ = attack.attacking_country_;
    defending_country_ = attack.defending_country_;
    defender_ = attack.defender_;
    attacker_ = attack.attacker_;
    game_map_ = attack.game_map_;
}

AttackPhase& AttackPhase::operator=(const AttackPhase& attack) {
    attacking_country_ = attack.attacking_country_;
    defending_country_ = attack.defending_country_;
    defender_ = attack.defender_;
    attacker_ = attack.attacker_;
    game_map_ = attack.game_map_;
    return *this;
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
void AttackPhase::SelectCountryToAttackFrom() {

    cout << "The Countries that you own are " << endl;
    attacker_->DisplayCountries();

    cout << "Please choose which country you would like to attack from (enter by numerical id):\n";
    //ask the player to select the country the wish to attack with
    attacking_country_ = attacker_->PromptPlayerToSelectCountry();

    if(attacking_country_) {
        while(attacking_country_->GetNumberOfArmies() < 2) {
            cout << "You do not have enough armies in country " << *attacking_country_->GetCountryName() << ". Please Try Again." << endl;
            attacking_country_ = attacker_->PromptPlayerToSelectCountry();
        }
    }
}

Country* AttackPhase::PromptPlayerToSelectDefender(vector<Country*>* neighbouring_countries) {
    //Display neighboring countries
    cout << "\n\nHere are the neighbouring opponent countries to " << *attacking_country_->GetCountryName() << endl;
    cout << endl << setw(25)  << left << "Country ID" << setw(25)  << "Name" << setw(25) << right <<  "Number of Armies" << endl;
    for (const Country *country : *neighbouring_countries) {
        cout << setw(25)  << left << country->GetCountryID() << setw(25) <<  *country->GetCountryName() << setw(25) << right  << country->GetNumberOfArmies() << endl;
        cout << endl;
    }

    cout << "Please choose which country you would like to attack (enter by numerical id):\n";
    int defender_id = -1;
    Country* defender = nullptr;
    while(!(cin >> defender_id) || defender_id < 1 || !(defender = attacker_->GetCountryInVectorById(neighbouring_countries, defender_id))) {
        cin.clear();
        cin.ignore(132, '\n');
        cout << "Invalid entry entered! Please try again: ";
    }
    return defender;
}

//Prompt user for which country they would like to attack
bool AttackPhase::SelectCountryToAttack() {
    vector<Country*>* neighbouring_countries = game_map_->GetNeighbouringCountriesWithArmies(attacking_country_);

    if(neighbouring_countries->empty()) {
        cout << endl << *attacking_country_->GetCountryName() << " has no neighbours with armies!\n";
        defending_country_ = nullptr;
        return false;
    }

    //prompt player to select country to attack from list of neighbours
    while(!defending_country_) {
        defending_country_ = PromptPlayerToSelectDefender(neighbouring_countries);
    }

    return true;
}

void AttackPhase::PerformDiceRoll() {
    //determine maximum number of rolls for each player based on rules of Risk
    const int MAX_NUM_OF_DICE_ATTACKER = (attacking_country_->GetNumberOfArmies() - 1) < 3 ? attacking_country_ ->GetNumberOfArmies() : 3;
    const int MAX_NUM_OF_DICE_DEFENDER = (defending_country_->GetNumberOfArmies()) < 2 ? defending_country_ ->GetNumberOfArmies() : 2;

    //prompt each player to enter the num of dice they wish to roll
    cout << "\nIt is " << *attacker_->GetPlayerName() << "'s turn to enter the number of dice they wish to roll (can roll max " << MAX_NUM_OF_DICE_ATTACKER << " dice: ";
    int attacker_num_dice;
    while( !(cin >> attacker_num_dice) || attacker_num_dice < 1 || attacker_num_dice > MAX_NUM_OF_DICE_ATTACKER) {
        cout << "\nYou have entered an invalid number of dice to roll. Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    cout << "\nIt is " << *defender_->GetPlayerName() << "'s turn to enter the number of dice they wish to roll (can roll max " << MAX_NUM_OF_DICE_DEFENDER << " dice: ";
    int defender_num_dice;
    while( !(cin >> defender_num_dice) || defender_num_dice < 1 || defender_num_dice > MAX_NUM_OF_DICE_DEFENDER) {
        cout << "You have entered an invalid number of dice to roll. Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }

    vector<int> attacker_dice_rolls = attacker_->GetPlayerDice()->Roll(attacker_num_dice);
    cout << "Attacker dice rolled:\n";
    vector<int> defender_dice_rolls = defender_->GetPlayerDice()->Roll(defender_num_dice);
    cout << "Defender dice rolled:\n";

    //sort the rolls from highest value to lowest value
    sort(attacker_dice_rolls.begin(), attacker_dice_rolls.end());
    reverse(attacker_dice_rolls.begin(), attacker_dice_rolls.end());
    sort(defender_dice_rolls.begin(), defender_dice_rolls.end());
    reverse(defender_dice_rolls.begin(), defender_dice_rolls.end());

    int num_of_iterations = (attacker_dice_rolls.size() == defender_dice_rolls.size() || attacker_dice_rolls.size() < defender_dice_rolls.size()) ? attacker_dice_rolls.size() : defender_dice_rolls.size();

    for(int i = 0; i < num_of_iterations; ++i) {
        //attacker lose an army if the value on the dice is less than or equal to value on the dice of the defender
        if(attacker_dice_rolls[i] <= defender_dice_rolls[i]) {

            attacking_country_->RemoveArmiesFromCountry(1);
            //TODO: not sure what the intended behaviour is when the attacker runs out armies. Needs to be clarified
            if(attacking_country_->GetNumberOfArmies() == 0) {
                cout << "Attacking country " << *attacking_country_->GetCountryName() << " has run out of armies. Attack phase has ended\n";
            }
        //defender lose an army if attacker's dice has a greater value
        } else if (attacker_dice_rolls[i] > defender_dice_rolls[i]) {

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

void FortifyPhase::SelectSourceCountry() {
    player_->DisplayCountries();
    cout << "Please choose your source country \n";
    Country* selected_country = player_->PromptPlayerToSelectCountry();

    if(selected_country) {
        while(selected_country->GetNumberOfArmies() < 1) {
            cout << "You do not have enough armies in country " << *selected_country->GetCountryName() << ". Please Try Again." << endl;
            selected_country = player_->PromptPlayerToSelectCountry();
        }
        source_country_ = selected_country;
    }
}

void FortifyPhase::SelectTargetCountry() {
    player_->DisplayCountries();
    cout << "Please your target country you wish to fortify:\n";

    vector<Country*>* neighbouring_countries = game_map_->GetNeighbouringCountries(source_country_);

    if(neighbouring_countries->empty()) {
        cout << *source_country_->GetCountryName() << " has no neighbours with armies!\n";
    }

    //prompt player to select country to attack from list of neighbours
    //Display neighboring countries
    cout << "\nHere are the neighbouring countries to " << *source_country_->GetCountryName() << endl << endl;
    cout << endl << setw(25)  << left << "Country ID" << setw(25)  << "Name" << setw(25) << right <<  "Number of Armies" << endl;
    for (const Country *country : *neighbouring_countries) {
        cout << setw(25)  << left << country->GetCountryID() << setw(25) <<  *country->GetCountryName() << setw(25) << right  << country->GetNumberOfArmies() << endl;
        cout << endl;
    }

    cout << "Please choose which country you would like to fortify (enter by numerical id):\n";
    int fortify_id;

    while(!(cin >> fortify_id) || fortify_id < 1 || !(target_country_ = player_->GetCountryInVectorById(neighbouring_countries, fortify_id) )) {
        cout << "Invalid entry entered! Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }
}

void FortifyPhase::MoveArmies() {
    cout << "There are " << source_country_->GetNumberOfArmies() << " armies in " << *source_country_->GetCountryName() << "." << endl;
    cout << "There are " << target_country_->GetNumberOfArmies() << " armies in " << *target_country_->GetCountryName() << "." << endl;

    int num_of_armies;
    cout << "How many armies do you wish to move.(Enter a number):" << endl;

    while (!(cin >> num_of_armies) || num_of_armies < 1 || num_of_armies > source_country_->GetNumberOfArmies()) {
        cout << "Invalid number of armies selected! Please try again\n";
        cin.clear();
        cin.ignore(132, '\n');
    }

    cout << "Fortifying " << *target_country_->GetCountryName() << " with " << num_of_armies << " armies." << endl;

    source_country_->RemoveArmiesFromCountry(num_of_armies);
    target_country_->SetNumberOfArmies(target_country_->GetNumberOfArmies() + num_of_armies);

    cout << "\nHere is the result after fortification: " << endl;

    cout << "There are " << source_country_->GetNumberOfArmies() << " armies in " << *source_country_->GetCountryName() << "." << endl;
    cout << "There are " << target_country_->GetNumberOfArmies() << " armies in " << *target_country_->GetCountryName() << "." << endl;
}
