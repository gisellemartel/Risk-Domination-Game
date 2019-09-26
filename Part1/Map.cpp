//
// Created by Giselle Martel on 2019-09-13.
//

#include "Map.h"
#include "Player.h"

using namespace std;

//Map class method implementations ----------------------
void Map::AddContinent(Continent* continent) {
    continents.push_front(continent);
}


//Country class method implementations ----------------------
void Country::AddNeighborCountry(const Country* neighbor) {
    neighbors.push_front(neighbor);
}

bool Country::IsNeighbor(const Country* neighbor) {
    return false;
}

bool Country::BelongsToContinent(const Continent* continent) {
    return false;
}


//Continent class method implementations ----------------------
void Continent::AddCountryToContinent(string* country){
    //need to add condition to check if country is already in any other continent
    countries_in_continent_.push_back(country);
}

