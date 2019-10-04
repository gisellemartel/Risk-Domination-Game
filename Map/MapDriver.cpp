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


    Continent* north = new Continent("North America", 5);
    north->DisplayInfo();

    Country* alaska = new Country(0, "Alaska", 0);
    alaska->DisplayInfo();

    Country* alberta = new Country(1, "Alberta", 0);
    alberta->DisplayInfo();

    Country* central_america = new Country(2, "Central America", 0);
    central_america->DisplayInfo();

    Country* eastern_united_states = new Country(3, "Eastern United States", 0);
    eastern_united_states->DisplayInfo();

    Country* greenland = new Country(4, "Greenland", 0);
    greenland->DisplayInfo();

    Country* northwest_territory = new Country(5, "Northwest Territory", 0);
    northwest_territory->DisplayInfo();

    Country* ontario = new Country(6, "Ontario", 0);
    ontario->DisplayInfo();

    Country* quebec = new Country(7, "Quebec", 0);
    quebec->DisplayInfo();

    Country* western_united_states = new Country(8, "Western United States", 0);
    western_united_states->DisplayInfo();


    Map* na_map = new Map("North American map", 9, 1);
    delete na_map;
    cout << "Map Driver" << endl;
}
