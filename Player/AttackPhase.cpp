//
// Created by Giselle Martel on 2019-11-29.
//

#include "AttackPhase.h"


// AttackPhase class implementation ------------------------------------------------------------------------------------

AttackPhase::AttackPhase() {
    attacking_country_ = nullptr;
    defending_country_ = nullptr;
    defender_ = nullptr;
    attacker_ = nullptr;
    opponent_neighbours_ = new vector<std::shared_ptr<Country>>;
    rand_player_num_attacks_ = 0;
}

AttackPhase::AttackPhase(std::shared_ptr<Player> player) {
    attacking_country_ = nullptr;
    defending_country_ = nullptr;
    defender_ = nullptr;
    attacker_ = player;
    opponent_neighbours_ = new vector<std::shared_ptr<Country>>;
    rand_player_num_attacks_ = 0;
}

AttackPhase::~AttackPhase() {

    attacking_country_ = nullptr;
    defending_country_ = nullptr;
    defender_ = nullptr;
    attacker_ = nullptr;

    delete opponent_neighbours_;
    opponent_neighbours_ = nullptr;
}

AttackPhase::AttackPhase(const AttackPhase& attack) {
    *attacking_country_ = *attack.attacking_country_;
    *defending_country_ = *attack.defending_country_;
    *defender_ = *attack.defender_;
    *attacker_ = *attack.attacker_;
    rand_player_num_attacks_ = attack.rand_player_num_attacks_;

    *opponent_neighbours_ = *attack.opponent_neighbours_;
    for(int i = 0; i < attack.opponent_neighbours_->size(); ++i) {
        (*opponent_neighbours_)[i] = (*attack.opponent_neighbours_)[i];
        (*attack.opponent_neighbours_)[i] = nullptr;
    }

    delete attack.opponent_neighbours_;
}

AttackPhase& AttackPhase::operator=(const AttackPhase& attack) {
    *attacking_country_ = *attack.attacking_country_;
    *defending_country_ = *attack.defending_country_;
    *defender_ = *attack.defender_;
    *attacker_ = *attack.attacker_;
    rand_player_num_attacks_ = attack.rand_player_num_attacks_;

    *opponent_neighbours_ = *attack.opponent_neighbours_;
    for(int i = 0; i < attack.opponent_neighbours_->size(); ++i) {
        (*opponent_neighbours_)[i] = (*attack.opponent_neighbours_)[i];
        (*attack.opponent_neighbours_)[i] = nullptr;
    }

    delete attack.opponent_neighbours_;

    return *this;
}

int AttackPhase::GetRandPlayerNumAttacks() const {
    return rand_player_num_attacks_;
}

std::shared_ptr<Country> AttackPhase::GetAttackingCountry() const {
    return attacking_country_;
}

std::shared_ptr<Country> AttackPhase::GetDefendingCountry() const {
    return defending_country_;
}

vector<std::shared_ptr<Country>>* AttackPhase::GetOpponentNeighbours() const {
    return opponent_neighbours_;
}

void AttackPhase::SetRandPlayerNumAttacks(int num_attacks) {
    rand_player_num_attacks_ = num_attacks;
}

void AttackPhase::SetAttackingCountry(std::shared_ptr<Country> attacking_country) {
    attacking_country_ = attacking_country;
}

void AttackPhase::SetDefender(std::shared_ptr<Player> defender) {

    defender_ = defender;
}

void AttackPhase::SetDefendingCountry(std::shared_ptr<Country> defending_country) {
    defending_country_ = defending_country;
}

void AttackPhase::UpdateNumAttacks() {
    --rand_player_num_attacks_;
}

void AttackPhase::RemoveDefeatedCountryFromOpponents(std::shared_ptr<Country> defeated_country) {
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
    opponent_neighbours_ = new vector<std::shared_ptr<Country>>;
    vector<Country*>* neighbours = attacker_->GetGameMap()->GetNeighbouringCountries(attacking_country_.get());
    defending_country_ = nullptr;

    if(neighbours->empty()) {
        cout << endl << *attacking_country_->GetCountryName() << " has no neighbours with armies!\n";
        defending_country_ = nullptr;
    }


    for(Country* neighbour : *neighbours) {
        if(!attacker_->DoesPlayerOwnCountry(neighbour->GetCountryID())) {
            std::shared_ptr<Country> ptr (neighbour);
            opponent_neighbours_->push_back(ptr);
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
        vector<Country*>* neighbouring_countries = attacker_->GetGameMap()->GetNeighbouringCountries(country);

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