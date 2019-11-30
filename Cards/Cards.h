/**
 * Assignment #4 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef CARDS_H
#define CARDS_H

#include "../Map/Map.h"
#include "../Utility/Utility.h"

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class Country;

// CARDS class ---------------------------------------------------------------------------------------------------------
class Cards{

private:
    string type_;

public:
    explicit Cards(const string& type);
    ~Cards() = default;

    string GetCardType() const;
    void DisplayCard();
};
// END OF CARDS class --------------------------------------------------------------------------------------------------

#endif //CARDS_H
