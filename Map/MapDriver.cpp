/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include "Map.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{



    Map* america = new Map("America map", 2, 5);
    //name, army value, id
    america->AddContinentToMap("North America", 5, 1);
    america->AddContinentToMap("South America", 2, 2);
    america->AddContinentToMap("Europe", 5, 3);
    america->DisplayContinents();

    america->AddCountryToMap(1,"Alaska", 1);
    america->AddCountryToMap(2, "Alberta", 1);
    america->AddCountryToMap(3, "Central America", 1);
    america->DisplayCountries();

    america->DisplayEdges();
//    cout<<endl;
//
//    vector<int> *border1 = new vector<int>;
//
//
//    border1->push_back(1);
//    border1->push_back(2);
//    border1->push_back(3);
//
//    america->AddCountryEdges(border1);
//
//    america->DisplayEdges();

    delete america;
    cout << "Map Driver" << endl;
}
