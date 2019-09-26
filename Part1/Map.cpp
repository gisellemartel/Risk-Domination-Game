//
// Created by Giselle Martel on 2019-09-13.
//

#include "Map.h"
#include "Player.h"

using namespace std;

//Map class method implementations ----------------------
void Map::addContinent(Continent* continent) {
    continents.push_front(continent);
}


//Country class method implementations ----------------------
void Country::addNeighborCountry(const Country* neighbor) {
    neighbors.push_front(neighbor);
}

bool Country::isNeighbor(const Country* neighbor) {
    return false;
}

bool Country::belongsToContinent(const Continent* continent) {
    return false;
}

//Continent class method implementations ----------------------
void Continent::addCountryToContinent(Country* country){
    //need to add condition to check if country is already in any other continent
    countriesInContinent.push_back(country);
}

