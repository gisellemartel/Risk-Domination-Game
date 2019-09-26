//
// Created by Giselle Martel on 2019-09-13.
//

#ifndef TEAMPROJECT_COMP345_MAP_H
#define TEAMPROJECT_COMP345_MAP_H


#include "../Part4/Player.h"
#include <list>
#include <string>
#include <iostream>

using namespace std;


//Continent class ------------------------------------------------------------------------------------
class Continent{
private:
    string* continent_name_;
    list<string*> countries_in_continent_;

public:
    //Constructor using initializer list
    Continent(string* in_continent_name)
        : continent_name_ (in_continent_name)
        {}

    //Setters --------------------------------------------------
    void SetContinentName(string* in_continent_name) { continent_name_ = in_continent_name; }


    //Getters --------------------------------------------------
    const string* GetContinentName() const { return continent_name_; }


    //Methods -------------------------------------------------------
    void AddCountryToContinent(string* country);
};

//Country class ------------------------------------------------------------------------------------
class Country{

private:
    string* country_name_;
    //Player* country_owner_;
    int number_of_armies_;
    list<Country*> neighbors_;
    Continent* continent_;

public:
    //Constructor using initializer list
    Country(string* in_country_name) :
            country_name_(in_country_name),
            //country_owner_(nullptr),
            number_of_armies_(0)
    {}

    //Setters --------------------------------------------------

    void SetCountryName(string* in_country_name){ country_name_ = in_country_name; }

    void SetNumberOfArmies(int in_number_of_armies){ number_of_armies_ = in_number_of_armies; }

    //Getters --------------------------------------------------

    const string* GetCountryName() const { return country_name_; }

    const int GetNumberOfArmies() const { return number_of_armies_; }

    const Continent* GetContinent() const { return continent_; }

    //Methods -------------------------------------------------------

    void AddNeighborCountry(const Country* neighbor);

    bool IsNeighbor(const Country* neighbor);

    bool BelongsToContinent(const Continent* continent);
};

//Map class ------------------------------------------------------------------------------------
class Map {
private:
    list<Continent *> continents;

public:
    Map(){
        cout << "Instantiating new map" << endl;
    }

    //Methods -------------------------------------------------------
    void AddContinent(Continent* continent);

};
#endif //TEAMPROJECT_COMP345_MAP_H


