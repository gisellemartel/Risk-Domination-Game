/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include <iostream>
#include <iomanip>

using namespace std;

#include "Player.h"

class Country;

int main()
{
    cout << "\nTesting Player Driver" << endl;
    string name = "Canada";

    Map* test_map = new Map("Test map");

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

    //Armies in each Country
    test_map->GetCountryById(1)->SetNumberOfArmies(5);
    test_map->GetCountryById(2)->SetNumberOfArmies(9);
    test_map->GetCountryById(4)->SetNumberOfArmies(4);

    test_map = nullptr;
    delete test_map;

    return 0;
}
