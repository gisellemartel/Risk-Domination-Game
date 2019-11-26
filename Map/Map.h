/**
 * Assignment #4 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef MAP_H
#define MAP_H

#include "Country.h"
#include "Continent.h"

#include <list>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Continent;
class Country;

//Map class ------------------------------------------------------------------------------------
//Implementation of a connected graph where nodes are countries and edges are adjacencies
class Map {

private:
    string* map_name_;
    int num_countries_;
    int num_continents_;
    vector<Continent*>* continents_;
    vector<Country*>* countries_;

    //2d array will be used to track what countries are adjacent to others
    bool** adjacency_matrix_;

public:
    //Constructors
    explicit Map(const string& name);
    Map(const Map &map);
    ~Map();

    //operator overloader
    Map& operator=(const Map &map);

    //Getters --------------------------------------------------
    int GetNumCountries() const;
    int GetNumContinents() const;
    string* GetMapName() const;
    Country* GetCountryById(int id) const;
    Continent* GetContinentByName(string name) const;
    Country* GetCountryByName(string name) const;
    Continent* GetContinentById(int id) const;
    vector<Country*>* GetCountries() const;
    vector<Continent*>* GetContinents() const;

    //Setters --------------------------------------------------
    void SetTwoCountriesAsNeighbours(bool value, int country_index, int border_index);

    //Methods -------------------------------------------------------
    void CreateAdjacencyMatrix();
    void DisplayContinents() const;
    void DisplayCountries() const;
    void DisplayAdjacencyMatrix() const;
    void AddCountryToMap(int country_num, const string& continent_name, int continent_index, int x_coordinate, int y_coordinate);
    void AddContinentToMap(const string& continent_name, int army_value, int id);
    void DisplayGraphTraversal(Country* origin_country) const;


    bool AreCountriesNeighbors(Country* country_a, Country* country_b) const;

    string GenerateListOfNeighboringCountries(Country* country) const;

    vector<Country*>* GetNeighbouringCountriesWithArmies(Country* country) const;
    vector<Country*>* GetNeighbouringCountries(Country* country) const;

    static string StripString(string string_to_strip, const string &left_delim, const string &right_delim);

    static bool IsContinentDuplicate(Continent* continent_a, Continent* continent_b);
    static bool IsCountryDuplicate(Country* country_a, Country* country_b);
};
#endif //MAP_H


