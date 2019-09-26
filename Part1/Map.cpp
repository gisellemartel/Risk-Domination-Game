/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include "Map.h"

using namespace std;

//Map class method implementations ---------------------------------------------------------

//Constructors

Map::Map(string name, int n_countries, int n_continents) {
    cout << "creating Map object" << endl;
    map_name_ = name;
    num_countries_ = n_countries;
    num_continents_ = n_continents;

    continents_ = new vector<Continent*>;
    countries_ = new vector<Country*>;
    adjacency_matrix_ = new bool*[num_countries_];

    /**create an array for each country in the map, which will have true/false value for adjacency for each other country
    * example:
    *
    *       [
    *           Canada [ true, true, false ],
    *           US     [ true, true, true ],
    *           Mexico  [false, true, true]
    *       ]
    */

    for (int i = 0; i < num_countries_; ++i) {

        adjacency_matrix_[i] = new bool[num_countries_];

        for (int j = 0; j < num_countries_; ++j) {
            //a country is adjacent to itself
            if (j == i)
            {
                adjacency_matrix_[i][j] = true;
            }
            adjacency_matrix_[i][j] = false;
        }
    }

}

//Destructor
Map::~Map() {
    cout << "Destroying Map object" << endl;
    //delete all the country objects
    for (int i = 0; i < (*countries_).size(); ++i) {
        delete (*countries_)[i];
    }

    //delete all the continent objects
    for (int i = 0; i < (*continents_).size(); ++i) {
        delete (*continents_)[i];
    }

    //delete rows of adjacency matrix
    for (int i = 0; i < num_countries_; ++i) {
        delete[] adjacency_matrix_[i];
    }

    delete[] adjacency_matrix_;
    delete countries_;
    delete continents_;
}

const int Map::GetNumCountries() const {
    return num_countries_;
}

const int Map::GetNumContinents() const {
    return num_continents_;
}

const string Map::GetMapName() const {
    return map_name_;
}

//--------------------------------------------------------------------------------------------

//Country class method implementations ----------------------

//Constructor
Country::Country(string* country_name) {
    country_name_ = country_name;
}

//Destructor
Country::~Country() {

}

//Setters --------------------------------------------------

void Country::SetCountryName(string* in_country_name){
    country_name_ = in_country_name;
}

void Country::SetNumberOfArmies(int in_number_of_armies){
    number_of_armies_ = in_number_of_armies;
}

//Getters --------------------------------------------------

const string* Country::GetCountryName() const {
    return country_name_;
}

int Country::GetNumberOfArmies() const {
    return number_of_armies_;
}

Continent* Country::GetContinent() const {
    return continent_;
}

void Country::AddNeighborCountry(const Country* neighbor) {
    //neighbors->push_front(neighbor);
}

bool Country::IsNeighbor(const Country* neighbor) {
    return false;
}

bool Country::BelongsToContinent(const Continent* continent) {
    return false;
}


//Continent class method implementations ----------------------
void Continent::AddCountryToContinent(string* country){
    //need to add condition to check if country is already in any other continent
    countries_in_continent_->push_back(country);
}

