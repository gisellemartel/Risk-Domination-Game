/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <vector>
#include "../Map/Map.h"

using namespace std;
class Country;

class Cards{
private:
    string type_;

public:
    //constructors
    Cards(string type);
    Cards(const Cards &cards);
    ~Cards();

    //operator overloader
    Cards& operator=(const Cards &cards);

//    Setters---------------------------------------------
    void SetCardType(string card_type);
//    Getters---------------------------------------------
    const string GetCardType() const;
//    Methods---------------------------------------------
    void DisplayCard();
};

class Deck{
private:
    int num_exchanges;
    int num_cards_deck_;
    vector<Cards*>* cards_;

public:
    Deck();
    Deck(const Deck &deck);
    ~Deck();

//    Setters---------------------------------------------

//    Getters---------------------------------------------
    int GetNumExchanges();
    const int GetNumberOfCardsInDeck() const;
//    Methods---------------------------------------------
    void CreateDeck(int num_cards);
    Cards* Draw();
    void DisplayDeck();

};

class Hand{
private:
    vector<Cards*>* cards_in_hand_;
public:
    Hand();
    Hand(const Hand &hand);
    ~Hand();

//    Setters---------------------------------------------

//    Getters---------------------------------------------

    const int GetNumberOfCardsInHand() const;
//    Methods---------------------------------------------
    void AddCardToHand(Cards* card_);
    int Exchange(int exchanges_done);
    int InputCard();
    bool ValidateInput(int card_index);
    int AcquireArmy(int exchanges_done);
    bool AreThreeSame(Cards* card_1, Cards* card_2, Cards* card_3);
    bool AreThreeDifferent(Cards* card_1, Cards* card_2, Cards* card_3);

    void DisplayHand();
};

#endif //CARDS_H
