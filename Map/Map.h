/**
 * Assignment #1 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef MAP_H
#define MAP_H

#include "../Player/Player.h"

#include <list>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Player;

//Continent class ------------------------------------------------------------------------------------
class Continent{

private:
    string continent_name_;
    int continent_ID_;
    int army_value_;
    string color_;
    vector<string*>* countries_in_continent_;

public:
    //Constructors
    Continent(string in_continent_name, int army_value, int continent_id);
    Continent(string in_continent_name, int army_value, string color);
    Continent(const Continent &continent);
    ~Continent();

    //operator overloader
    Continent& operator=(const Continent &continent);

    //Setters --------------------------------------------------
    void SetContinentName(string in_continent_name);
    void SetContinentID(int in_continent_ID);

    //Getters --------------------------------------------------
    const string GetContinentName() const;
    const int GetContinentArmyValue() const;
    const int GetContinentID() const;

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
    int number_of_armies_;
    int coordinate_x_;
    int coordinate_y_;
    Player* country_owner_;
    Continent* continent_;
    vector<Country*>* neighbors_;

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
    void SetCountryOwner(Player* player);

    //Getters --------------------------------------------------
    const string GetCountryName() const;
    const int GetCountryID() const;
    int GetNumberOfArmies() const;
    int GetContinentID() const;
    Player* GetCountryOwner() const;

    //Methods -------------------------------------------------------
    void AddNeighborCountry(const Country* neighbor);
    void DisplayInfo();
    bool IsNeighbor(const Country* neighbor);
    bool BelongsToContinent(const Continent* continent);
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
    Map(const Map &map);
    ~Map();

    //operator overloader
    Map& operator=(const Map &map);

    //Getters --------------------------------------------------
    const int GetNumCountries() const;
    const int GetNumContinents() const;
    const string GetMapName() const;
    Country* GetCountryById(int id) const;

    //Setters --------------------------------------------------
    void SetTwoCountriesAsNeighbours(bool value, int country_index, int border_index);

    //Methods -------------------------------------------------------
    void CreateAdjacencyMatrix();
    void DisplayContinents();
    void DisplayCountries();
    void DisplayAdjacencyMatrix();
    void AddCountryToMap(int country_num, string continent_name, int continent_index, int x_coordinate, int y_coordinate);
    void AddContinentToMap(string continent_name, int army_value, int id);
    void AddCountryEdges(vector<int> *edges);

    bool AreCountriesNeighbors(Country* country_a, Country* country_b);
    bool IsContinentDuplicate(Continent* continent_a, Continent* continent_b);
    bool IsCountryDuplicate(Country* country_a, Country* country_b);
};
#endif //MAP_H


