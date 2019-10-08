/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */


#include <iostream>
#include "Cards.h"

using namespace std;


int main()
{
    Deck* adeck = new Deck();
    adeck->CreateDeck(12);
    adeck->DisplayDeck();
    cout<<"current cards in deck: " <<adeck->GetNumberOfCardsInDeck()<<endl;

    cout << "Cards Driver" << endl;
    return 0;
}
