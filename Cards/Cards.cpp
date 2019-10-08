/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */


#include "Cards.h"
#include <iostream>
using namespace std;


//Cards class ---------------------------------------------

//Constructors
Cards::Cards(const Cards &cards) {
    type_ = cards.type_;
}

Cards::Cards(string type){
    type_ = type;
}

Cards::~Cards() {

}

Cards& Cards::operator=(const Cards &cards)
{
    type_ = cards.type_;
    return *this;
}

void Cards::SetCardType(string card_type)
{
    type_ = card_type;
}


const string Cards::GetCardType() const {
    return type_;
}


void Cards::DisplayCard(){
    cout<<"Card Type: "<<Cards::GetCardType()<<endl;
}

//Deck class -----------------------------------------------
Deck::Deck(const Deck &deck){
    num_cards_deck_ = deck.num_cards_deck_;
    cards_ = deck.cards_;
}

Deck::Deck(){
    cards_ = new vector<Cards*>;
    num_cards_deck_ = 0;
}

Deck::~Deck(){

}

void Deck::SetNumberOfCardsInDeck(int num_cards)
{
    num_cards_deck_ = num_cards;
}

const int Deck::GetNumberOfCardsInDeck() const {
    return num_cards_deck_;
}

void Deck::CreateDeck(int num_cards){

    int artillery_cards = num_cards/3;
    int cavalry_cards = num_cards/3;
    int infantry_cards = num_cards - (artillery_cards + cavalry_cards);


    for(int i=0; i<artillery_cards;i++){
        cards_->push_back(new Cards("artillery"));
        num_cards_deck_++;
    }

    for(int i=0; i<cavalry_cards;i++){
        cards_->push_back(new Cards("cavalry"));
        num_cards_deck_++;
    }

    for(int i=0; i<infantry_cards;i++){
        cards_->push_back(new Cards("infantry"));
        num_cards_deck_++;
    }

}

Cards Deck::Draw()
{
    if(cards_->size()<=0){
        cout<<"no more cards in deck"<<endl;
    }

    else{
        Cards *top_card = cards_->at(0);
        num_cards_deck_--;
        delete cards_->at(0);
        return *top_card;
    }

}

void Deck::DisplayDeck()
{
    for(int i= 0; i<cards_->size(); i++){
        cards_->at(i)->DisplayCard();
    }
}



//Hand class ------------------------------------------------
Hand::Hand(){
    cards_in_hand_ = new vector<Cards*>;
}

Hand::Hand(const Hand &hand){
    num_cards_hand_ = hand.num_cards_hand_;
    cards_in_hand_ = hand.cards_in_hand_;
}

Hand::~Hand(){

}

void Hand::AddCardToHand(Cards* card_)
{
    cards_in_hand_->push_back(card_);
}

int Hand::Exchange()
{

}

void Hand::DisplayHand()
{
    for(int i = 0; i<cards_in_hand_->size(); i++){
        cout<<"card #"<<i<<endl;
        cards_in_hand_->at(i)->DisplayCard();

    }
}