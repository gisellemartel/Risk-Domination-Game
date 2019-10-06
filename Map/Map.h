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
    string color_;
    vector<string*>* countries_in_continent_;

public:
    //Constructor using initializer list
    Continent(string in_continent_name, int army_value);
    Continent(string in_continent_name, int army_value, string color);
    Continent(const Continent &continent);
    ~Continent();

    //operator overloader
    Continent& operator=(const Continent &continent);

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




//Border class ------------------------------------------------------------------------------------
class Border {
private:
    int country_ID_;
    vector<int> *neighbour_ids_;

public:
    //Constructors
    Border(int country_ID, vector<int> *neighbour_ids);
    Border(const Border &border);
    ~Border();

    //operator overloader
    Border& operator=(const Border &border);
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
    int coordinate_x_;
    int coordinate_y_;

public:
    //Constructors
    Country(int country_ID, string country_name, int continent_ID);
    Country(int country_ID, string country_name, int continent_ID, int coordinate_x, int coordinate_y);
    Country(const Country &country);
    ~Country();

    //operator overloader
    Country& operator=(const Country &country);

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
    //Constructors
    Map(string name);
    Map(string name, int n_countries, int n_continents);
    Map(const Map &map);
    ~Map();

    //operator overloader
    Map& operator=(const Map &map);


    //Getters --------------------------------------------------

    const int GetNumCountries() const;
    const int GetNumContinents() const;
    const string GetMapName() const;

    //Setters --------------------------------------------------
    void SetTwoCountriesToNeighbors(int index_country_a, int index_country_b);

    //Methods -------------------------------------------------------
    bool AreCountriesNeighbors(Country* country_a, Country* country_b);
    void AddCountryToMap(Country* country_to_add);
    void AddContinentToMap(Continent* continent_to_add);
    bool IsContinentDuplicate(Continent* continent_a, Continent* continent_b);
    bool IsCountryDuplicate(Country* country_a, Country* country_b);
    void AddCountryEdges(vector<int> *edges);
    void DisplayContinents();
    void DisplayCountries();
    void DisplayEdges();
};
#endif //MAP_H


