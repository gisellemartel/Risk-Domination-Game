
#include "Deck.h"

// DECK class ----------------------------------------------------------------------------------------------------------
Deck::Deck(const Deck& deck) {
    num_exchanges = deck.num_exchanges;
    num_cards_deck_ = deck.num_cards_deck_;
    *cards_ = *deck.cards_;

    for(int i = 0; i < deck.cards_->size(); ++i) {
        (*cards_)[i] = (*deck.cards_)[i];
        delete (*deck.cards_)[i];
        (*deck.cards_)[i] = nullptr;
    }

    delete deck.cards_;
}

Deck::Deck() {
    num_exchanges = 0;
    cards_ = new vector<Cards*>;
    num_cards_deck_ = 0;
}

Deck::~Deck() {
    for(Cards* card : *cards_) {
        delete card;
        card = nullptr;
    }

    delete cards_;
    cards_ = nullptr;
}

Deck& Deck::operator=(const Deck &deck) {
   if(this != &deck) {
       num_exchanges = deck.num_exchanges;
       num_cards_deck_ = deck.num_cards_deck_;
       *cards_ = *deck.cards_;

       for(int i = 0; i < deck.cards_->size(); ++i) {
           (*cards_)[i] = (*deck.cards_)[i];
           delete (*deck.cards_)[i];
           (*deck.cards_)[i] = nullptr;
       }

       delete deck.cards_;
   }

    return *this;
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