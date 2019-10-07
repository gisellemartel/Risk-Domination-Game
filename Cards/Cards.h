/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <vector>

using namespace std;

class Cards{
private:
    string type_;

public:
    Cards();
    ~Cards();

//    Setters---------------------------------------------

//    Getters---------------------------------------------
    const string GetCardType() const {return type_ ;}
//    Methods---------------------------------------------
};

class Deck{
private:
    int num_cards_deck;
    vector<Cards*>* cards_;

public:
    Deck(int num_countries);
    ~Deck();

//    Setters---------------------------------------------

//    Getters---------------------------------------------

//    Methods---------------------------------------------
    Cards Draw();

};

class Hand{
private:
    int num_cards_hand;
public:
    Hand();
    ~Hand();

//    Setters---------------------------------------------

//    Getters---------------------------------------------

//    Methods---------------------------------------------
    int Exchange(Cards* card_1, Cards* card_2, Cards* card_3);

};

#endif //CARDS_H
