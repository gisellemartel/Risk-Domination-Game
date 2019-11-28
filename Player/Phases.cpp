//
// Created by Giselle Martel on 2019-11-26.
//

#include "Phases.h"

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
    *turn_player_ = *reinforce.turn_player_;
    num_of_swaps_ = reinforce.num_of_swaps_;
    divider_ = reinforce.divider_;
    reinforcement_army_ = reinforce.reinforcement_army_;

    *reinforce_values_ = *reinforce.reinforce_values_;
    for(int i = 0; i < reinforce.reinforce_values_->size(); ++i) {
        reinforce_values_[i] = reinforce.reinforce_values_[i];
    }

    *countries_to_reinforce_ = *reinforce.countries_to_reinforce_;
    for(int i = 0; i < reinforce.countries_to_reinforce_->size(); ++i) {
        countries_to_reinforce_[i] = reinforce.countries_to_reinforce_[i];
    }

    delete reinforce.turn_player_;
    delete[] reinforce.reinforce_values_;
    delete[] reinforce.countries_to_reinforce_;

}

ReinforcePhase& ReinforcePhase::operator=(const ReinforcePhase& reinforce){
    *turn_player_ = *reinforce.turn_player_;
    num_of_swaps_ = reinforce.num_of_swaps_;
    divider_ = reinforce.divider_;
    reinforcement_army_ = reinforce.reinforcement_army_;

    *reinforce_values_ = *reinforce.reinforce_values_;
    for(int i = 0; i < reinforce.reinforce_values_->size(); ++i) {
        reinforce_values_[i] = reinforce.reinforce_values_[i];
    }

    *countries_to_reinforce_ = *reinforce.countries_to_reinforce_;
    for(int i = 0; i < reinforce.countries_to_reinforce_->size(); ++i) {
        countries_to_reinforce_[i] = reinforce.countries_to_reinforce_[i];
    }

    delete reinforce.turn_player_;
    delete[] reinforce.reinforce_values_;
    delete[] reinforce.countries_to_reinforce_;

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
        if(turn_player_->IsHuman()) {
            army_from_cards += turn_player_->GetPlayersCards()->Exchange();
        } else {
            army_from_cards += turn_player_->GetPlayersCards()->AutoExchange();
        }
    }

    return army_from_cards;
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
    rand_player_num_attacks_ = 0;
}

AttackPhase::AttackPhase(Player* player) {
    attacking_country_ = nullptr;
    defending_country_ = nullptr;
    defender_ = nullptr;
    attacker_ = player;
    game_map_ = player->GetGameMap();
    opponent_neighbours_ = new vector<Country*>;
    rand_player_num_attacks_ = 0;
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
    *attacking_country_ = *attack.attacking_country_;
    *defending_country_ = *attack.defending_country_;
    *defender_ = *attack.defender_;
    *attacker_ = *attack.attacker_;
    *game_map_ = *attack.game_map_;
    rand_player_num_attacks_ = attack.rand_player_num_attacks_;

    *opponent_neighbours_ = *attack.opponent_neighbours_;
    for(int i = 0; i < attack.opponent_neighbours_->size(); ++i) {
        (*opponent_neighbours_)[i] = (*attack.opponent_neighbours_)[i];
        (*attack.opponent_neighbours_)[i] = nullptr;
        delete (*attack.opponent_neighbours_)[i];
    }

    delete attack.attacking_country_;
    delete attack.defending_country_;
    delete attack.attacker_;
    delete attack.defender_;
    delete attack.game_map_;
    delete[] attack.opponent_neighbours_;
}

AttackPhase& AttackPhase::operator=(const AttackPhase& attack) {
    *attacking_country_ = *attack.attacking_country_;
    *defending_country_ = *attack.defending_country_;
    *defender_ = *attack.defender_;
    *attacker_ = *attack.attacker_;
    *game_map_ = *attack.game_map_;
    rand_player_num_attacks_ = attack.rand_player_num_attacks_;

    *opponent_neighbours_ = *attack.opponent_neighbours_;
    for(int i = 0; i < attack.opponent_neighbours_->size(); ++i) {
        (*opponent_neighbours_)[i] = (*attack.opponent_neighbours_)[i];
        (*attack.opponent_neighbours_)[i] = nullptr;
        delete (*attack.opponent_neighbours_)[i];
    }

    delete attack.attacking_country_;
    delete attack.defending_country_;
    delete attack.attacker_;
    delete attack.defender_;
    delete attack.game_map_;
    delete[] attack.opponent_neighbours_;

    return *this;
}

int AttackPhase::GetRandPlayerNumAttacks() const {
    return rand_player_num_attacks_;
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

void AttackPhase::SetRandPlayerNumAttacks(int num_attacks) {
    rand_player_num_attacks_ = num_attacks;
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

void AttackPhase::UpdateNumAttacks() {
    --rand_player_num_attacks_;
}

void AttackPhase::RemoveDefeatedCountryFromOpponents(Country *defeated_country) {
    if(!defeated_country || !opponent_neighbours_ || opponent_neighbours_->empty()) {
        return;
    }

    int idx_to_remove = -1;
    for(int i = 0; i < opponent_neighbours_->size(); ++i) {
        if (*(*opponent_neighbours_)[i] == *defeated_country) {
            idx_to_remove = i;
            break;
        }
    }

    if(idx_to_remove != -1) {
        opponent_neighbours_->erase(opponent_neighbours_->begin() + idx_to_remove);
        defending_country_ = nullptr;
    }

}

void AttackPhase::FindOpponentNeighboursToAttackingCountry() {
    opponent_neighbours_ = new vector<Country*>;
    vector<Country*>* neighbours = game_map_->GetNeighbouringCountries(attacking_country_);
    defending_country_ = nullptr;

    if(neighbours->empty()) {
        cout << endl << *attacking_country_->GetCountryName() << " has no neighbours with armies!\n";
        defending_country_ = nullptr;
    }


    for(Country* neighbour : *neighbours) {
        if(!attacker_->DoesPlayerOwnCountry(neighbour->GetCountryID())) {
            opponent_neighbours_->push_back(neighbour);
        }
    }

    if(!opponent_neighbours_ || opponent_neighbours_->empty()) {
        cout << "No opposing neighbours found!\n";
        opponent_neighbours_ = nullptr;
    }
}

bool AttackPhase::DoesOpposingCountryExist() {
    //check here to see if there is not a single country that can attack
    bool has_enemy = false;
    for(Country* country : *attacker_->GetPlayersCountries()) {
        //Get all the neighbouring countries
        vector<Country*>* neighbouring_countries = game_map_->GetNeighbouringCountries(country);

        if(!neighbouring_countries->empty()) {
            //if there is a neighbour that has an army, then verify the country belongs to an opponent
            for(int i = 0; i < neighbouring_countries->size(); ++i) {
                if(!attacker_->DoesPlayerOwnCountry((*neighbouring_countries)[i]->GetCountryID())) {
                    has_enemy = true;
                }
            }
        }
    }

    if(!has_enemy) {
        cout << "No opposing neighbour exists that you can attack right now\n";
        return false;
    } else {
        return true;
    }
}

bool AttackPhase::PlayerHasCountryWithEnoughArmiesToAttack() {

    int countries_not_enough_armies_ctr = 0;

    for(Country* country : *attacker_->GetPlayersCountries()) {
        if(country->GetNumberOfArmies() < 2) {
            ++countries_not_enough_armies_ctr;
        }
    }

    return countries_not_enough_armies_ctr != attacker_->GetPlayersCountries()->size();
}

// FortifyPhase class implementation -----------------------------------------------------------------------------------

FortifyPhase::FortifyPhase() {
    player_= nullptr;
    game_map_ = nullptr;
    source_country_ = nullptr;
    target_country_ = nullptr;
    countries_with_armies_ = new vector<Country*>;
    neighbours_to_fortify_ = new vector<Country*>;
}

FortifyPhase::FortifyPhase(Player* player) {
    player_= player;
    game_map_ = player->GetGameMap();
    source_country_ = nullptr;
    target_country_ = nullptr;
    neighbours_to_fortify_ = new vector<Country*>;
    countries_with_armies_ = new vector<Country*>;
}

FortifyPhase::FortifyPhase(const FortifyPhase& fortify) {
    *player_ = *fortify.player_;
    *game_map_ = *fortify.game_map_;
    *source_country_ = *fortify.source_country_;
    *target_country_ = *fortify.target_country_;

    *neighbours_to_fortify_ = *fortify.neighbours_to_fortify_;


    for(int i = 0; i < fortify.neighbours_to_fortify_->size(); ++i) {
        (*neighbours_to_fortify_)[i] = (*fortify.neighbours_to_fortify_)[i];
        (*fortify.neighbours_to_fortify_)[i] = nullptr;
        delete (*fortify.neighbours_to_fortify_)[i];
    }

    *countries_with_armies_ = *fortify.countries_with_armies_;
    for(int i = 0; i < fortify.countries_with_armies_->size(); ++i) {
        (*countries_with_armies_)[i] = (*fortify.countries_with_armies_)[i];
        (*fortify.countries_with_armies_)[i] = nullptr;
        delete (*fortify.countries_with_armies_)[i];
    }

    delete fortify.player_;
    delete fortify.game_map_;
    delete fortify.source_country_;
    delete fortify.target_country_;
    delete[] fortify.neighbours_to_fortify_;
    delete[] fortify.countries_with_armies_;
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

    for(Country* country : *countries_with_armies_) {
        country = nullptr;
        delete country;
    }

    countries_with_armies_ = nullptr;
    neighbours_to_fortify_ = nullptr;

    delete[] countries_with_armies_;
    delete [] neighbours_to_fortify_;
    delete player_;
    delete game_map_;
    delete source_country_;
    delete target_country_;
}

FortifyPhase& FortifyPhase::operator=(const FortifyPhase &fortify) {
    *player_ = *fortify.player_;
    *game_map_ = *fortify.game_map_;
    *source_country_ = *fortify.source_country_;
    *target_country_ = *fortify.target_country_;

    *neighbours_to_fortify_ = *fortify.neighbours_to_fortify_;

    for(int i = 0; i < fortify.neighbours_to_fortify_->size(); ++i) {
        (*neighbours_to_fortify_)[i] = (*fortify.neighbours_to_fortify_)[i];
        (*fortify.neighbours_to_fortify_)[i] = nullptr;
        delete (*fortify.neighbours_to_fortify_)[i];
    }

    *countries_with_armies_ = *fortify.countries_with_armies_;
    for(int i = 0; i < fortify.countries_with_armies_->size(); ++i) {
        (*countries_with_armies_)[i] = (*fortify.countries_with_armies_)[i];
        (*fortify.countries_with_armies_)[i] = nullptr;
        delete (*fortify.countries_with_armies_)[i];
    }

    delete fortify.player_;
    delete fortify.game_map_;
    delete fortify.source_country_;
    delete fortify.target_country_;
    delete[] fortify.neighbours_to_fortify_;
    delete[] fortify.countries_with_armies_;

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

vector<Country *> *FortifyPhase::GetCountriesWithArmies() const {
    return countries_with_armies_;
}


void FortifyPhase::SetSourceCountry(Country *source) {
    source_country_ = source;
}

void FortifyPhase::SetTargetCountry(Country *target) {
    target_country_ = target;
}

