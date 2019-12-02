
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
