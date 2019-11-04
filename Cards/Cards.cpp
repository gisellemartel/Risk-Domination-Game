/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include "Cards.h"
#include <iostream>
#include <utility>
#include <ctime>
using namespace std;


// CARDS class ---------------------------------------------------------------------------------------------------------

//Constructors
Cards::Cards(const Cards& cards) {
    type_ = cards.type_;
}

Cards::Cards(const string& type) {
    type_ = type;
}

Cards::~Cards() = default;

Cards& Cards::operator=(const Cards& cards) = default;

void Cards::SetCardType(string& card_type) {
    type_ = card_type;
}

string Cards::GetCardType() const {
    return type_;
}

void Cards::DisplayCard() {
    cout << "Card Type: " << type_ << endl;
}

// END CARDS class -----------------------------------------------------------------------------------------------------


// DECK class ----------------------------------------------------------------------------------------------------------
Deck::Deck(const Deck& deck) {
    num_exchanges = deck.num_exchanges;
    num_cards_deck_ = deck.num_cards_deck_;
    cards_ = deck.cards_;
}

Deck::Deck() {
    num_exchanges = 0;
    cards_ = new vector<Cards*>;
    num_cards_deck_ = 0;
}

Deck::~Deck() = default;

int Deck::GetNumExchanges() const {
    return num_exchanges;
}

size_t Deck::GetNumberOfCardsInDeck() const {
    return cards_->size();
}

void Deck::CreateDeck(int num_cards) {

    int artillery_cards = num_cards / 3;
    int cavalry_cards = num_cards / 3;
    int infantry_cards = num_cards - (artillery_cards + cavalry_cards);

    for(int i = 0; i < artillery_cards; ++i) {
        cards_->push_back(new Cards("artillery"));
        ++num_cards_deck_;
    }

    for(int i = 0; i<  cavalry_cards; ++i) {
        cards_->push_back(new Cards("cavalry"));
        ++num_cards_deck_;
    }

    for(int i = 0; i < infantry_cards; ++i){
        cards_->push_back(new Cards("infantry"));
        ++num_cards_deck_;
    }

}

Cards* Deck::Draw() {

    if(cards_->empty()) {
        cout << "no more cards in deck" << endl;
        return nullptr;
    }

    else {

        srand(time (nullptr));
        size_t random_card = rand() % cards_->size();

        Cards* top_card = cards_->at(random_card);

        cards_->erase(cards_->begin()+ random_card);

        return top_card;
    }

}

void Deck::DisplayDeck() {
    for(Cards* card : *cards_){
        card->DisplayCard();
    }
}

// END DECK class ------------------------------------------------------------------------------------------------------


// HAND class ----------------------------------------------------------------------------------------------------------
Hand::Hand(){
    cards_in_hand_ = new vector<Cards*>;
}

Hand::Hand(const Hand &hand) {
    cards_in_hand_ = hand.cards_in_hand_;
}

Hand::~Hand()= default;

size_t Hand::GetNumberOfCardsInHand() const {
    return cards_in_hand_->size();
}

void Hand::AddCardToHand(Cards* card_) {
    cards_in_hand_->push_back(card_);
}
// 3 conditions to verify:
// 1-(Minimum 3 cards in hand)
// 2-(Inputs for choices of cards in hand are valid and unique)
// 3-(Cards are 3 same type or 3 different type)
int Hand::Exchange() {
    static int exchanges_done = 0;
    //condition #1
    if(cards_in_hand_->size() < 3) {
        cout << "Not enough cards to exchange" << endl;
        return 0;
    }
    string user_response;
    if(cards_in_hand_->size() < 5){
        cout<< "Do you wish to exchange cards? Input 'y' to exchange, else no: ";
        cin >> user_response;
        if(user_response != "y")
            return 0;
    }
    size_t card_1 = 0, card_2 = 0, card_3 = 0;
    bool valid_input = false;
    bool valid_cards = false;

    while(!valid_cards) {

        //condition #2
        while (!valid_input) {
            cout << "Pick 3 valid cards to exchange" << endl << endl;

            card_1 = InputCard();
            card_2 = InputCard();
            card_3 = InputCard();

            if (card_1 == card_2 || card_1 == card_3 || card_2 == card_3) {
                cout << "Invalid inputs. Pick 3 unique cards" << endl << endl;
                continue;
            }
            else {
                valid_input = true;
            }

        }

        //condition #3
        if(AreThreeSame(cards_in_hand_->at(card_1), cards_in_hand_->at(card_2), cards_in_hand_->at(card_3))|| AreThreeDifferent(cards_in_hand_->at(card_1), cards_in_hand_->at(card_2), cards_in_hand_->at(card_3))) {
            cout << "Exchanging Cards" << endl;
            cards_in_hand_->erase(cards_in_hand_->begin() + Max(card_1, card_2, card_3));
            cards_in_hand_->erase(cards_in_hand_->begin() + Mid(card_1, card_2, card_3));
            cards_in_hand_->erase(cards_in_hand_->begin() + Min(card_1, card_2, card_3));

            return AcquireArmy(exchanges_done++);
        }
        else {
            cout << "Cards are invalid for exchange. Input y to retry: ";
            cin >> user_response;
            if(user_response != "y") {
                return 0;
            }
            else {
                valid_input = false; //restart condition #2
            }
        }
    }
}

size_t Hand::InputCard() {
    size_t card_value;
    cout<<"Pick a card#: ";
    cin>> card_value;
    //loops until input is int and within range {
    while (cin.fail() || ValidateInput(card_value)) {
        cout<<"Invalid input. Pick a valid card number: ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> card_value;
    }
    cout << "You picked card #" << card_value << endl << endl;

    return card_value;
}

bool Hand::ValidateInput(size_t card_index) {
    return (card_index < 0 || card_index > cards_in_hand_->size()-1);
}

int Hand::AcquireArmy(int exchanges_done) {
    return (exchanges_done*5 + 5);
}

bool Hand::AreThreeSame(Cards* card_1, Cards* card_2, Cards* card_3) {
    return
            (
                    card_1->GetCardType() == card_2->GetCardType() &&
                    card_2->GetCardType() == card_3->GetCardType()
            );

}

bool Hand::AreThreeDifferent(Cards *card_1, Cards *card_2, Cards *card_3) {
    return
            (
                    card_1->GetCardType() != card_2->GetCardType() &&
                    card_2->GetCardType() != card_3->GetCardType() &&
                    card_1->GetCardType() != card_3->GetCardType()
            );
}

size_t Hand::Max(size_t index_1, size_t index_2, size_t index_3) {
    if(index_1> index_2 && index_1 > index_3)
        return index_1;
    if(index_2> index_1 && index_2 > index_3)
        return index_2;
    return index_3;
}

size_t Hand::Mid(size_t index_1, size_t index_2, size_t index_3) {
    if(index_1 > index_2 && index_1 < index_3)
        return index_1;
    if(index_2 > index_1 && index_2 < index_3)
        return index_2;
    return index_3;
}

size_t Hand::Min(size_t index_1, size_t index_2, size_t index_3) {
    if(index_1 < index_2 && index_1 < index_3)
        return index_1;
    if(index_2 < index_1 && index_2 < index_3)
        return index_2;
    return index_3;
}

void Hand::DisplayHand() {
    for(size_t i = 0; i < cards_in_hand_->size(); ++i){
        cout << "card #" << i << ": ";
        cards_in_hand_->at(i)->DisplayCard();
    }
}