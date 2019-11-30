//
// Created by Giselle Martel on 2019-11-29.
//

#include "ReinforcePhase.h"

// ReinforcePhase class implementation ----------------------------------------------------------------------------
ReinforcePhase::ReinforcePhase() {
    num_of_swaps_ = 0;
    divider_ = 3;
    reinforcement_army_ = 0;
    reinforce_values_ = new vector<int>;
    countries_to_reinforce_ = new vector<int>;
}

ReinforcePhase::~ReinforcePhase(){
    delete countries_to_reinforce_;
    delete reinforce_values_;
    reinforce_values_ = nullptr;
    countries_to_reinforce_ = nullptr;
}

ReinforcePhase::ReinforcePhase(const ReinforcePhase& reinforce){
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

    delete reinforce.reinforce_values_;
    delete reinforce.countries_to_reinforce_;
}

ReinforcePhase& ReinforcePhase::operator=(const ReinforcePhase& reinforce){
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

    delete reinforce.reinforce_values_;
    delete reinforce.countries_to_reinforce_;

    return *this;
}

int ReinforcePhase::TotalReinforceArmy(Player* player, vector<Continent*>* continents){

    return PerCountryReinforceArmy(player->GetPlayersCountries()) + PerContinentReinforceArmy(player, continents) + CardSwapReinforceArmy(player);
}

int ReinforcePhase::PerCountryReinforceArmy(vector<Country*>* countries){
    if (countries->size() > 9) {
        int num_countries = countries->size();
        int rounded_down = num_countries / divider_;
        return rounded_down;
    } else {
        return 3;
    }
}

int ReinforcePhase::PerContinentReinforceArmy(Player* player, vector<Continent*>* continents){
    int armies_from_continent_bonus = 0;
    int num_of_continents =  continents->size();

    for(int i = 0; i < num_of_continents; ++i){

        vector<Country*>* countries = (*continents).at(i)->GetCountriesInContinent();
        int num_countries_in_continent = countries->size();

        for(int j = 0; j < num_countries_in_continent; ++j){
            int current_country_id = countries->at(j)->GetCountryID();

            //if there is a single country in the continent that the player does not own, then it does not control the continent
            if(!player->DoesPlayerOwnCountry(current_country_id)) {
                return 0;
            }
        }

        int army_value = continents->at(i)->GetContinentArmyValue();
        armies_from_continent_bonus += army_value;
    }
    return armies_from_continent_bonus;
}

int ReinforcePhase::CardSwapReinforceArmy(Player* player){
    int army_from_cards = 0;

    while(player->GetPlayersCards()->GetNumberOfCardsInHand() >= 5) {
        if(player->IsHuman()) {
            army_from_cards += player->GetPlayersCards()->Exchange();
        } else {
            army_from_cards += player->GetPlayersCards()->AutoExchange();
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

