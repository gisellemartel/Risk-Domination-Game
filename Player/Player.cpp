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
#include <random>

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
    cout << endl << setw(25)  << left << "Country ID" << setw(25)  << "Name" << setw(25) << right <<  "Number of Armies" << endl;
    for (const Country *country : *countries_) {
        cout << setw(25)  << left << country->GetCountryID() << setw(25) <<  *country->GetCountryName() << setw(25) << right  << country->GetNumberOfArmies() << endl;
        cout << endl;
    }
}

void Player::Reinforce() {
    cout << "In reinforce method" << endl;

    //the number of armies the player is assigned at their current turn is the number of countries
    //they own divided by 3 rounded down
//    int num_of_armies_to_assign = (int)floor((float)(countries_->size() / 3));

    //TODO implementation of the rules below
    /**
     * If the player owns all the countries of entire continent,
     * then the player is given # of armies corresponding to the continents control value
     *
     * If the player owns 3 cards of different sorts or same sorts, he can exchange them for armies
     *
     * The # armies a player will get for 3 cards is first 5,
     * and then increases by 5 every time player trades 3 cards (5, 10, 15, 20, …)
     *
     * Minimal number reinforcement armies is 3
     *
     * Once total number or reinforcements is determined for the players turn,
     * the player may place the armies on any country he owns, divided as he wants amongst his countries

     */

}

void Player::Attack() {
    cout << "In attack method" << endl;

    AttackPhase* attack_phase = new AttackPhase(this);

    //ask player if they wish to carry-out an attack
    if (attack_phase->PromptUserToAttack()) {
        //prompt player to select a country they wish to attack with
        attack_phase->SetAttackingCountry(attack_phase->SelectCountryToAttackFrom());
        if (attack_phase->GetAttackingCountry()) {
            cout << "You have chosen to attack with " << *attack_phase->GetAttackingCountry()->GetCountryName() << endl;
            attack_phase->SetDefendingCountry(attack_phase->SelectCountryToAttack());
            if (!attack_phase->GetDefendingCountry()) {
                cout << "Cannot proceed attack, invalid country selected to attack!";
                return;
            }

            cout << "You have chosen to attack " << *attack_phase->GetDefendingCountry()->GetCountryName() << endl;
        } else {
            cout << "Cannot proceed attack, invalid country selected to attack from!";
            return;
        }
    } else {
        cout << "You do not wish to attack, aborting";
        return;
    }

    //roll the dice once countries are selected for Attack
    attack_phase->PerformDiceRoll();

    //recursively call function until player indicates they no longer want to play
    Attack();
}

void Player::Fortify() {

}

Reinforcement::Reinforcement() {

}

Reinforcement::Reinforcement(Cards* player_cards, int num_of_swaps){
    Cards* player_cards_ = player_cards;
    num_of_swaps_ = num_of_swaps;
    divider = 3;
    reinforcement_army = 0;
}

Reinforcement::~Reinforcement(){

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

void AttackPhase::SetAttackingCountry(Country *country) {
    attacking_country_ = country;
}

void AttackPhase::SetDefendingCountry(Country *country) {
    defending_country_ = country;
}

Country* AttackPhase::GetAttackingCountry() const {
    return attacking_country_;
}

Country* AttackPhase::GetDefendingCountry() const {
    return defending_country_;
}

bool AttackPhase::PromptUserToAttack() {
    string answer;
    cout << "Does " << *attacker_->GetPlayerName() << " want attack an opponent's country ? (enter 'y' to attack and any other character otherwise)" << endl;
    while(!(cin >> answer)) {
        cout << "Your answer is not correct, please choose a valid answer" << endl;
        cin.clear();
        cin.ignore(132, '\n');
    }
    return answer == "y" ? true : false;
}

Country* AttackPhase::PromptPlayerToSelectAttacker() {
    cout << "Please choose which country you would like to attack from (enter by numerical id):\n";
    int attacker_id;
    while(!(cin >> attacker_id) || attacker_id < 1 || !attacker_->DoesPlayerOwnCountry(attacker_id) ) {
        cin.clear();
        cin.ignore(132, '\n');
        cout << "Invalid entry entered! Please try again: ";
    }

    return attacker_->GetCountryById(attacker_id);
}

//Select which country Player would like to be the attacker
Country* AttackPhase::SelectCountryToAttackFrom() {

    cout << "The Countries that you own are " << endl;
    attacker_->DisplayCountries();

    //ask the player to select the country the wish to attack with
    Country* current_country = PromptPlayerToSelectAttacker();

    if(current_country) {
        while(current_country->GetNumberOfArmies() < 2) {
            cout << "You do not have enough armies in country " << *current_country->GetCountryName() << ". Please Try Again." << endl;
            current_country = PromptPlayerToSelectAttacker();
        }
        return current_country;
    }

    return nullptr;
}

Country* AttackPhase::PromptPlayerToSelectDefender(vector<Country*>* neighbouring_countries) {
    //Display neighboring countries
    cout << "\nHere are the neighbouring countries to " << *attacking_country_->GetCountryName() << endl << endl;
    cout << endl << setw(25)  << left << "Country ID" << setw(25)  << "Name" << setw(25) << right <<  "Number of Armies" << endl;
    for (const Country *country : *neighbouring_countries) {
        cout << setw(25)  << left << country->GetCountryID() << setw(25) <<  *country->GetCountryName() << setw(25) << right  << country->GetNumberOfArmies() << endl;
        cout << endl;
    }

    cout << "Please choose which country you would like to attack (enter by numerical id):\n";
    int defender_id;
    while(!(cin >> defender_id) || defender_id < 1 || defender_id >= neighbouring_countries->size()) {
        cin.clear();
        cin.ignore(132, '\n');
        cout << "Invalid entry entered! Please try again: ";
    }

    //debug string
    game_map_->DisplayAdjacencyMatrix();
    return (*neighbouring_countries)[defender_id];
}

//Prompt user for which country they would like to attack
Country *AttackPhase::SelectCountryToAttack() {
    vector<Country*>* neighbouring_countries = game_map_->GetNeighbouringCountriesWithArmies(attacking_country_);

    if(neighbouring_countries->empty()) {
        cout << *attacking_country_->GetCountryName() << " has no neighbours with armies!\n";
        return nullptr;
    }

    //prompt player to select country to attack from list of neighbours
    defending_country_ = PromptPlayerToSelectDefender(neighbouring_countries);
    return defending_country_;
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
    }

    cout << "\nIt is " << *defender_->GetPlayerName() << "'s turn to enter the number of dice they wish to roll (can roll max " << MAX_NUM_OF_DICE_DEFENDER << " dice: ";
    int defender_num_dice;
    while( !(cin >> defender_num_dice) || defender_num_dice < 1 || defender_num_dice > MAX_NUM_OF_DICE_DEFENDER) {
        cout << "You have entered an invalid number of dice to roll. Please try again: ";
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
    attacker_= nullptr;
    defender_ = nullptr;
    game_map_ = nullptr;
    attacking_country_ = nullptr;
    defending_country_ = nullptr;
}

FortifyPhase::FortifyPhase(Player *player) {
    attacker_= player;
    defender_ = nullptr;
    game_map_ = nullptr;
    attacking_country_ = nullptr;
    defending_country_ = nullptr;
}

FortifyPhase::FortifyPhase(const FortifyPhase& fortify) {
    attacker_ = fortify.attacker_;
    defender_ = fortify.defender_;
    game_map_ = fortify.game_map_;
    attacking_country_ = fortify.attacking_country_;
    defending_country_ = fortify.defending_country_;
}

FortifyPhase::~FortifyPhase() {
    attacker_ = nullptr;
    defender_ = nullptr;
    game_map_ = nullptr;
    attacking_country_ = nullptr;
    defending_country_ = nullptr;
    delete attacker_;
    delete defender_;
    delete game_map_;
    delete attacking_country_;
    delete defending_country_;
}

FortifyPhase& FortifyPhase::operator=(const FortifyPhase &fortify) {
    attacker_ = fortify.attacker_;
    defender_ = fortify.defender_;
    game_map_ = fortify.game_map_;
    attacking_country_ = fortify.attacking_country_;
    defending_country_ = fortify.defending_country_;
    return *this;
}

void FortifyPhase::FortifyHelper() {
//    string input;
//
//    cout << "In fortify method" << endl;
//    cout << "Do you wish to fortify a country?(Enter y, any other char otherwise):" << endl;
//    cin >> input;
//
//    if (input.find('y') == -1) {
//        cout << "Ending Fortify phase\n" << *player_name_ << "'s turn end." << endl;
//        return;//Skips/End Fortify phase
//    }
//
//    cout << "You have armies in the following countries:" << endl;
//    for (auto countries_owned : *countries_) {
//        cout << *countries_owned->GetCountryName() << " (" << countries_owned->GetNumberOfArmies() << " armies)" << endl;
//    }
//
//    //SOURCE COUNTRY
//    while(true) {
//        string country_source;
//        bool valid_country = false;
//        cout << "Which country do you wish to move your armies from?(Choose a country):" << endl;
//        cin >> country_source;
//
//        for (size_t i = 0; i < countries_->size(); i++) {
//            country_source_ = countries_->at(i);
//            if (country_source == *country_source_->GetCountryName() && country_source_->GetNumberOfArmies() > 1){
//                valid_country = true;
//                break;
//            }else if (country_source == *country_source_->GetCountryName() && country_source_->GetNumberOfArmies() <= 1){
//                cout << "Not enough units in this country. Please choose another country.\n" << endl;
//                break;
//            }
//
//            if((i+1) == countries_->size()) {
//                cout << "Invalid country name entered. Please choose another country.\n" << endl;
//            }
//        }
//
//        if(valid_country) {
//            break;
//        }
//    }
//
//    //TARGET COUNTRY
//    while(true) {
//        bool valid_country = false;
//        string country_target;
//        cout << "Which country to you wish to fortify?(Choose a country):" << endl;
//        cin >> country_target;
//
//        for (size_t i = 0; i < countries_->size(); i++) {
//            country_target_ = countries_->at(i);
//            if(country_target == *country_source_->GetCountryName()) {
//                cout << "Target country cannot be the same as source country." << endl;
//                break;
//            }else if(country_target == *country_target_->GetCountryName() && map_loaded_->AreCountriesNeighbors(country_target_, country_source_)){
//                cout<< "These countries are neighbors:" << endl;
//                cout<< "There are " << country_source_->GetNumberOfArmies() << " armies in " << *country_source_->GetCountryName() << "." << endl;
//                cout<< "There are " << country_target_->GetNumberOfArmies() << " armies in " << *country_target_->GetCountryName() << "." << endl;
//                valid_country = true;
//                break;
//            }else if(country_target == *country_target_->GetCountryName()){
//                cout <<"These countries are not neighbors. Please choose another country." << endl;
//                break;
//            }
//
//            if((i+1) == countries_->size()) {
//                cout << "Invalid country name entered. Please choose another country.\n" << endl;
//            }
//        }
//
//        if(valid_country){
//            break;
//        }
//    }
//
//    //ARMIES
//    while(true) {
//        int armies_number;
//        cout << "How many armies do you wish to move.(Enter a number):" << endl;
//
//        try{
//            cin >> input;
//            armies_number = stoi(input);
//        }catch(invalid_argument& e){
//            cout <<"Please enter a number." << endl;
//            continue;
//        }
//
//        if (armies_number > country_source_->GetNumberOfArmies()) {
//            cout << "You do not have enough armies in this country." << endl;
//        } else if (armies_number > country_source_->GetNumberOfArmies() - 1) {
//            cout << "You must leave at least 1 army in the country." << endl;
//        } else if (armies_number < 1) {
//            cout << "You must move at least 1 army." << endl;
//        } else {
//            cout << "Fortifying " << *country_target_->GetCountryName() << " with " << armies_number << " armies."
//                 << endl;
//            country_target_->SetNumberOfArmies(country_target_->GetNumberOfArmies() + armies_number);
//            country_source_->SetNumberOfArmies(country_source_->GetNumberOfArmies() - armies_number);
//            for (auto countries_owned : *countries_) {
//                cout << *countries_owned->GetCountryName() << " (" << countries_owned->GetNumberOfArmies()
//                     << " armies)" << endl;
//            }
//            cout << *player_name_ << "'s turn end." << endl;
//            delete country_source_;
//            delete country_target_;
//            delete map_loaded_;
//            return;
//        }
//    }
}
