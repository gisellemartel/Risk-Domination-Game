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

class Cards{
private:
    string type_;
    int card_value_;

public:
    Cards();
    Cards(const Cards &cards);
    ~Cards();

//    Setters---------------------------------------------
    void setCardType(string card_type);
    void setCardValue(int card_value);
    void setCardCountry(string card_country);
//    Getters---------------------------------------------
    const string GetCardType() const {return type_ ;}
    const int GetCardValue() const {return card_value_;}
    const string GetCardCountry() const {return card_country;}
//    Methods---------------------------------------------
};

class Deck{
private:
    int num_cards_deck_;
    vector<Cards*>* cards_;

public:
    Deck(vector<Country*>* countries_);
    Deck(const Deck &deck);
    ~Deck();

//    Setters---------------------------------------------

//    Getters---------------------------------------------

//    Methods---------------------------------------------
    void CreateDeck();
    Cards Draw();

};

class Hand{
private:
    int num_cards_hand;
    vector<Cards*>* cards_in_hands_;
public:
    Hand();
    Hand(const Hand &hand);
    ~Hand();

//    Setters---------------------------------------------

//    Getters---------------------------------------------

//    Methods---------------------------------------------
    void AddCardToHand(Cards* card_);
    int Exchange(Cards* card_1, Cards* card_2, Cards* card_3);

};

#endif //CARDS_H
