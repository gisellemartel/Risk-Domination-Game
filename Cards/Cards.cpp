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

const int Deck::GetNumberOfCardsInDeck() const {
    return cards_->size();
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

Cards* Deck::Draw()
{

    if(cards_->size()<=0){
        cout<<"no more cards in deck"<<endl;
        return nullptr;
    }

    else{

        srand(time (NULL));
        int random_card = rand() % cards_->size();

        Cards* top_card = cards_->at(random_card);

        cards_->erase(cards_->begin()+ random_card);

        return top_card;
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
    num_cards_hand_ = 0;
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
    if(cards_in_hand_->size()<3){
        cout<<"Not enough cards to exchange"<<endl;
        return 0;
    }

    int card_1, card_2, card_3;
    bool valid_input = false;

    cout<<"Pick 3 valid cards to exchange"<<endl
    <<"Card #1: ";
    cin >> card_1;
    cout <<"Card #2: ";
    cin >> card_2;
    cout <<"Card #3: ";
    cin >> card_3;
    cout<<"picked card # " << card_1<<endl
        <<"picked card # " << card_2<<endl
        <<"picked card # " << card_3<<endl;

    if
    (
            AreThreeSame(cards_in_hand_->at(card_1), cards_in_hand_->at(card_2), cards_in_hand_->at(card_3))
         || AreThreeDifferent(cards_in_hand_->at(card_1), cards_in_hand_->at(card_2), cards_in_hand_->at(card_3))
     )
        cout<<"You get more armies"<<endl;
}

bool Hand::AreThreeSame(Cards* card_1, Cards* card_2, Cards* card_3)
{
    return
    (
        card_1->GetCardType() == card_2->GetCardType() &&
        card_2->GetCardType() == card_3->GetCardType()
    );

}

bool Hand::AreThreeDifferent(Cards *card_1, Cards *card_2, Cards *card_3)
{
    return
            (
            card_1->GetCardType() != card_2->GetCardType() &&
            card_2->GetCardType() != card_3->GetCardType() &&
            card_1->GetCardType() != card_3->GetCardType()
            );
}

void Hand::DisplayHand()
{
    for(int i = 0; i<cards_in_hand_->size(); i++){
        cout<<"card #"<<i<<" ";
        cards_in_hand_->at(i)->DisplayCard();

    }
}