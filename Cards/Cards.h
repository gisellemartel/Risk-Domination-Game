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
    int card_army_value_;
    string card_country_;

public:
    //constructors
    Cards(string type, int card_army_value, string card_country);
    Cards(const Cards &cards);
    ~Cards();

    //operator overloader
    Cards& operator=(const Cards &cards);

//    Setters---------------------------------------------
    void SetCardType(string card_type);
    void SetCardArmyValue(int card_value);
    void SetCardCountry(string card_country);
//    Getters---------------------------------------------
    const string GetCardType() const;
    const int GetCardArmyValue() const;
    const string GetCardCountry() const;
//    Methods---------------------------------------------
    void DisplayCard();
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
    void SetNumberOfCardsInDeck(int num_cards);
//    Getters---------------------------------------------
    const int GetNumberOfCardsInDeck() const;
//    Methods---------------------------------------------
    void CreateDeck();
    Cards Draw();
    void DisplayDeck();

};

class Hand{
private:
    int num_cards_hand;
    vector<Cards*>* cards_in_hand_;
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
