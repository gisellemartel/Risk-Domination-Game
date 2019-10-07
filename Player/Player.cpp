/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

#include "Player.h"

Player::Player(string player_name) {
    player_name_ = player_name;
    is_player_turn_ = false;
    countries_ = new vector<Country*>;
    risk_cards_ = new vector<Cards*>;
    dice_roll_ = new Dice();
}

Player::Player(string player_name, vector<Country*>* countries_to_assign_to_player, bool is_player_turn) {
    cout << "Instantiating new Player object" << endl;
    player_name_ = player_name;
    is_player_turn_ = is_player_turn;
    //countries to be assigned to each player are chosen randomly at start-up phase
    countries_ = countries_to_assign_to_player;
    risk_cards_ = new vector<Cards*>;
    dice_roll_ = new Dice();
};

Player::Player(const Player &player) {
    player_name_ = player.player_name_;
    is_player_turn_ = player.is_player_turn_;
    for(int i = 0; i < player.risk_cards_->size(); ++i) {
        risk_cards_[i] = player.risk_cards_[i];
    }

    for(int i = 0; i < player.countries_->size(); ++i) {
        countries_[i] = player.countries_[i];
    }
    countries_ = player.countries_;
    risk_cards_ = player.risk_cards_;
    dice_roll_ = player.dice_roll_;
}

Player::~Player() {
    cout << "Destroying Player object" << endl;

    for(int i = 0; i < risk_cards_->size(); ++i) {
        delete (*risk_cards_)[i];
    }

    for(int i = 0; i < countries_->size(); ++i) {
        delete (*countries_)[i];
    }

    delete risk_cards_;
    delete countries_;
    delete dice_roll_;
}

Player& Player::operator=(const Player &player) {
    player_name_ = player.player_name_;
    is_player_turn_ = player.is_player_turn_;

    for(int i = 0; i < player.risk_cards_->size(); ++i) {
       risk_cards_[i] = player.risk_cards_[i];
    }

    for(int i = 0; i < player.countries_->size(); ++i) {
        countries_[i] = player.countries_[i];
    }

    risk_cards_ = player.risk_cards_;
    countries_ = player.countries_;
    dice_roll_ = player.dice_roll_;
    return *this;
}

void Player::Reinforce() {
    cout << "In reinforce method" << endl;

    //the number of armies the player is assigned at their current turn is the number of countries
    //they own divided by 3 rounded down
    int num_of_armies_to_assign = floor((float)(countries_->size() / 3));
    return;

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
    return;

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
    return;
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

bool Player::isCurrentlyPlayersTurn() const {
    return is_player_turn_;
}

Dice* Player::GetPlayerDice() const {
    return dice_roll_;
}

string Player::GetPlayerName() const {
    return player_name_;
}

vector<Country*>* Player::GetPlayersCountries() const {
    return countries_;
}

vector<Cards*>* Player::GetPlayersCards() const {
    return risk_cards_;
}

void Player::SetPlayersTurn(bool is_turn) {
    is_player_turn_ = is_turn;
}

void Player::SetPlayerName(string player_name) {
    player_name_ = player_name;
}

void Player::AddCountryToCollection(Country *country) {
    countries_->push_back(country);
}

void Player::AddCardToCollection(Cards* card) {
    risk_cards_->push_back(card);
}


