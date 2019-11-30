/**
 * Assignment #4 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include "Cards.h"

// CARDS class ---------------------------------------------------------------------------------------------------------


Cards::Cards(const string& type) {
    type_ = type;
}

string Cards::GetCardType() const {
    return type_;
}

void Cards::DisplayCard() {
    cout << "Card Type: " << type_ << endl;
}

// END CARDS class -----------------------------------------------------------------------------------------------------

