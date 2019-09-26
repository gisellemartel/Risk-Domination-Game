//
// Created by Giselle Martel on 2019-09-13.
//

#ifndef TEAMPROJECT_COMP345_MAP_H
#define TEAMPROJECT_COMP345_MAP_H


#include "Part4/Player.h"
#include <list>
#include <string>

using namespace std;

//Country class ------------------------------------------------------------------------------------
class Country{

private:
    string* country_name;
    Player* country_owner;
    int number_of_armies;
    list<Country*> neighbors;
    Continent* continent;

public:
    //Constructor using initializer list
    Country(string* in_country_name) :
        country_name(in_country_name),
        country_owner(nullptr),
        number_of_armies(0)
        {}

    //Setters --------------------------------------------------

    void setCountryName(string* in_country_name){ country_name = in_country_name; }

    void setNumberOfArmies(int in_number_of_armies){ number_of_armies = in_number_of_armies; }

    //Getters --------------------------------------------------

    const string* getCountryName() const { return country_name; }

    const int getNumberOfArmies() const { return number_of_armies; }

    const Continent* getContinent() const { return continent; }

    //Methods -------------------------------------------------------

    void addNeighborCountry(const Country* neighbor);

    bool isNeighbor(const Country* neighbor);

    bool belongsToContinent(const Continent* continent);
};


//Continent class ------------------------------------------------------------------------------------
class Continent{
private:
    string* continent_name;
    list<Country*> countries_in_continent;

public:
    //Constructor using initializer list
    Continent(string* in_continent_name)
        : continent_name (in_continent_name)
        {}

    //Setters --------------------------------------------------
    void setContinentName(string* in_continent_name) { continent_name = in_continent_name; }


    //Getters --------------------------------------------------
    const string* getContinentName() const { return continent_name; }


    //Methods -------------------------------------------------------
    void addCountryToContinent(Country* country);
};


//Map class ------------------------------------------------------------------------------------
class Map
{
private:
    list<Continent*> continents;

public:

    //Methods -------------------------------------------------------
    void addContinent(Continent* continent);

};
#endif //TEAMPROJECT_COMP345_MAP_H


