/**
 * Assignment #4 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef CARDS_H
#define CARDS_H

#include "../Map/Map.h"

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
    Cards(const Cards& cards);
    ~Cards();

    //operator overloader
    Cards& operator=(const Cards& cards);

    void SetCardType(string& card_type);

    string GetCardType() const;

    void DisplayCard();
};
// END OF CARDS class --------------------------------------------------------------------------------------------------


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
    
    int GetNumExchanges() const;
    size_t GetNumberOfCardsInDeck() const;

    void CreateDeck(int num_cards);
    void DisplayDeck();

    Cards* Draw();
};
// END DECK class ------------------------------------------------------------------------------------------------------


// HAND class ----------------------------------------------------------------------------------------------------------
class Hand{

private:
    vector<Cards*>* cards_in_hand_;

public:
    inline static int exchanges_done = 0;
    Hand();
    Hand(const Hand& hand);
    ~Hand();


    size_t GetNumberOfCardsInHand() const;

    // Methods---------------------------------------------
    int Exchange();
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


#endif //CARDS_H
