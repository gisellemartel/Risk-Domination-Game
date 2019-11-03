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

//method to get country id
int Player::FindPositionOfCountry(Country* country) const {
    for (int i = 0; i < countries_->size(); i++) {

        //to list all countries
        //cout << *countries_->at(i)->GetCountryName() << endl;

        if (*countries_->at(i)->GetCountryName() == *country->GetCountryName()) {
            return i;
        }
    }
    return -1;
}

int Player::FindPositionOfCountryByName(string* country_name) const {


    for (int i = 0; i < countries_->size(); ++i) {

        //to list all countries
        //cout << *countries_->at(i)->GetCountryName() << endl;

        if (*countries_->at(i)->GetCountryName() == *country_name) {
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
    int num_of_armies_to_assign = (int)floor((float)(countries_->size() / 3));

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
    attack_phase->AttackHelper();

    //TODO implementation of rules below
    /**
     *  The player may choose one of the countries he owns that contains 2 or more armies,
     * and declare an attack on an adjacent country that is owned by another player

     A battle is then simulated by the attacker rolling at most 3 dice (which should not be more than the number
     of armies contained in the attacking country), and the defender rolling at most 2 dice (which should not be more
     than the number of armies contained in the attacking country)

    Outcome of attack is determined by comparing the defenders best dice roll with the attacker’s best dice roll
    •	If the defender rolls >= to the attacker, then then the attacker loses an army

    •	else the defender loses an army

    •	if the defender rolled 2 dice, then his other dice roll is compared to the attacker’s 2nd best dice roll
        and a second army is lost by the attacker or defender in the same way as above

    •	the attackers can choose to continue attacking until either all his armies or all the defending armies have been eliminated.

    •	If all the defender’s armies are eliminated the attacker captures the territory, and the attacking player
        must then place a number of armies in the conquered country which is greater or equal than the number of
        dice that was used in the attack that resulted in conquering the country

    •	A player may do as many attacks as he wants during his turn

    •	Once he declares that he is done attacking, or he cannot attack because none of his countries that have an
        adjacent country controlled by another player is containing more than one army), the fortification phase begins

     */
}

void Player::Fortify() {
    cout << "In fortify method" << endl;
    //TODO implementation of rules below
    /**
     	The player may move any number of armies from one of his owed countries to the other,
         provided that there is a path between these two countries that is composed of countries that he owns.

     	Only one such move is allowed per fortification phase

     	Once the move is made, or the place forfeits his fortification phase, the player’s turn ends,
         and it is now the next player’s turn.

     	Any player that does not control at least one country is removed from the game

     	The game end at any time one of the players owns all the countries in the map
     */

}


// Attack class implementation -----------------------------------------------------------------------------------------
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
    cout << "Do you Mr/Miss " << *attacker_->GetPlayerName() << " want to issue an attack ? (enter 'y' to attack and any other character otherwise)" << endl;
    while(!(cin >> answer)) {
        cout << "Your answer is not correct, please choose a valid answer" << endl;
        cin.clear();
        cin.ignore(132, '\n');
    }
    return answer == "y" ? true : false;
}

void AttackPhase::AttackHelper() {
    //ask player if they wish to carry-out an attack
    if (PromptUserToAttack()) {
        //prompt player to select a country they wish to attack with
        attacking_country_ = SelectCountryToAttackFrom();
        if (attacking_country_) {
            cout << "You have chosen to attack with " << *attacking_country_->GetCountryName() << endl;
            defending_country_ = SelectCountryToAttack();
            if (!defending_country_) {
                cout << "Cannot proceed attack, invalid country selected to attack!";
                return;
            }

            cout << "You have chosen to attack " << *defending_country_->GetCountryName() << endl;
        } else {
            cout << "Cannot proceed attack, invalid country selected to attack from!";
            return;
        }
    } else {
        cout << "You do not wish to attack, aborting";
        return;
    }


    PerformDiceRoll();

//    //to try to attack again
//    AttackHelper();
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


    //compare the values in pairwise manner
//    int compares = 0;
//    if (num_of_attacker_dice < num_of_defender_dice) {
//        compares = num_of_attacker_dice;
//    } else {
//        compares = num_of_defender_dice;
//    }
//
//    for (int i = 0; i < compares; ++i) {
//        if (attackerDiceArray[i] <= defenderDiceArray[i]) {
//            cout << "Defender has won this turn ! Attacker Role : " << attackerDiceArray[i] << "; Defender Role: "
//                 << defenderDiceArray[i] << endl;
//            attacking_country_->SetNumberOfArmies(attacking_country_->GetNumberOfArmies() - 1);
//        } else {
//            cout << "Attacker has won this turn ! Attacker Role : " << attackerDiceArray[i] << "; Defender Role: "
//                 << defenderDiceArray[i] << endl;
//            defending_country_->SetNumberOfArmies(defending_country_->GetNumberOfArmies() - 1);
//        }
//
//
//        cout << "Number of armies left on base country  <<Attacker>>" << attacking_country_->GetNumberOfArmies() << endl;
//        cout << "Number of armies left on target country <<Defender>> : " << defending_country_->GetNumberOfArmies() << endl;
//
//        //attacker won
//        if (defending_country_->GetNumberOfArmies() < 1) {
//            cout << "Attacker " << *attacker_->GetPlayerName() << " has won this round of attack! They now own : "
//                 << *defending_country_->GetCountryName() << endl;
//            attacker_->AddCountryToCollection(defending_country_);
//            //move army from base to target
//            while (true) {
//                cout << "Choose number of army to move between 1 and " << attacking_country_->GetNumberOfArmies() - 1 << endl;
//                int moveNo;
//                cin >> moveNo;
//                if (moveNo > 0 && moveNo < attacking_country_->GetNumberOfArmies()) {
//                    attacking_country_->SetNumberOfArmies(attacking_country_->GetNumberOfArmies() - moveNo);
//                    defending_country_->SetNumberOfArmies(moveNo);
//                    break;
//                } else {
//                    cout << "The number you choose is not valid, try again" << endl;
//                }
//            }
//            break;
//        } else if (attacking_country_->GetNumberOfArmies() < 1) {
//            cout << "Attacker has no more army in base country, ending attack" << endl;
//            break;
//        }
//    }
}
