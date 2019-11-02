/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <iostream>
#include <iomanip>

using namespace std;

#include "Player.h"
#include "../Cards/Cards.h"

class Country;

int main()
{
    cout << "\nTesting Player Driver" << endl;
    string name = "Canada";

    Player* new_player = new Player("New player");

    //Assignment2/task6
   // Map* test_map = new Map("Test Map");
   // test_map->AddCountryToMap(1,"Canada", 1, 0, 0);
   // test_map->AddCountryToMap(2, "United States", 1, 0, 0);
    //test_map->AddCountryToMap(3, "Mexico", 1, 0, 0);

   // SetTwoCountriesAsNeighbours(bool value, int country_index, int border_index);



    //Player has Countries
    new_player->AddCountryToCollection(new Country(1, new string("Canada"), 1));
    new_player->AddCountryToCollection(new Country(2, new string("US"), 1));
    new_player->AddCountryToCollection(new Country(3, new string("Mexico"), 1));
    cout << "\nPlayer owns collection of following countries: " << endl;
    for(Country* country : *new_player->GetPlayersCountries()) {
        country->SetNumberOfArmies(9);//set number of armies in country for Assignment6/Task6
        cout << *country->GetCountryName() << " (" << country->GetNumberOfArmies() << " armies)" << endl;
    }

    //Player has Cards
    new_player->AddCardToCollection(new Cards("calvary"));
    new_player->AddCardToCollection(new Cards("infantry"));
    new_player->AddCardToCollection(new Cards("artillery"));
    cout << "\nPlayer owns collection of following cards: " << endl;

    for(size_t i = 0; i < new_player->GetPlayersCards()->GetNumberOfCardsInHand(); ++i) {
        cout << "card " << (i + 1) << ": ";
        new_player->GetPlayersCards()->DisplayHand();
    }

    //Player has Dice Rolling mechanism
    cout << "\nPlayer owns dice rolling mechanism and can roll 2 dice: " << endl;
    new_player->SetPlayerDice(new Dice);
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
