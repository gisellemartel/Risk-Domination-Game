/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */


#include <iostream>
#include "Cards.h"

using namespace std;


int main()
{
    Deck* deck = new Deck();
    deck->CreateDeck(12);
    deck->Draw();
    deck->DisplayDeck();
    cout<<"current cards in deck: " <<deck->GetNumberOfCardsInDeck()<<endl;

    Hand* hand = new Hand();

    hand->AddCardToHand(deck->Draw());
    hand->AddCardToHand(deck->Draw());
    hand->AddCardToHand(deck->Draw());
    hand->AddCardToHand(deck->Draw());
    hand->AddCardToHand(deck->Draw());
//    hand->AddCardToHand(new Cards("infantry"));
//    hand->AddCardToHand(new Cards("infantry"));
//    hand->AddCardToHand(new Cards("infantry"));

    hand->DisplayHand();
    cout<<hand->Exchange(0)<<endl;
    hand->DisplayHand();



    return 0;
}
