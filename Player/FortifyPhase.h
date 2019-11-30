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
    Player* player_;
    Map* game_map_;
    Country* source_country_;
    Country* target_country_;

    vector<Country*>* countries_with_armies_;
    vector<Country*>* neighbours_to_fortify_;

public:

    explicit FortifyPhase();
    explicit FortifyPhase(Player* player);
    FortifyPhase(const FortifyPhase& fortify);
    ~FortifyPhase();

    FortifyPhase& operator=(const FortifyPhase& fortify);

    Country* GetSourceCountry() const;
    Country* GetTargetCountry() const;
    vector<Country*>* GetNeighboursToFortify() const;
    vector<Country*>* GetCountriesWithArmies() const;

    void SetSourceCountry(Country* source);
    void SetTargetCountry(Country* target);
};


#endif //TEAMPROJECT_COMP345_FORTIFYPHASE_H