/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include <iostream>
using namespace std;

#include "Player.h"
#include "../Map/Map.h"

int main()
{
    cout << "Executing Player Driver" << endl;
    vector<Country*>* countries = new vector<Country*>;
    string name = "Canada";
//    Country* country = new Country(name);
//    countries->push_back(country);
    Player* newPlayer = new Player("New player", countries, false);
    //delete country;
    //delete countries;
    delete newPlayer;


    return 0;
}
