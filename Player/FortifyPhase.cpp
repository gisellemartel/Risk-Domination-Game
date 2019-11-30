//
// Created by Giselle Martel on 2019-11-26.
//

#include "FortifyPhase.h"

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
    delete countries_to_reinforce_;
    delete reinforce_values_;
    delete turn_player_;

    reinforce_values_ = nullptr;
    countries_to_reinforce_ = nullptr;
    turn_player_ = nullptr;
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
    delete reinforce.reinforce_values_;
    delete reinforce.countries_to_reinforce_;

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
    delete reinforce.reinforce_values_;
    delete reinforce.countries_to_reinforce_;

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
        delete (*fortify.neighbours_to_fortify_)[i];
        (*fortify.neighbours_to_fortify_)[i] = nullptr;
    }

    *countries_with_armies_ = *fortify.countries_with_armies_;
    for(int i = 0; i < fortify.countries_with_armies_->size(); ++i) {
        (*countries_with_armies_)[i] = (*fortify.countries_with_armies_)[i];
        delete (*fortify.countries_with_armies_)[i];
        (*fortify.countries_with_armies_)[i] = nullptr;
    }

    delete fortify.player_;
    delete fortify.game_map_;
    delete fortify.source_country_;
    delete fortify.target_country_;
    delete fortify.neighbours_to_fortify_;
    delete fortify.countries_with_armies_;
}

FortifyPhase::~FortifyPhase() {
    for(Country* neighbour : *neighbours_to_fortify_) {
        delete neighbour;
        neighbour = nullptr;
    }

    for(Country* country : *countries_with_armies_) {
        delete country;
        country = nullptr;
    }

    delete countries_with_armies_;
    delete neighbours_to_fortify_;
    delete player_;
    delete game_map_;
    delete source_country_;
    delete target_country_;

    player_ = nullptr;
    game_map_ = nullptr;
    source_country_ = nullptr;
    target_country_ = nullptr;
    countries_with_armies_ = nullptr;
    neighbours_to_fortify_ = nullptr;
}

FortifyPhase& FortifyPhase::operator=(const FortifyPhase &fortify) {
    *player_ = *fortify.player_;
    *game_map_ = *fortify.game_map_;
    *source_country_ = *fortify.source_country_;
    *target_country_ = *fortify.target_country_;
    *neighbours_to_fortify_ = *fortify.neighbours_to_fortify_;

    for(int i = 0; i < fortify.neighbours_to_fortify_->size(); ++i) {
        (*neighbours_to_fortify_)[i] = (*fortify.neighbours_to_fortify_)[i];
        delete (*fortify.neighbours_to_fortify_)[i];
        (*fortify.neighbours_to_fortify_)[i] = nullptr;
    }

    *countries_with_armies_ = *fortify.countries_with_armies_;
    for(int i = 0; i < fortify.countries_with_armies_->size(); ++i) {
        (*countries_with_armies_)[i] = (*fortify.countries_with_armies_)[i];
        delete (*fortify.countries_with_armies_)[i];
        (*fortify.countries_with_armies_)[i] = nullptr;
    }

    delete fortify.player_;
    delete fortify.game_map_;
    delete fortify.source_country_;
    delete fortify.target_country_;
    delete fortify.neighbours_to_fortify_;
    delete fortify.countries_with_armies_;

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

