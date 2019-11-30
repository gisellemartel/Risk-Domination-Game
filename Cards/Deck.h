//
// Created by Giselle Martel on 2019-11-29.
//

#ifndef TEAMPROJECT_COMP345_DECK_H
#define TEAMPROJECT_COMP345_DECK_H

#include "Cards.h"

#include <vector>
#include <iostream>

using namespace std;

// DECK class ----------------------------------------------------------------------------------------------------------
class Deck{

private:
    int num_exchanges;
    int num_cards_deck_;
    vector<Cards*>* cards_;

public:
    Deck();
    Deck(const Deck& deck);
    ~Deck();

    Deck& operator=(const Deck& deck);

    size_t GetNumberOfCardsInDeck() const;

    void CreateDeck(int num_cards);
    void DisplayDeck();

    Cards* Draw();
};
// END DECK class ------------------------------------------------------------------------------------------------------


#endif //TEAMPROJECT_COMP345_DECK_H
