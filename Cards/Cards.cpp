/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */


#include "Cards.h"
#include "../Map/Map.h"
#include <iostream>
using namespace std;


//Cards class ---------------------------------------------

//Constructors
Cards::Cards(const Cards &cards) {
    type_ = cards.type_;
    card_army_value_ =  cards.card_army_value_;
    card_country_ = cards.card_country_;
}

Cards::Cards(string type, int card_army_value, string card_country){
    type_ = type;
    card_army_value_ = card_army_value;
    card_country_ = card_country;
}

Cards::~Cards() {

}

Cards& Cards::operator=(const Cards &cards)
{
    type_ = cards.type_;
    card_army_value_ = cards.card_army_value_;
    card_country_ = cards.card_country_;
    return *this;
}

void Cards::SetCardType(string card_type)
{
    type_ = card_type;
}

void Cards::SetCardArmyValue(int card_value)
{
    card_army_value_ = card_value;
}

void Cards::SetCardCountry(string card_country)
{
    card_country_ = card_country;
}

const string Cards::GetCardType() const {
    return type_;
}

const int Cards::GetCardArmyValue() const {
    return card_army_value_;
}

const string Cards::GetCardCountry() const {
    return card_country_;
}

//Deck class -----------------------------------------------
Deck::Deck(const Deck &deck){
    num_cards_deck_ = deck.num_cards_deck_;
    cards_ = deck.cards_;
}

Deck::Deck(vector<Country*>* countries){
    num_cards_deck_ = countries->size();
    for(int i = 0; i< countries->size(); i++)
    {
        Cards deck_card = new Cards("soldier", 0,countries->at(i)->GetCountryName());
    }
}

Deck::~Deck(){

}

//Hand class ------------------------------------------------
Hand::Hand(){

}

Hand::~Hand(){

}