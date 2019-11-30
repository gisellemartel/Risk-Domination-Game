//
// Created by Giselle Martel on 2019-11-26.
//

#include "FortifyPhase.h"

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

FortifyPhase::~FortifyPhase() = default;

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