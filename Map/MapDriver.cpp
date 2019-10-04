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



    Map* america = new Map("America map", 9, 5);
    //name, army value, id
    america->AddContinentToMap("North America", 4, 1);
    america->AddContinentToMap("South America", 3, 2);
    america->DisplayContinents();

    america->AddCountryToMap();

    delete america;
    cout << "Map Driver" << endl;
}
