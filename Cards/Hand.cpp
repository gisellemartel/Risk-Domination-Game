//
// Created by Giselle Martel on 2019-11-29.
//

#include "Hand.h"


// HAND class ----------------------------------------------------------------------------------------------------------
Hand::Hand(){
    cards_in_hand_ = new vector<Cards*>;
}


Hand::Hand(const Hand &hand) {
    *cards_in_hand_ = *hand.cards_in_hand_;

    for(int i = 0; i < hand.cards_in_hand_->size(); ++i) {
        (*cards_in_hand_)[i] = (*hand.cards_in_hand_)[i];
        delete (*hand.cards_in_hand_)[i];
        (*hand.cards_in_hand_)[i] = nullptr;
    }

    delete hand.cards_in_hand_;
}

Hand::~Hand() {

    for(Cards* card : *cards_in_hand_) {
        delete card;
        card = nullptr;
    }

    delete cards_in_hand_;
    cards_in_hand_ = nullptr;
}

Hand& Hand::operator=(const Hand &hand) {
   if(this != &hand) {
       *cards_in_hand_ = *hand.cards_in_hand_;

       for(int i = 0; i < hand.cards_in_hand_->size(); ++i) {
           (*cards_in_hand_)[i] = (*hand.cards_in_hand_)[i];

           delete (*hand.cards_in_hand_)[i];
           (*hand.cards_in_hand_)[i] = nullptr;
       }

       delete hand.cards_in_hand_;
   }
    return *this;
}

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
            DisplayHand();
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

    return 0;
}

int Hand::AutoExchange() {
    //condition #1
    if(!cards_in_hand_ || cards_in_hand_->size() < 3) {
        cout << "Not enough cards to exchange" << endl;
        return 0;
    }

    size_t card_1 = 0, card_2 = 0, card_3 = 0;
    bool valid_input = false;


    while (!valid_input) {
        DisplayHand();
        cout << "Pick 3 valid cards to exchange" << endl << endl;

        card_1 = Utility::GenerateRandomNumInRange(0, (int)cards_in_hand_->size() - 1);
        card_2 = Utility::GenerateRandomNumInRange(0, (int)cards_in_hand_->size() - 1);
        card_3 = Utility::GenerateRandomNumInRange(0, (int)cards_in_hand_->size() - 1);

        if (card_1 == card_2 || card_1 == card_3 || card_2 == card_3) {
            cout << "Invalid inputs. Pick 3 unique cards" << endl << endl;
            continue;
        }
        else {
            valid_input = true;
        }
    }

    if(AreThreeSame(cards_in_hand_->at(card_1), cards_in_hand_->at(card_2), cards_in_hand_->at(card_3))|| AreThreeDifferent(cards_in_hand_->at(card_1), cards_in_hand_->at(card_2), cards_in_hand_->at(card_3))) {
        cout << "Exchanging Cards" << endl;
        cards_in_hand_->erase(cards_in_hand_->begin() + Max(card_1, card_2, card_3));
        cards_in_hand_->erase(cards_in_hand_->begin() + Mid(card_1, card_2, card_3));
        cards_in_hand_->erase(cards_in_hand_->begin() + Min(card_1, card_2, card_3));

        return AcquireArmy(exchanges_done++);
    }

    return 0;
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
    return (exchanges_done * 5 + 5);
}

bool Hand::AreThreeSame(Cards* card_1, Cards* card_2, Cards* card_3) {
    if(!card_1 || !card_2 || !card_3) {
        return false;
    }
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
        if(cards_in_hand_->at(i)) {
            cards_in_hand_->at(i)->DisplayCard();
        }
    }
}