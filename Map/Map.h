/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#ifndef MAP_H
#define MAP_H

#include "../Player/Player.h"

#include <list>
#include <vector>
#include <string>
#include <iostream>

using namespace std;


//Continent class ------------------------------------------------------------------------------------
class Continent{
private:
    string continent_name_;
    int continent_ID_;
    int army_value_;
    vector<string*>* countries_in_continent_;

public:
    //Constructor using initializer list
    Continent(string in_continent_name, int army_value);

    ~Continent(){}

    //Setters --------------------------------------------------
    void SetContinentName(string in_continent_name) { continent_name_ = in_continent_name; }
    void SetContinentID(int in_continent_ID){ continent_ID_ = in_continent_ID;};


    //Getters --------------------------------------------------
    const string GetContinentName() const { return continent_name_; }
    const int GetContinentArmyValue() const {return army_value_; }
    const int GetContinentID() const{return continent_ID_;}


    //Methods -------------------------------------------------------
    void AddCountryToContinent(string* country);
    void DisplayInfo();
};



//Country class ------------------------------------------------------------------------------------
class Country{

private:
    string country_name_;
    int continent_ID_;
    int country_ID_;
    //Player* country_owner_;
    int number_of_armies_;
    vector<Country*>* neighbors_;
    Continent* continent_;

public:
    //Constructor
    Country(int country_ID, string country_name, int continent_ID);
    //Destructor
    ~Country();

    //Setters --------------------------------------------------

    void SetCountryName(string in_country_name);
    void SetNumberOfArmies(int in_number_of_armies);

    //Getters --------------------------------------------------

    const string GetCountryName() const;
    const int GetCountryID() const;
    int GetNumberOfArmies() const;
    int GetContinentID() const;

    //Methods -------------------------------------------------------

    void AddNeighborCountry(const Country* neighbor);
    bool IsNeighbor(const Country* neighbor);
    bool BelongsToContinent(const Continent* continent);
    void DisplayInfo();
};
//Map class ------------------------------------------------------------------------------------
//Implementation of a connected graph where nodes are countries and edges are adjacencies
class Map {

private:
    string map_name_;
    int num_countries_;
    int num_continents_;
    vector<Continent*>* continents_;
    vector<Country*>* countries_;

    //2d array will be used to track what countries are adjacent to others
    bool** adjacency_matrix_;

public:
    //Constructor
    Map(string name, int n_countries, int n_continents);

    //Destructor
    ~Map();


    //Getters --------------------------------------------------

    const int GetNumCountries() const;
    const int GetNumContinents() const;
    const string GetMapName() const;

    //Setters --------------------------------------------------
    void SetTwoCountriesToNeighbors(int index_country_a, int index_country_b);

    //Methods -------------------------------------------------------
    bool AreCountriesNeighbors(Country* country_a, Country* country_b);
    void AddCountryToMap(int index_of_country, string country_name, int continent_index);
    void BuildMap();
    void AddContinentToMap(string continent_name, int army_value, int continent_id);
    bool IsDuplicate(Continent* continent_a, Continent* continent_b);
    void AddCountryEdges(list<int> edges);
    void DisplayContinents();
    //void AddContinent(Continent* continent);

};
#endif //MAP_H


