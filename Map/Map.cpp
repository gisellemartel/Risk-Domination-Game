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
            else
                adjacency_matrix_[i][j] = false;
//
        }
    }
}

Map::Map(const Map &map) {
    map_name_ = map.map_name_;
    num_countries_ = map.num_countries_;
    num_continents_ = map.num_continents_;
    continents_ = map.continents_;
    countries_ = map.countries_;
    adjacency_matrix_ = map.adjacency_matrix_;
}

Map::Map(string name) {
    map_name_ = name;
    continents_ = new vector<Continent*>;
    countries_ = new vector<Country*>;
    num_countries_ = 0;
    num_continents_ = 0;
    adjacency_matrix_ = nullptr;
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

Map& Map::operator=(const Map &map)
{
    map_name_ = map.map_name_;
    num_countries_ = map.num_countries_;
    num_continents_ = map.num_continents_;
    continents_ = map.continents_;
    countries_ = map.countries_;
    adjacency_matrix_ = map.adjacency_matrix_;
    return *this;
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
    adjacency_matrix_[index_country_a][index_country_b] = true;
    adjacency_matrix_[index_country_b][index_country_a] = true;
}

void Map::SetAdjacencyMatrix(int num_countries) {

    adjacency_matrix_ = new bool*[num_countries];
    num_countries_ = num_countries;
    /**create an array for each country in the map, which will have true/false value for adjacency for each other country
    * example:
    *
    *       [
    *           Canada [ true, true, false ],
    *           US     [ true, true, true ],
    *           Mexico  [false, true, true]
    *       ]
    */

    for (int i = 0; i < num_countries; ++i) {

        adjacency_matrix_[i] = new bool[num_countries];

        for (int j = 0; j < num_countries; ++j) {
            //a country is adjacent to itself
            if (j == i)
            {
                adjacency_matrix_[i][j] = true;
            }
            else
                adjacency_matrix_[i][j] = false;
        }
    }
}

void Map::SetValueOfBorderInMatrix(bool value, int country_index, int border_index) {

    if(country_index >= num_countries_ || border_index >= num_countries_) {
        cout << "error, invalid index give" << endl;
        return;
    }
    adjacency_matrix_[country_index][border_index] = value;
}

bool Map::AreCountriesNeighbors(Country* country_a, Country* country_b){
    if(adjacency_matrix_[country_a->GetCountryID()][country_b->GetCountryID()] == 1) {
        return true;
    }
    return false;
}

void Map::AddCountryToMap(Country* country_to_add){

    for(int i=0; i<countries_->size();i++){
        if(IsCountryDuplicate(country_to_add, countries_->at(i))){
            cout<<"duplicate country found"<<endl;
            throw "duplicate country error";
        }
    }

    countries_->push_back(country_to_add);
}


void Map::AddContinentToMap(Continent* continent_to_add){
    if(continent_to_add->GetContinentArmyValue() == 0){
        cout<<"Invalid Continent Army Value"<<endl;
        throw "Invalid Continent Army value";
    }

    num_continents_++;

    //check for continent duplicate
    if(continents_->size() > 0) {
        for(int i = 0; i < continents_->size(); ++i){
            Continent* continent_to_check = (*continents_)[i];

            if(!continent_to_check) {
                continue;
            }

            if(IsContinentDuplicate(continent_to_add, continent_to_check)){
                cout<<"duplicate continent name found"<< endl;
                //throw "duplicate Continent";
            }
        }

    }

    continents_->push_back(continent_to_add);
}

bool Map::IsContinentDuplicate(Continent* continent_a, Continent* continent_b){
    return(continent_a->GetContinentID() == continent_b->GetContinentID() || continent_a->GetContinentName() == continent_b->GetContinentName());
}

bool Map::IsCountryDuplicate(Country* country_a, Country* country_b){
    return (country_a->GetCountryID() == country_b->GetCountryID() || country_a->GetCountryName() == country_b->GetCountryName());
}

void Map::AddCountryEdges(vector<int> *edges){

    if(edges->size() <= 1){
        cout<<"no neighbors found for country index " << edges->at(0) <<endl;
        throw "no edge on country";
    }

    for(int i= 1; i< edges->size(); i++){
        SetTwoCountriesToNeighbors(edges->at(0)-1, edges->at(i)-1);
    }
}

void Map::DisplayContinents(){
    for(int i=0; i<continents_->size();i++){
        continents_->at(i)->DisplayInfo();
    }
}

void Map::DisplayCountries(){
    for(int i=0; i<countries_->size(); i++){
        countries_->at(i)->DisplayInfo();
    }
}

void Map::DisplayEdges(){
    for(int i = 0; i< num_countries_ ; i++){
        for(int j = 0; j<num_countries_; j++){
            cout<<" "<<adjacency_matrix_[i][j];
        }
        cout<<endl;
    }
}

void Map::DisplayAdjacencyMatrix() {

    for(int i = 0; i < num_countries_; ++i) {
        //debugging to print matrix
        cout << "country: " << (i + 1) << '\t';
        for(int j = 0; j < num_countries_; ++j) {
            cout << adjacency_matrix_[i][j] << ' ';
        }
        cout << endl;
        //debug end
    }
}
//--------------------------------------------------------------------------------------------




//Border class method implementations ----------------------------------------------------------
Border::Border(int country_ID, vector<int> *neighbour_ids) {
    country_ID_ = country_ID;
    neighbour_ids_ = neighbour_ids;
}

Border::Border(const Border &border) {
    country_ID_ = border.country_ID_;
    neighbour_ids_ = border.neighbour_ids_;
}

Border::~Border() {
    delete neighbour_ids_;
}

Border& Border::operator=(const Border &border) {
    country_ID_ = border.country_ID_;
    neighbour_ids_ = border.neighbour_ids_;
    return *this;
}
//--------------------------------------------------------------------------------------------




//Continent class method implementations -----------------------------------------------------

//Constructor-----------------------------------------------------
Continent::Continent(string continent_name, int army_value, int continent_id){
    continent_name_ = continent_name;
    army_value_ = army_value;
    continent_ID_ = continent_id;
}

//Constructor for map loader----------------------------------------
Continent::Continent(string continent_name, int army_value, string color) {
    continent_name_ = continent_name;
    army_value_ = army_value;
    color_ = color;
}

Continent& Continent::operator=(const Continent &continent) {
    continent_name_ = continent.continent_name_;
    continent_ID_ = continent.continent_ID_;
    army_value_ = continent.army_value_;
    color_ = continent.color_;
    countries_in_continent_ = continent.countries_in_continent_;
    return *this;
}

Continent::~Continent() {
    delete countries_in_continent_;
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




//Country class method implementations -----------------------------------------------------

//Constructor
Country::Country(int country_ID, string country_name, int continent_ID) {

    country_ID_ = country_ID;
    country_name_ = country_name;
    continent_ID_ = continent_ID;
    number_of_armies_ = 0;
}

//Constructor for map loader
Country::Country(int country_ID, string country_name, int continent_ID, int coordinate_x, int coordinate_y) {
    country_ID_ = country_ID;
    country_name_ = country_name;
    continent_ID_ = continent_ID;
    coordinate_x_ = coordinate_x;
    coordinate_y_ = coordinate_y;
}

//Destructor
Country::~Country() {
    delete neighbors_;
    delete continent_;
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
            <<"Occupying Army Value: "<<Country::GetNumberOfArmies()<<endl
            <<"Continent: " <<Country::GetContinentID()<<endl<<endl;
}
//----------------------------------------------------------------------------------------