//
// Created by Giselle Martel on 2019-11-26.
//

#include "FortifyPhase.h"

// FortifyPhase class implementation -----------------------------------------------------------------------------------

FortifyPhase::FortifyPhase() {
    source_country_ = nullptr;
    target_country_ = nullptr;
    countries_with_armies_ = new vector<std::shared_ptr<Country>>;
    neighbours_to_fortify_ = new vector<std::shared_ptr<Country>>;
}

FortifyPhase::FortifyPhase(Player* player) {
    source_country_ = nullptr;
    target_country_ = nullptr;
    neighbours_to_fortify_ = new vector<std::shared_ptr<Country>>;
    countries_with_armies_ = new vector<std::shared_ptr<Country>>;
}

FortifyPhase::FortifyPhase(const FortifyPhase& fortify) {
    *source_country_ = *fortify.source_country_;
    *target_country_ = *fortify.target_country_;
    *neighbours_to_fortify_ = *fortify.neighbours_to_fortify_;

    for(int i = 0; i < fortify.neighbours_to_fortify_->size(); ++i) {
        (*neighbours_to_fortify_)[i] = (*fortify.neighbours_to_fortify_)[i];
        (*fortify.neighbours_to_fortify_)[i] = nullptr;
    }

    *countries_with_armies_ = *fortify.countries_with_armies_;
    for(int i = 0; i < fortify.countries_with_armies_->size(); ++i) {
        (*countries_with_armies_)[i] = (*fortify.countries_with_armies_)[i];
        (*fortify.countries_with_armies_)[i] = nullptr;
    }

    delete fortify.neighbours_to_fortify_;
    delete fortify.countries_with_armies_;
}

FortifyPhase::~FortifyPhase() {
    delete countries_with_armies_;
    delete neighbours_to_fortify_;
    countries_with_armies_ = nullptr;
    neighbours_to_fortify_ = nullptr;
}

FortifyPhase& FortifyPhase::operator=(const FortifyPhase &fortify) {
    *source_country_ = *fortify.source_country_;
    *target_country_ = *fortify.target_country_;
    *neighbours_to_fortify_ = *fortify.neighbours_to_fortify_;

    for(int i = 0; i < fortify.neighbours_to_fortify_->size(); ++i) {
        (*neighbours_to_fortify_)[i] = (*fortify.neighbours_to_fortify_)[i];
        (*fortify.neighbours_to_fortify_)[i] = nullptr;
    }

    *countries_with_armies_ = *fortify.countries_with_armies_;
    for(int i = 0; i < fortify.countries_with_armies_->size(); ++i) {
        (*countries_with_armies_)[i] = (*fortify.countries_with_armies_)[i];
        (*fortify.countries_with_armies_)[i] = nullptr;
    }

    delete fortify.neighbours_to_fortify_;
    delete fortify.countries_with_armies_;

    return *this;
}

std::shared_ptr<Country> FortifyPhase::GetSourceCountry() const {
    return source_country_;
}

std::shared_ptr<Country> FortifyPhase::GetTargetCountry() const {
    return target_country_;
};

vector<std::shared_ptr<Country>>* FortifyPhase::GetNeighboursToFortify() const {
    return neighbours_to_fortify_;
}

vector<std::shared_ptr<Country>> *FortifyPhase::GetCountriesWithArmies() const {
    return countries_with_armies_;
}


void FortifyPhase::SetSourceCountry(std::shared_ptr<Country> source) {
    source_country_ = source;
}

void FortifyPhase::SetTargetCountry(std::shared_ptr<Country> target) {
    target_country_ = target;
}

