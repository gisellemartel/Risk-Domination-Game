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
    cout << "Testing Map Driver" << endl << endl;
    Map* america = new Map("America map");

    america->AddContinentToMap(new Continent("North America", 5, 1));
    america->AddContinentToMap(new Continent("South America", 2, 2));
    america->AddContinentToMap(new Continent("Europe", 5, 3));

    cout << "Displaying Continents of Map" << endl;
    america->DisplayContinents();

    america->AddCountryToMap(new Country(1,"Alaska", 1));
    america->AddCountryToMap(new Country(2, "Alberta", 1));
    america->AddCountryToMap(new Country(3, "Brazil", 2));
    america->AddCountryToMap(new Country(4, "British Columbia", 1));
    america->AddCountryToMap(new Country(5, "Portugal", 3));

    cout << "Displaying Countries of Map" << endl;
    america->DisplayCountries();

    america->CreateAdjacencyMatrix();
    america->SetTwoCountriesAsNeighbours(true, 0, 1);
    america->SetTwoCountriesAsNeighbours(false, 0, 2);
    america->SetTwoCountriesAsNeighbours(false, 0, 4);
    america->SetTwoCountriesAsNeighbours(false, 1, 2);
    america->SetTwoCountriesAsNeighbours(false, 1, 4);
    america->SetTwoCountriesAsNeighbours(false, 2, 4);
    america->SetTwoCountriesAsNeighbours(false, 3, 2);
    america->SetTwoCountriesAsNeighbours(true, 3, 1);
    america->SetTwoCountriesAsNeighbours(true, 3, 0);
    america->SetTwoCountriesAsNeighbours( false, 3, 4);

    cout << "Displaying county nodes and edges:" << endl;
    america->DisplayAdjacencyMatrix();

    delete america;
}
