

#ifndef TEAMPROJECT_COMP345_HAND_H
#define TEAMPROJECT_COMP345_HAND_H

#include "Cards.h"

#include <vector>
#include <iostream>

using namespace std;

class Cards;

// HAND class ----------------------------------------------------------------------------------------------------------
class Hand{

private:
    vector<Cards*>* cards_in_hand_;

public:
    inline static int exchanges_done = 0;
    Hand();
    Hand(const Hand& hand);
    ~Hand();

    Hand& operator=(const Hand& hand);


    size_t GetNumberOfCardsInHand() const;

    // Methods---------------------------------------------
    int Exchange();
    int AutoExchange();
    size_t InputCard();
    bool ValidateInput(size_t card_index);
    void AddCardToHand(Cards* card_);
    void DisplayHand();

    static int AcquireArmy(int exchanges_done);
    static size_t Max(size_t index_1, size_t index_2, size_t index_3);
    static size_t Mid(size_t index_1, size_t index_2, size_t index_3);
    static size_t Min(size_t index_1, size_t index_2, size_t index_3);
    static bool AreThreeSame(Cards* card_1, Cards* card_2, Cards* card_3);
    static bool AreThreeDifferent(Cards* card_1, Cards* card_2, Cards* card_3);
};
// END HAND class ------------------------------------------------------------------------------------------------------

#endif //TEAMPROJECT_COMP345_HAND_H
