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

    auto* new_player = new Player("New player");
    auto* test_map = new Map("Test map");

    test_map->AddContinentToMap("North America", 5, 1);
    test_map->AddContinentToMap("South America", 2, 2);
    test_map->AddContinentToMap("Europe", 5, 3);

    cout << "----------------------------------------------------" << endl;
    cout << "Displaying Continents of Map:\n" << endl;
    test_map->DisplayContinents();

    test_map->AddCountryToMap(1,"Canada", 1, 0, 0);
    test_map->AddCountryToMap(2, "United States", 1, 0, 0);
    test_map->AddCountryToMap(3, "Brazil", 2, 0, 0);
    test_map->AddCountryToMap(4, "Mexico", 1, 0, 0);
    test_map->AddCountryToMap(5, "Portugal", 3, 0, 0);

    cout << "----------------------------------------------------" << endl;
    cout << "\nDisplaying Countries of Map:\n" << endl;
    test_map->DisplayCountries();

    test_map->CreateAdjacencyMatrix();
    test_map->SetTwoCountriesAsNeighbours(true, 0, 1);
    test_map->SetTwoCountriesAsNeighbours(false, 0, 2);
    test_map->SetTwoCountriesAsNeighbours(false, 0, 4);
    test_map->SetTwoCountriesAsNeighbours(false, 1, 2);
    test_map->SetTwoCountriesAsNeighbours(false, 1, 4);
    test_map->SetTwoCountriesAsNeighbours(false, 2, 4);
    test_map->SetTwoCountriesAsNeighbours(false, 3, 2);
    test_map->SetTwoCountriesAsNeighbours(true, 3, 1);
    test_map->SetTwoCountriesAsNeighbours(false, 3, 0);
    test_map->SetTwoCountriesAsNeighbours( false, 3, 4);

    //Player has Countries
    new_player->AddCountryToCollection(test_map->GetCountryById(1));
    new_player->AddCountryToCollection(test_map->GetCountryById(2));
    new_player->AddCountryToCollection(test_map->GetCountryById(4));

    //Armies in each Country
    test_map->GetCountryById(1)->SetNumberOfArmies(5);
    test_map->GetCountryById(2)->SetNumberOfArmies(9);
    test_map->GetCountryById(4)->SetNumberOfArmies(4);

    cout << "\nPlayer owns collection of following countries: " << endl;
    for(Country* country : *new_player->GetPlayersCountries()) {
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
