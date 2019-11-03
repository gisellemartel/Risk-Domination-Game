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

Attack::Attack(Player *pl, vector<Player> *payersVector, Map *mymap) {
    attacker = pl;
    vectorOfPlayers = payersVector;
    map = mymap;

}

bool Attack::attackOrNot() {
    cout << "Do you Mr/Miss " << *attacker->GetPlayerName() << " want to issue an attack ? (Yes or No)" << endl;

    string answer;
    cin >> answer;

    if (answer == "Yes" || answer == "yes") {
        return true;

    } else if (answer == "No" || answer == "no") {
        return false;

    } else {
        cout << "Your answer is not correct, please choose a valid answer" << endl;

        return attackOrNot();
    }

}

void Attack::attack() {
    int numofAttackerDice = 0;
    int numberofDefenderDice = 0;


    if (attackOrNot()) {
        Base = CheckBaseCountry();

        if (Base) {
            int BaseArmyNo = Base->GetNumberOfArmies();
            Target = ChecktargetCountry(Base);
            if (Target) {
            } else {
                cout << "Cannot proceed attack without target country";
                return;
            }
        } else {
            cout << "Cannot proceed attack without base country";
            return;
        }
    } else {
        cout << "You do not wish to attack, aborting";
        return;
    }

    int BaseArmyNo = Base->GetNumberOfArmies();
    int TargetArmyNo = Target->GetNumberOfArmies();

    cout << "The attacker has : " << BaseArmyNo << " armies" << endl;
    cout << "The defender has : " << TargetArmyNo << " armies" << endl;

    int attackerMax = 3;

    if ((BaseArmyNo - 1) < 3) {
        attackerMax = BaseArmyNo - 1;
    }

    while (true) {
        cout << "How many dice does attacker want to roll? Choose between 1-" << attackerMax << endl;
        cin >> numofAttackerDice;
        if (numofAttackerDice <= attackerMax && numofAttackerDice > 0) {
            break;
        } else {
            cout << "The number you selected is not within the right range, try again";
            continue;
        }
    }

    int defenderMax = 2;

    if ((TargetArmyNo) < 2) {
        defenderMax = TargetArmyNo;
    }

    while (true) {
        cout << "How many dice does defender want to roll? Choose between 1-" << defenderMax << endl;
        cin >> numberofDefenderDice;
        if (numberofDefenderDice <= defenderMax && numberofDefenderDice > 0) {
            break;
        } else {
            cout << "The number you selected is not within the right range, try again";
            continue;
        }
    }

    attacker->SetPlayerDice(new Dice);
    defender->SetPlayerDice(new Dice);

    vector<int> attackerDiceArray = attacker->GetPlayerDice()->Roll(numofAttackerDice);
    cout << "Attacker dice rolled:\n";
    vector<int> defenderDiceArray = defender->GetPlayerDice()->Roll(numberofDefenderDice);
    cout << "Defender dice rolled:\n";

    sort(attackerDiceArray.begin(), attackerDiceArray.end());
    reverse(attackerDiceArray.begin(), attackerDiceArray.end());
    sort(defenderDiceArray.begin(), defenderDiceArray.end());
    reverse(defenderDiceArray.begin(), defenderDiceArray.end());


    int compares = 0;
    if (numofAttackerDice < numberofDefenderDice) {
        compares = numofAttackerDice;
    } else {
        compares = numberofDefenderDice;
    }

    for (int i = 0; i < compares; i++) {
        if (attackerDiceArray[i] <= defenderDiceArray[i]) {
            cout << "Defender has won this turn ! Attacker Role : " << attackerDiceArray[i] << "; Defender Role: "
                 << defenderDiceArray[i] << endl;
            Base->SetNumberOfArmies(Base->GetNumberOfArmies() - 1);
        } else {
            cout << "Attacker has won this turn ! Attacker Role : " << attackerDiceArray[i] << "; Defender Role: "
                 << defenderDiceArray[i] << endl;
            Target->SetNumberOfArmies(Target->GetNumberOfArmies() - 1);
        }


        cout << "Number of armies left on base country  <<Attacker>>" << Base->GetNumberOfArmies() << endl;
        cout << "Number of armies left on target country <<Defender>> : " << Target->GetNumberOfArmies() << endl;

        //attacker won
        if (Target->GetNumberOfArmies() < 1) {
            cout << "Attacker " << *attacker->GetPlayerName() << " has won this round of attack! They now own : "
                 << *Target->GetCountryName() << endl;
            attacker->AddCountryToCollection(Target);
            //move army from base to target
            while (true) {
                cout << "Choose number of army to move between 1 and " << Base->GetNumberOfArmies() - 1 << endl;
                int moveNo;
                cin >> moveNo;
                if (moveNo > 0 && moveNo < Base->GetNumberOfArmies()) {
                    Base->SetNumberOfArmies(Base->GetNumberOfArmies() - moveNo);
                    Target->SetNumberOfArmies(moveNo);
                    break;
                } else {
                    cout << "The number you choose is not valid, try again" << endl;
                }
            }
            break;
        } else if (Base->GetNumberOfArmies() < 1) {
            cout << "Attacker has no more army in base country, ending attack" << endl;
            break;
        }
    }

//to try to attack again
    Attack();
}


void Player::setArmies(int i) {
    numOFArmy = &i;
}


Country *Attack::CheckBaseCountry() {

    string baseCountryName;


    cout << "The Countries that you own are " << endl;
    attacker->DisplayCountires();


    cout << "Which country do you want to attack from?" << endl;

    cin >> baseCountryName;
    cout << baseCountryName << endl;
    cout << "hereerererer" << endl;

    int countryId = attacker->positionOfCountryByName(&baseCountryName);

    if (countryId != -1) {
        cout << "You own that country." << endl;

        if (attacker->getCountries()->at(countryId)->GetNumberOfArmies() >= 2) {
            cout << "Next we choose target country";
            return attacker->getCountries()->at(countryId);
            //call checktarget

        } else {
            cout << "You do not have enough armies in this country. Try Again." << endl;
            if (this->attackOrNot()) {
                return this->CheckBaseCountry();
            }

        }

    } else {
        cout << "You do not own that country. Try Again." << endl;
        if (this->attackOrNot()) {
            return this->CheckBaseCountry();
        }
    }
    return nullptr;
}

Country *Attack::ChecktargetCountry(Country *baseCountry) {

    cout << "Now, which country you would like to attack " << endl;
    string targetCountryName;
    cin >> targetCountryName;
    Country *target;

    if (baseCountry->IsNeighborByName(&targetCountryName, target)) {
        cout << "Those Countries are neighbors, Now you can proceed " << endl;
        return target;
    } else {
        cout << "You can not attack this country from your base" << endl;
        cout << "Do you want to try again ? (Yes or No)" << endl;

        while (true) {
            string answer;
            cin >> answer;

            if (answer == "Yes" || answer == "yes") {
                return ChecktargetCountry(baseCountry);
                break;
            } else if (answer == "No" || answer == "no") {
                break;
            } else {
                cout << "Your answer is not correct, please choose a valid answer" << endl;
            }
        }

        return nullptr;

    }
}

void Player::DisplayCountires() const {


    for (const Country *country : *countries_) {


        cout << *country->GetCountryName() << endl;
    }
}

//method to get country id
int Player::positionOfCountry(Country *country) const {


    for (int i = 0; i < countries_->size(); i++) {

        //to list all countries
        //cout << *countries_->at(i)->GetCountryName() << endl;

        if (*countries_->at(i)->GetCountryName() == *country->GetCountryName()) {
            return i;
        }
    }
    return -1;
}

int Player::positionOfCountryByName(string *countryName) const {


    for (int i = 0; i < countries_->size(); i++) {

        //to list all countries
        //cout << *countries_->at(i)->GetCountryName() << endl;

        if (*countries_->at(i)->GetCountryName() == *countryName) {
            return i;
        }
    }
    return -1;
}

vector<Country *> *Player::getCountries() const {
    return countries_;
}


