
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

