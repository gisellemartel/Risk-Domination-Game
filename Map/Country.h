//
// Created by Giselle Martel on 2019-11-26.
//

#ifndef TEAMPROJECT_COMP345_COUNTRY_H
#define TEAMPROJECT_COMP345_COUNTRY_H

#include "Map.h"
#include "../Player/Player.h"

#include <string>

using namespace std;

class Player;
class Continent;
class Map;


//Country class ------------------------------------------------------------------------------------
class Country{

private:
    string* country_name_;
    int continent_ID_;
    int country_ID_;
    int number_of_armies_;
    int coordinate_x_;
    int coordinate_y_;
    Player* country_owner_;
    Continent* continent_;

public:
    //Constructors
    Country(int country_ID, string* country_name, int continent_ID);
    Country(int country_ID, string* country_name, int continent_ID, int coordinate_x, int coordinate_y);
    Country(const Country &country);
    ~Country();

    //operator overloader
    Country& operator=(const Country &country);
    bool operator==(const Country &country);

    //Setters --------------------------------------------------
    void SetCountryName(string* in_country_name);
    void SetNumberOfArmies(int in_number_of_armies);
    void SetCountryOwner(Player* player);
    void SetContinent(Continent* continent);

    //Getters --------------------------------------------------
    string* GetCountryName() const;
    int GetCountryID() const;
    int GetNumberOfArmies() const;
    int GetContinentID() const;
    Player* GetCountryOwner() const;
    string GetDisplayInfo() const;

    //Methods -------------------------------------------------------
    void AddArmyToCountry();
    void RemoveArmiesFromCountry(int num_armies_to_remove);
    void DisplayInfo() const;

    bool BelongsToContinent(const Continent* continent);
};


#endif //TEAMPROJECT_COMP345_COUNTRY_H
