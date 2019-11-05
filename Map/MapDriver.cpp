/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
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
    test_map->SetTwoCountriesAsNeighbours(true, 1, 2);
    test_map->SetTwoCountriesAsNeighbours(true, 1, 3);
    test_map->SetTwoCountriesAsNeighbours(true, 1, 4);


    cout << "----------------------------------------------------" << endl;
    cout << "\nDisplaying all country nodes and edges:\n" << endl;
    test_map->DisplayAdjacencyMatrix();


    cout << "----------------------------------------------------" << endl;
    cout << "\nDisplaying comparison between country nodes and edges:" << endl;

    cout << "\nAre Canada (country 1) and Brazil (country 3) neighbours?\nResult: ";
    cout << (test_map->AreCountriesNeighbors(test_map->GetCountryById(1), test_map->GetCountryById(3))? "true\n" : "false\n");


    cout << "\nAre Mexico (country 4) and United States (country 2) neighbours?\nResult: ";
    cout << (test_map->AreCountriesNeighbors(test_map->GetCountryById(4), test_map->GetCountryById(2)) ? "true\n" : "false\n");

    cout << "\nAre Mexico (country 4) and Portugal (country 5) neighbours?\nResult: ";
    cout << (test_map->AreCountriesNeighbors(test_map->GetCountryById(4), test_map->GetCountryById(5)) ? "true\n" : "false\n");

    cout << "\n----------------------------------------------------" << endl;
    cout << "Testing that graph is connected:\n\n";
    test_map->DisplayGraphTraversal(test_map->GetCountryById(1));

    test_map = nullptr;
    delete test_map;
}
