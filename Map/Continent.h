//
// Created by Giselle Martel on 2019-11-26.
//

#ifndef TEAMPROJECT_COMP345_CONTINENT_H
#define TEAMPROJECT_COMP345_CONTINENT_H

#include "Country.h"

#include <string>

using namespace std;
//Continent class ------------------------------------------------------------------------------------
class Continent{

private:
    string* continent_name_;
    string* color_;
    int continent_ID_;
    int army_value_;
    vector<Country*>* countries_in_continent_;

public:
    //Constructors
    Continent(string* in_continent_name, int army_value, int continent_id);
    Continent(const Continent &continent);
    ~Continent();

    //operator overloader
    Continent& operator=(const Continent &continent);

    //Setters --------------------------------------------------
    void SetContinentName(string* in_continent_name);
    void SetContinentID(int in_continent_ID);

    //Getters --------------------------------------------------
    string* GetContinentName() const;
    int GetContinentArmyValue() const;
    int GetContinentID() const;
    vector<Country*>* GetCountriesInContinent() const;

    //Methods -------------------------------------------------------
    void AddCountryToContinent(Country* country);
    void DisplayInfo() const;
};


#endif //TEAMPROJECT_COMP345_CONTINENT_H
