/**
 * Assignment #1 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef CARDS_H
#define CARDS_H

#include "../Map/Map.h"

#include <iostream>
#include <vector>

using namespace std;

class Country;

class Cards{

private:
    string type_;

public:

    Cards(string type);
    Cards(const Cards &cards);
    ~Cards();

    //operator overloader
    Cards& operator=(const Cards &cards);

    void SetCardType(string card_type);

    const string GetCardType() const;

    void DisplayCard();
};

class Deck{

private:
    int num_cards_deck_;
    vector<Cards*>* cards_;

public:
    Deck();
    Deck(const Deck &deck);
    ~Deck();


    void SetNumberOfCardsInDeck(int num_cards);

    const int GetNumberOfCardsInDeck() const;

    void CreateDeck(int num_cards);
    Cards Draw();
    void DisplayDeck();

};

class Hand{
private:
    int num_cards_hand_;
    int infantry_cards_;
    int cavalry_cards_;
    int artillery_cards_;
    vector<Cards*>* cards_in_hand_;
public:
    Hand();
    Hand(const Hand &hand);
    ~Hand();

//    Setters---------------------------------------------

//    Getters---------------------------------------------

//    Methods---------------------------------------------
    void AddCardToHand(Cards* card_);
    int Exchange();
    bool AreThreeSame(Cards* card_1, Cards* card_2, Cards* card_3);
    bool AreThreeDifferent(Cards* card_1, Cards* card_2, Cards* card_3);
    void DisplayHand();
};

#endif //CARDS_H
