/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <vector>
#include <iostream>
#include <utility>
#include <map>
#include <iterator>
#include <filesystem>

using namespace std;

#include "../Utility/Utility.h"
#include "../GameEngine/GameEngine.h"
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
    reinforce_phase_ = nullptr;
    fortify_phase_ = nullptr;
    game_engine_ = nullptr;
}

Player::Player(string player_name, Map *game_map, GameEngine* game_engine) {
    player_name_ = new string(player_name);
    game_map_ = game_map;
    game_engine_ = game_engine;
    is_player_turn_ = false;
    is_human_ = false;
    countries_ = new vector<Country*>;
    risk_cards_ = nullptr;
    dice_roll_ = nullptr;
    player_strategy_ = nullptr;
    reinforce_phase_ = nullptr;
    attack_phase_ = nullptr;
    fortify_phase_ = nullptr;
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
    fortify_phase_ = nullptr;
    attack_phase_ = nullptr;
    reinforce_phase_ = nullptr;
    game_engine_ = nullptr;
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
    reinforce_phase_ = player.reinforce_phase_;
    attack_phase_ = player.attack_phase_;
    fortify_phase_ = player.fortify_phase_;
    game_engine_ = player.game_engine_;
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
    delete reinforce_phase_;
    delete fortify_phase_;
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
    game_engine_ = player.game_engine_;
    player_strategy_ = player.player_strategy_;
    reinforce_phase_ = player.reinforce_phase_;
    attack_phase_ = player.attack_phase_;
    fortify_phase_ = player.fortify_phase_;
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
            && reinforce_phase_ == player.reinforce_phase_
            && attack_phase_ == player.attack_phase_
            && fortify_phase_ == player.fortify_phase_
            && game_engine_ == player.game_engine_
            && is_human_ == player.is_human_;
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

ReinforcePhase* Player::GetReinforcePhase() const {
    return reinforce_phase_;
}

AttackPhase* Player::GetAttackPhase() const {
    return attack_phase_;
}

FortifyPhase* Player::GetFortifyPhase() const {
    return fortify_phase_;
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

    Notify(this, GamePhase::Reinforce, "", false);

    reinforce_phase_ = new ReinforcePhase(this, 0);

    if(reinforce_phase_->TotalReinforceArmy() < 1) {
        string msg = *player_name_;
        msg.append(" currently has to armies to reinforce a country with. Please try again next round");
        Notify(this, GamePhase::Reinforce, msg, false);
        return;
    }

    player_strategy_->ReinforceStrategy(this);


    for(int i = 0; i < reinforce_phase_->GetReinforceValues()->size(); ++i) {
        Country* current_country = GetCountryById((*reinforce_phase_->GetCountriesToReinforce())[i]);

        if(!current_country) {
            continue;
        }

        int num_armies_to_add = (*reinforce_phase_->GetReinforceValues())[i];
        int current_num_armies = current_country->GetNumberOfArmies();

        string msg = *current_country->GetCountryName();
        msg.append(" | #armies: " + to_string(current_country->GetNumberOfArmies()));
        msg.append("\n" + *player_name_ + " reinforcing " + *current_country->GetCountryName() + " with " + to_string(num_armies_to_add) + " armies\n");

        Notify(this, GamePhase::Reinforce, msg, false);

        current_country->SetNumberOfArmies(current_num_armies + num_armies_to_add);

        msg = "Result: ";
        msg.append(*current_country->GetCountryName() + " | #armies: " + to_string(current_country->GetNumberOfArmies()) + "\n\n");

        Notify(this, GamePhase::Reinforce, msg, true);
    }


}

void Player::Attack() {

    if(!player_strategy_) {
        cout << "Player strategy undefined! Cannot Attack!" << endl;
        return;
    }

    attack_phase_ = new AttackPhase(this);

    while (player_strategy_->PromptPlayerToAttack(this)) {

        if(!attack_phase_->DoesOpposingCountryExist()) {
            cout << "No opposing country exists that has enough armies to be attacked!" << endl;
            break;
        }

        if(!player_strategy_->SelectCountryToAttackFrom(this)) {
            cout << "Failed to Select valid country to attack from!" << endl;
            break;
        }

        cout << *player_name_ << " has selected " << *attack_phase_->GetAttackingCountry()->GetCountryName() << " to attack with" << endl;
        attack_phase_->FindOpponentNeighboursToAttackingCountry();

        bool can_attack = !attack_phase_->GetOpponentNeighbours()->empty();

        if(can_attack) {
            can_attack &= player_strategy_->SelectCountryToAttack(this);

            if(!can_attack){
                cout << *player_name_ << " cannot attack since no neighbouring countries have armies!\n";
                can_attack = player_strategy_->SelectCountryToAttackFrom(this);
                can_attack &= player_strategy_->SelectCountryToAttack(this);
            }

            if(!attack_phase_->GetDefendingCountry()) {
                cout << "Invalid country selected to attack!" << endl;
                break;
            }

            cout << *player_name_<< " has selected " << *attack_phase_->GetDefendingCountry()->GetCountryName() << " to attack" << endl;

            Country* attacking_country = attack_phase_->GetAttackingCountry();
            Country* defending_country = attack_phase_->GetDefendingCountry();
            Player* defender = defending_country->GetCountryOwner();
            int attacker_num_dice = 0;
            int defender_num_dice = 0;
            //determine maximum number of rolls for each player based on rules of Risk
            int max_num_dice_attacker = (attacking_country->GetNumberOfArmies() - 1) < 3 ? attacking_country ->GetNumberOfArmies() : 3;

            const int MAX_NUM_OF_DICE_ATTACKER = (max_num_dice_attacker == 0) ? 1 : max_num_dice_attacker;
            const int MAX_NUM_OF_DICE_DEFENDER = (defending_country->GetNumberOfArmies()) < 2 ? defending_country ->GetNumberOfArmies() : 2;

            player_strategy_->AttackerSelectNumberOfDice(this, MAX_NUM_OF_DICE_ATTACKER, attacker_num_dice);

            cout << "\nIt is " << *defender->GetPlayerName() << "'s turn to enter the number of dice they wish to roll (can roll max " << MAX_NUM_OF_DICE_DEFENDER << ") dice: ";

            //if the player is human then they select their own number of dice otherwise it is randomly generated
            if(defender->IsHuman()) {
                while( !(cin >> defender_num_dice) || defender_num_dice < 1 || defender_num_dice > MAX_NUM_OF_DICE_DEFENDER) {
                    cout << "You have entered an invalid number of dice to roll. Please try again: ";
                    cin.clear();
                    cin.ignore(132, '\n');
                }
            } else {
                defender_num_dice = Utility::GenerateRandomNumInRange(1, MAX_NUM_OF_DICE_DEFENDER + 1);
            }

            cout << endl << *player_name_ << " has chosen to roll " << attacker_num_dice << " dice" << endl;
            cout << *defender->GetPlayerName() << " has chosen to roll " << defender_num_dice << " dice" << endl;

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
                    cout << "Attacker has lost this roll. Loosing an army\n";
                    attacking_country->RemoveArmiesFromCountry(1);
                    if(attacking_country->GetNumberOfArmies() == 0) {
                        cout << "Attacking country " << *attacking_country->GetCountryName() << " has run out of armies. Attack phase has ended\n";
                        return;
                    }
                    //defender lose an army if attacker's dice has a greater value
                } else if (attacker_dice_rolls[i] > defender_dice_rolls[i]) {
                    cout << "Defender has lost this roll. Loosing an army\n";

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

            cout << "\nResult:" << endl;

            cout << *player_name_ << endl;
            attacking_country->DisplayInfo();

            cout << endl << *defender->GetPlayerName() << endl;
            defending_country->DisplayInfo();
        }
    }

    //cout << *player_name_ << "'s Attack phase is over, going to next phase";
}

void Player::Fortify() {
    if(!player_strategy_) {
        cout << "Player strategy undefined! Cannot Fortify!" << endl;
        return;
    }

   // cout << "Beginning Fortify phase for " << *player_name_ << endl << endl;

    fortify_phase_ = new FortifyPhase(this);

    if(player_strategy_->PromptPlayerToFortify(this))  {
        vector<Country*> neighbouring_countries;

        int count = 0;
        for(Country* country : *countries_) {
            if(country->GetNumberOfArmies() < 1) {
                ++count;
            }
        }

        if(count == countries_->size()) {
            cout << "No countries with enough armies to assign to another country!\n";
           // cout << "Ending Fortify phase\n" << *player_name_ << "'s turn end." << endl;
            return;
        }

        player_strategy_->SelectSourceCountry(this);

        if(!fortify_phase_->GetSourceCountry()) {
            //cout << "Ending Fortify phase\n" << *player_name_ << "'s turn end." << endl;
            return;
        }

        Country* source_country = fortify_phase_->GetSourceCountry();


        cout << "Please select which target country you wish to fortify:\n";

        vector<Country*>* neighbours = game_map_->GetNeighbouringCountries(source_country);

        if(!neighbours || neighbours->empty()) {
            cout << *source_country->GetCountryName() << " has no neighbours!\n";
          //  cout << "Ending Fortify phase\n" << *player_name_ << "'s turn end." << endl;
            return;
        }

        //find all the neighbours of the source country that belong to the current player
        for(Country* country : *neighbours) {
            if(DoesPlayerOwnCountry(country->GetCountryID())) {
                fortify_phase_->GetNeighboursToFortify()->push_back(country);
            }
        }

        //only opponents are neighbours, skip phase
        if(fortify_phase_->GetNeighboursToFortify()->empty()) {
            cout << *source_country->GetCountryName() << " has no neighbours to assign armies to!\n";
           // cout << "Ending Fortify phase\n" << *player_name_ << "'s turn end." << endl;
            return;
        }

        //player selects country to fortify from list of neighbours
        cout << "\nHere are the neighbouring countries to " << *source_country->GetCountryName() << endl;
        cout << endl << setw(25)  << left << "Country ID" << setw(25)  << "Name" << setw(25) << right <<  "Number of Armies" << endl;
        for (const Country *country : *fortify_phase_->GetNeighboursToFortify()) {
            cout << setw(25)  << left << country->GetCountryID() << setw(25) <<  *country->GetCountryName() << setw(25) << right  << country->GetNumberOfArmies() << endl;
            cout << endl;
        }


        player_strategy_->SelectTargetCountry(this);

        if(!fortify_phase_->GetTargetCountry()) {
            //cout << "Ending Fortify phase\n" << *player_name_ << "'s turn end." << endl;
            return;
        }

        Country* target_country = fortify_phase_->GetTargetCountry();

        cout << "There are " << source_country->GetNumberOfArmies() << " armies in " << *source_country->GetCountryName() << "." << endl;
        cout << "There are " << target_country->GetNumberOfArmies() << " armies in " << *target_country->GetCountryName() << "." << endl;


        int num_of_armies;

        player_strategy_->FortifyStrategy(this, num_of_armies);

        cout << "Fortifying " << *target_country->GetCountryName() << " with " << num_of_armies << " armies." << endl;

        source_country->RemoveArmiesFromCountry(num_of_armies);
        target_country->SetNumberOfArmies(target_country->GetNumberOfArmies() + num_of_armies);

//        cout << "\nHere is the result after fortification: " << endl;
//
//        cout << "There are " << source_country->GetNumberOfArmies() << " armies in " << *source_country->GetCountryName() << "." << endl;
//        cout << "There are " << target_country->GetNumberOfArmies() << " armies in " << *target_country->GetCountryName() << "." << endl;

    }

//    cout << "Ending Fortify phase\n" << *player_name_ << "'s turn end." << endl;
}

//will be used to implicitly notify the game engine of phase changes
void Player::Notify(Player* current_player, int current_phase, string current_action_description, bool phase_over) {
    game_engine_->Notify(current_player, current_phase, current_action_description, phase_over);
}




// ReinforcePhase class implementation ----------------------------------------------------------------------------

ReinforcePhase::ReinforcePhase() {
    turn_player_ = nullptr;
    num_of_swaps_ = 0;
    divider_ = 3;
    reinforcement_army_ = 0;
    reinforce_values_ = new vector<int>;
    countries_to_reinforce_ = new vector<int>;
}

ReinforcePhase::ReinforcePhase(Player* turn_player, int num_of_swaps){
    turn_player_ = turn_player;
    num_of_swaps_ = num_of_swaps;
    divider_ = 3;
    reinforcement_army_ = 0;
    reinforce_values_ = new vector<int>;
    countries_to_reinforce_ = new vector<int>;
}

ReinforcePhase::~ReinforcePhase(){
    reinforce_values_ = nullptr;
    countries_to_reinforce_ = nullptr;
    turn_player_ = nullptr;

    delete[] countries_to_reinforce_;
    delete[] reinforce_values_;
    delete turn_player_;

}

ReinforcePhase::ReinforcePhase(const ReinforcePhase& reinforce){
    turn_player_ = reinforce.turn_player_;
    num_of_swaps_ = reinforce.num_of_swaps_;
    divider_ = reinforce.divider_;
    reinforcement_army_ = reinforce.reinforcement_army_;
    reinforce_values_ = reinforce.reinforce_values_;
    countries_to_reinforce_ =reinforce.countries_to_reinforce_;
}

ReinforcePhase& ReinforcePhase::operator=(const ReinforcePhase& reinforce){
    turn_player_ = reinforce.turn_player_;
    num_of_swaps_ = reinforce.num_of_swaps_;
    divider_ = reinforce.divider_;
    reinforcement_army_ = reinforce.reinforcement_army_;
    reinforce_values_ = reinforce.reinforce_values_;
    countries_to_reinforce_ =reinforce.countries_to_reinforce_;
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

vector<int>* ReinforcePhase::GetCountriesToReinforce() const {
    return countries_to_reinforce_;
}

vector<int>* ReinforcePhase::GetReinforceValues() const {
    return reinforce_values_;

}
void ReinforcePhase::SetTotalReinforcementArmy(int num_reinforcements) {
    reinforcement_army_= num_reinforcements;
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
    opponent_neighbours_ = game_map_->GetNeighbouringCountries(attacking_country_);
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

bool AttackPhase::DoesOpposingCountryExist() {
    //check here to see if there is not a single country that can attack
    bool country_that_can_be_attacked_exists = false;
    for(Country* country : *attacker_->GetPlayersCountries()) {
        //Get all the neighbouring countries that have armies
        vector<Country*>* neighbouring_countries = game_map_->GetNeighbouringCountries(country);

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

    if(!country_that_can_be_attacked_exists) {
        cout << "No opposing neighbour exists that you can attack right now\n";
        return false;
    } else {
        return true;
    }
}

// FortifyPhase class implementation -----------------------------------------------------------------------------------

FortifyPhase::FortifyPhase() {
    player_= nullptr;
    game_map_ = nullptr;
    source_country_ = nullptr;
    target_country_ = nullptr;
    neighbours_to_fortify_ = new vector<Country*>;
}

FortifyPhase::FortifyPhase(Player* player) {
    player_= player;
    game_map_ = player->GetGameMap();
    source_country_ = nullptr;
    target_country_ = nullptr;
    neighbours_to_fortify_ = new vector<Country*>;
}

FortifyPhase::FortifyPhase(const FortifyPhase& fortify) {
    player_ = fortify.player_;
    game_map_ = fortify.game_map_;
    source_country_ = fortify.source_country_;
    target_country_ = fortify.target_country_;
    neighbours_to_fortify_ = fortify.neighbours_to_fortify_;

    for(int i = 0; i < fortify.neighbours_to_fortify_->size(); ++i) {
        neighbours_to_fortify_[i] = fortify.neighbours_to_fortify_[i];
    }

}

FortifyPhase::~FortifyPhase() {
    player_ = nullptr;
    game_map_ = nullptr;
    source_country_ = nullptr;
    target_country_ = nullptr;

    for(Country* neighbour : *neighbours_to_fortify_) {
        neighbour = nullptr;
        delete neighbour;
    }

    neighbours_to_fortify_ = nullptr;

    delete [] neighbours_to_fortify_;
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
    neighbours_to_fortify_ = fortify.neighbours_to_fortify_;
    for(int i = 0; i < fortify.neighbours_to_fortify_->size(); ++i) {
        neighbours_to_fortify_[i] = fortify.neighbours_to_fortify_[i];
    }

    return *this;
}

Country* FortifyPhase::GetSourceCountry() const {
    return source_country_;
}

Country* FortifyPhase::GetTargetCountry() const {
    return target_country_;
};

vector<Country*>* FortifyPhase::GetNeighboursToFortify() const {
    return neighbours_to_fortify_;
}

void FortifyPhase::SetSourceCountry(Country *source) {
    source_country_ = source;
}

void FortifyPhase::SetTargetCountry(Country *target) {
    target_country_ = target;
}