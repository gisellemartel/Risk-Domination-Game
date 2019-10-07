/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include <iostream>
#include <string>

#include "Map.h"

using namespace std;

int main()
{
    cout << "\nTesting Map Driver" << endl << endl;
    Map* test_map = new Map("Test map");

    test_map->AddContinentToMap("North America", 5, 1);
    test_map->AddContinentToMap("South America", 2, 2);
    test_map->AddContinentToMap("Europe", 5, 3);

    cout << "----------------------------------------------------" << endl;
    cout << "Displaying Continents of Map:\n" << endl;
    test_map->DisplayContinents();

    test_map->AddCountryToMap(1,"Alaska", 1, 0, 0);
    test_map->AddCountryToMap(2, "Alberta", 1, 0, 0);
    test_map->AddCountryToMap(3, "Brazil", 2, 0, 0);
    test_map->AddCountryToMap(4, "British Columbia", 1, 0, 0);
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
    test_map->SetTwoCountriesAsNeighbours(true, 3, 0);
    test_map->SetTwoCountriesAsNeighbours( false, 3, 4);

    cout << "----------------------------------------------------" << endl;
    cout << "\nDisplaying all country nodes and edges:\n" << endl;
    test_map->DisplayAdjacencyMatrix();


    cout << "----------------------------------------------------" << endl;
    cout << "\nDisplaying comparison between country nodes and edges:" << endl;

    cout << "\nAre Alaska (country 1) and Brazil (country 3) neighbours?\nResult: ";
    cout << (test_map->AreCountriesNeighbors(test_map->GetCountryById(1), test_map->GetCountryById(3))? "true\n" : "false\n");


    cout << "\nAre British Columbia (country 4) and Alberta (country 2) neighbours?\nResult: ";
    cout << (test_map->AreCountriesNeighbors(test_map->GetCountryById(4), test_map->GetCountryById(2)) ? "true\n" : "false\n");

    cout << "\nAre British Columbia (country 4) and Portugal (country 5) neighbours?\nResult: ";
    cout << (test_map->AreCountriesNeighbors(test_map->GetCountryById(4), test_map->GetCountryById(5)) ? "true\n" : "false\n");

    delete test_map;
}
