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
    cout << "\nTesting Cards Driver...\nCreating 12 cards for deck:\n";
    Deck* deck = new Deck();
    deck->CreateDeck(12);
    deck->DisplayDeck();
    cout << "\nCurrent number cards in deck: " << deck->GetNumberOfCardsInDeck() << "\n\nDrawing a card from deck:";
    deck->Draw();
    cout << "\nCurrent number cards in deck: " << deck->GetNumberOfCardsInDeck() << endl << endl;
    deck->DisplayDeck();

    cout << "\n\nCreating Hand of cards by drawing from deck:";
    Hand* hand = new Hand();
    hand->AddCardToHand(deck->Draw());
    hand->AddCardToHand(deck->Draw());
    hand->AddCardToHand(deck->Draw());
    hand->AddCardToHand(deck->Draw());
    hand->AddCardToHand(deck->Draw());

    cout << "\n\nCurrent number cards in deck after draw: " << deck->GetNumberOfCardsInDeck() << "\n\nContents of deck:\n";
    deck->DisplayDeck();

    cout << "\nContents of Hand: \n";
    hand->DisplayHand();

    cout << "\n\nAttempting to exchange card 0: " << hand->Exchange(0) << "\nHere is the result:\n\n";
    hand->DisplayHand();

    return 0;
}
