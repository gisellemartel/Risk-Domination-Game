//
// Created by Giselle Martel on 2019-09-13.
//

#include "Map.h"
#include "Player.h"

using namespace std;

class map{

};

class Country{
private:
    string country_name;
    Player country_owner;
    int numberOfArmies;
    vector<Country> neighbors

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

    }


};
