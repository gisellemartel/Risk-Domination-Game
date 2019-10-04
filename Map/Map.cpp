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
//Methods--------------------------------------------------------------------------------------------

void Map::SetTwoCountriesToNeighbors(int index_country_a, int index_country_b){
    adjacency_matrix_[index_country_a][index_country_b] = 1;
    adjacency_matrix_[index_country_b][index_country_a] = 1;
}

bool Map::AreCountriesNeighbors(Country* country_a, Country* country_b){
    if(adjacency_matrix_[country_a->GetCountryID()][country_b->GetCountryID()] == 1) {
        return true;
    }
    return false;
}

void Map::AddCountryToMap(int index_of_country, string country_name, int continent_index){

    countries_->push_back(new Country(index_of_country, country_name, continent_index));
    num_countries_++;

//    for (list<int*>::iterator it=borders->begin(); it != borders->end(); ++it)
//        SetTwoCountriesToNeighbors(index_of_country, **it);

}

void Map::BuildMap(){

}

void Map::AddContinentToMap(string continent_name, int army_value, int continent_id){
    Continent* cur_continent = new Continent(continent_name, army_value);
    num_continents_++;

    //check for continent duplicate
    for(int i=0; i<continents_->size();i++){
        if(IsContinentDuplicate(cur_continent, continents_->at(i)))
            cout<<"duplicate continent found"<< endl;

    }

    cur_continent->SetContinentID(continent_id);
    continents_->push_back(cur_continent);
}

bool Map::IsContinentDuplicate(Continent* continent_a, Continent* continent_b){
    return(continent_a->GetContinentID() == continent_b->GetContinentID() || continent_a->GetContinentName() == continent_b->GetContinentName());
}

void Map::AddCountryEdges(vector<int> edges){
    SetTwoCountriesToNeighbors(*edges.begin(), 6);
}

void Map::DisplayContinents(){
    for(int i=0; i<continents_->size();i++){
        continents_->at(i)->DisplayInfo();
    }
}

//--------------------------------------------------------------------------------------------

//Continent class method implementations ----------------------

//Constructor-----------------------------------------------------
Continent::Continent(string continent_name, int army_value){
    continent_name_ = continent_name;
    army_value_ = army_value;
}


//Methods --------------------------------------------------------
void Continent::AddCountryToContinent(string* country){
    //need to add condition to check if country is already in any other continent
    countries_in_continent_->push_back(country);
}

void Continent::DisplayInfo(){
    cout
    <<"Continent ID: "<< Continent::GetContinentID() <<endl
    <<"Continent Name: "<< Continent::GetContinentName()<<endl
    <<"Continent Army Value: "<< Continent::GetContinentArmyValue()<<endl<<endl;
}


//Country class method implementations ----------------------

//Constructor
Country::Country(int country_ID, string country_name, int continent_ID) {

    country_ID_ = country_ID;
    country_name_ = country_name;
    continent_ID_ = continent_ID;
    number_of_armies_ = 0;
}

//Destructor
Country::~Country() {

}

//Setters --------------------------------------------------

void Country::SetCountryName(string in_country_name){
    country_name_ = in_country_name;
}

void Country::SetNumberOfArmies(int in_number_of_armies){
    number_of_armies_ = in_number_of_armies;
}

//Getters --------------------------------------------------

const string Country::GetCountryName() const {
    return country_name_;
}

const int Country::GetCountryID() const {
    return country_ID_;
}

int Country::GetNumberOfArmies() const {
    return number_of_armies_;
}

int Country::GetContinentID() const {
    return continent_ID_;
}

void Country::AddNeighborCountry(const Country* neighbor) {
    //neighbors->push_front(neighbor);
}

bool Country::IsNeighbor(const Country* neighbor) {
    return false;
}
//Methods------------------------------------------------------

bool Country::BelongsToContinent(const Continent* continent) {
    return false;
}

void Country::DisplayInfo(){
    cout
            <<"Country ID: "<<Country::GetCountryID() << endl
            <<"Country Name: " <<Country::GetCountryName()<<endl
            <<"Army Value: "<<Country::GetNumberOfArmies()<<endl
            <<"Continent: " <<Country::GetContinentID()<<endl<<endl;
}