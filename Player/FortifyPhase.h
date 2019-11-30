//
// Created by Giselle Martel on 2019-11-26.
//

#ifndef TEAMPROJECT_COMP345_FORTIFYPHASE_H
#define TEAMPROJECT_COMP345_FORTIFYPHASE_H

#include <iostream>
using namespace std;

#include "Player.h"

class Map;

class FortifyPhase {

private:
    std::shared_ptr<Country> source_country_;
    std::shared_ptr<Country> target_country_;

    vector<std::shared_ptr<Country>>* countries_with_armies_;
    vector<std::shared_ptr<Country>>* neighbours_to_fortify_;

public:

    explicit FortifyPhase();
    explicit FortifyPhase(Player* player);
    FortifyPhase(const FortifyPhase& fortify);
    ~FortifyPhase();

    FortifyPhase& operator=(const FortifyPhase& fortify);

    std::shared_ptr<Country> GetSourceCountry() const;
    std::shared_ptr<Country> GetTargetCountry() const;
    vector<std::shared_ptr<Country>>* GetNeighboursToFortify() const;
    vector<std::shared_ptr<Country>>* GetCountriesWithArmies() const;

    void SetSourceCountry(std::shared_ptr<Country> source);
    void SetTargetCountry(std::shared_ptr<Country> target);
};


#endif //TEAMPROJECT_COMP345_FORTIFYPHASE_H
