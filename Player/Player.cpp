/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

#include "Player.h"

Player::Player(string player_name) {
    player_name_ = new string(player_name);
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
}

Player::~Player() {

    for(Country* country : *countries_) {
        delete country;
    }

    delete risk_cards_;
    delete countries_;
    delete dice_roll_;
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
    return *this;
}

bool Player::operator==(const Player& player) {
    return player_name_ == player.player_name_
            && is_player_turn_ == player.is_player_turn_
            && countries_ == player.countries_
            && risk_cards_ == player.risk_cards_
            && dice_roll_ == player.dice_roll_;
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

bool Player::isCurrentlyPlayersTurn() const {
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
    string input;

    cout << "In fortify method" << endl;
    cout << "Do you wish to fortify a country?(Enter y, any other char otherwise):" << endl;
    cin >> input;

    if (input.find('y') == -1) {
        cout << "Ending Fortify phase\n" << *player_name_ << "'s turn end." << endl;
        return;//Skips/End Fortify phase
    }

    cout << "You have armies in the following countries:" << endl;
    for (auto countries_owned : *countries_) {
        cout << *countries_owned->GetCountryName() << " (" << countries_owned->GetNumberOfArmies() << " armies)" << endl;
    }

    //SOURCE COUNTRY
    while(true) {
        string country_source;
        bool valid_country = false;
        cout << "Which country do you wish to move your armies from?(Choose a country):" << endl;
        cin >> country_source;

        for (size_t i = 0; i < countries_->size(); i++) {
            country_source_ = countries_->at(i);
            if (country_source == *country_source_->GetCountryName() && country_source_->GetNumberOfArmies() > 1){
                valid_country = true;
                break;
            }else if (country_source == *country_source_->GetCountryName() && country_source_->GetNumberOfArmies() <= 1){
                cout << "Not enough units in this country. Please choose another country.\n" << endl;
                break;
            }

            if((i+1) == countries_->size()) {
                cout << "Invalid country name entered. Please choose another country.\n" << endl;
            }
        }

        if(valid_country) {
            break;
        }
    }

    //TARGET COUNTRY
    while(true) {
        bool valid_country = false;
        string country_target;
        cout << "Which country to you wish to fortify?(Choose a country):" << endl;
        cin >> country_target;

        for (size_t i = 0; i < countries_->size(); i++) {
            country_target_ = countries_->at(i);
            if(country_target == *country_source_->GetCountryName()) {
                cout << "Target country cannot be the same as source country." << endl;
                break;
            }else if(country_target == *country_target_->GetCountryName() && map_loaded_->AreCountriesNeighbors(country_target_, country_source_)){
                cout<< "These countries are neighbors:" << endl;
                cout<< "There are " << country_source_->GetNumberOfArmies() << " armies in " << *country_source_->GetCountryName() << "." << endl;
                cout<< "There are " << country_target_->GetNumberOfArmies() << " armies in " << *country_target_->GetCountryName() << "." << endl;
                valid_country = true;
                break;
            }else if(country_target == *country_target_->GetCountryName()){
                cout <<"These countries are not neighbors. Please choose another country." << endl;
                break;
            }

            if((i+1) == countries_->size()) {
                cout << "Invalid country name entered. Please choose another country.\n" << endl;
            }
        }

        if(valid_country){
            break;
        }
    }

    //ARMIES
    while(true) {
        int armies_number;
        cout << "How many armies do you wish to move.(Enter a number):" << endl;

        try{
            cin >> input;
            armies_number = stoi(input);
        }catch(invalid_argument& e){
            cout <<"Please enter a number." << endl;
            continue;
        }

        if (armies_number > country_source_->GetNumberOfArmies()) {
            cout << "You do not have enough armies in this country." << endl;
        } else if (armies_number > country_source_->GetNumberOfArmies() - 1) {
            cout << "You must leave at least 1 army in the country." << endl;
        } else if (armies_number < 1) {
            cout << "You must move at least 1 army." << endl;
        } else {
            cout << "Fortifying " << *country_target_->GetCountryName() << " with " << armies_number << " armies."
                 << endl;
            country_target_->SetNumberOfArmies(country_target_->GetNumberOfArmies() + armies_number);
            country_source_->SetNumberOfArmies(country_source_->GetNumberOfArmies() - armies_number);
            for (auto countries_owned : *countries_) {
                cout << *countries_owned->GetCountryName() << " (" << countries_owned->GetNumberOfArmies()
                     << " armies)" << endl;
            }
            cout << *player_name_ << "'s turn end." << endl;
            delete country_source_;
            delete country_target_;
            delete map_loaded_;
            return;
        }
    }
}
