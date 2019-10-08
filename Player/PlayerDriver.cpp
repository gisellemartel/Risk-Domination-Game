/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include <iostream>
#include <iomanip>

using namespace std;

#include "Player.h"
#include "../Cards/Cards.h"
#include "../Map/Map.h"

class Country;

int main()
{
    cout << "\nTesting Player Driver" << endl;
    string name = "Canada";

    Player* new_player = new Player("New player");

    //Countries
    new_player->AddCountryToCollection(new Country(1, "Canada", 1));
    new_player->AddCountryToCollection(new Country(2, "US", 1));
    new_player->AddCountryToCollection(new Country(3, "Mexico", 1));
    cout << "\nPlayer owns collection of following countries: " << endl;
    for(int i = 0; i < new_player->GetPlayersCountries()->size(); ++i) {
        cout << (*new_player->GetPlayersCountries())[i]->GetCountryName() << endl;
    }

    new_player->AddCardToCollection(new Cards("calvary"));
    new_player->AddCardToCollection(new Cards("infantry"));
    new_player->AddCardToCollection(new Cards("artillery"));
    cout << "\nPlayer owns collection of following cards: " << endl;

    for(int i = 0; i < new_player->GetPlayersCards()->size(); ++i) {
        cout << "card " << (i + 1) << ": ";
        (*new_player->GetPlayersCards())[i]->DisplayCard();
    }

    //Dice
    cout << "\nPlayer own dice  and can roll 2 of them: " << endl;
    vector<int> dice_rolls = new_player->GetPlayerDice()->Roll(2);
    cout << "Dice rolled:\n";
    for (int & dice_roll : dice_rolls) {
        cout << ' ' << dice_roll << endl;//print dice rolls
    }
    cout << "Total Rolls: " << new_player->GetPlayerDice()->GetTotalRolls() << endl;

    //Methods
    cout << "\nPlayer implements Attack, Fortify, and Reinforce methods:" << endl;
    new_player->Attack();
    new_player->Fortify();
    new_player->Reinforce();

    delete new_player;

    return 0;
}
