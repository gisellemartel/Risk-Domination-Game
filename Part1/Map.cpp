//
// Created by Giselle Martel on 2019-09-13.
//

#include "Map.h"
#include "Player.h"
#include <list>

using namespace std;

class map{
private:
    list <Continent> continents;

public:
    void addContinent(Continent continent){
        continents.push_front(continent);
    }


};

class Continent{
private:
    string continent_name;
    list <Country> countriesInContinent;

public:
    Continent(string continent){
        this->continent_name = continent;
    }

    void setContinentName(string continentName){
        this->continent_name = continentName;
    }

    string getContinentName(){
        return this->continent_name;
    }

    void addCountryToContinent(Country country){
        //need to add condition to check if country is already in any other continent
        countriesInContinent.push_back(country);
    }

};
class Country{
private:
    string country_name;
    Player country_owner;
    int numberOfArmies;
    list <Country> neighbors;
    Continent continent;

public:
    Country(string country_name){
        this->country_name = country_name;
        this->country_owner = null;
        this->numberOfArmies = 0;
    }

    void setCountryName(string country_name){
        this->country_name = country_name;
    }
    string getCountryName(){
        return this->country_name;
    }

    void setNumberOfArmies(int numberOfArmies){
        this->numberOfArmies = numberOfArmies;
    }

    int getNumberOfArmies(){
        return this->numberOfArmies;
    }

    void addNeighborCountry(Country neighbor){
        neighbors.push_front(neighbor);
    }

    bool isNeighbor(Country neighbor){

        return false;
    }

    void belongsToContinent(Continent continent){
        this->continent = continent;
    }

    Continent getContinent(){
        return this=>continent ;
    }

};
