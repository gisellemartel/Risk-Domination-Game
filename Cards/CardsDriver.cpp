/**
 * Assignment #1 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <iostream>
#include "Cards.h"

using namespace std;


int main()
{
    Deck* deck = new Deck();
    deck->CreateDeck(12);
    deck->DisplayDeck();
    cout<<"current cards in deck: " <<deck->GetNumberOfCardsInDeck()<<endl;

    cout<<endl<<"Cards in hands test"<<endl<<endl;

    Hand* hand = new Hand();
    hand->AddCardToHand(new Cards("infantry"));
    hand->AddCardToHand(new Cards("infantry"));
    hand->AddCardToHand(new Cards("artillery"));
    hand->AddCardToHand(new Cards("artillery"));
    hand->AddCardToHand(new Cards("cavalry"));

    hand->DisplayHand();
    hand->Exchange();
    hand->DisplayHand();

    cout << "Cards Driver" << endl;
    return 0;
}
