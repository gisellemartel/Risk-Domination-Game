/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include "Map.h"

using namespace std;

//Map class method implementations ---------------------------------------------------------

//Constructors

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

Country* Map::GetCountryById(int id) const {
    if(id < 1 || id > countries_->size()) {
        return nullptr;
    }
    return (*countries_)[id - 1];
}
//Methods--------------------------------------------------------------------------------------------

void Map::SetTwoCountriesAsNeighbours(bool value, int country_index, int border_index) {

    if(country_index >= num_countries_ || border_index >= num_countries_) {
        cout << "error, invalid index given" << endl;
        return;
    }
    adjacency_matrix_[country_index][border_index] = value;
    adjacency_matrix_[border_index][country_index] = value;
}

bool Map::AreCountriesNeighbors(Country* country_a, Country* country_b){
    int index_a = country_a->GetCountryID() - 1;
    int index_b = country_b->GetCountryID() - 1;
    if(index_a < 0 || index_a > countries_->size() || index_b < 0 || index_a > countries_->size()) {
        return false;
    }
    if(adjacency_matrix_[index_a][index_b] && adjacency_matrix_[index_b][index_a]) {
        return true;
    }
    return false;
}

void Map::AddCountryToMap(int country_num, string continent_name, int continent_index, int x_coordinate, int y_coordinate){

    Country* country_to_add = new Country(country_num, continent_name, continent_index, x_coordinate, y_coordinate);
    for(int i=0; i<countries_->size();i++){
        if(IsCountryDuplicate(country_to_add, countries_->at(i))){
            cout << "Duplicate country found. Aborting operation" << endl;
            return;
        }
    }

    countries_->push_back(country_to_add);
    ++num_countries_;
}


void Map::AddContinentToMap(string continent_name, int army_value, int id){
    if(army_value == 0) {
        cout << "Invalid Continent Army Value" << endl;
        return;
    }
    Continent* continent_to_add = new Continent(continent_name, army_value, id);

    //check for continent duplicate
    if(continents_->size() > 0) {
        for(int i = 0; i < continents_->size(); ++i){
            Continent* continent_to_check = (*continents_)[i];

            if(!continent_to_check) {
                continue;
            }

            if(IsContinentDuplicate(continent_to_add, continent_to_check)){
                cout << "duplicate continent name found" << endl;
                continue;
            }
        }
    }
    continents_->push_back(continent_to_add);
    ++num_continents_;
}

void Map::CreateAdjacencyMatrix() {
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

bool Map::IsContinentDuplicate(Continent* continent_a, Continent* continent_b){
    return(continent_a->GetContinentID() == continent_b->GetContinentID() || continent_a->GetContinentName() == continent_b->GetContinentName());
}

bool Map::IsCountryDuplicate(Country* country_a, Country* country_b){
    return (country_a->GetCountryID() == country_b->GetCountryID() || country_a->GetCountryName() == country_b->GetCountryName());
}

void Map::AddCountryEdges(vector<int> *edges){

    if(edges->size() <= 1){
        cout << "no neighbors found for country index " << edges->at(0) <<endl;
        return;
    }

    for(int i= 1; i< edges->size(); i++){
        SetTwoCountriesAsNeighbours(true, edges->at(0)-1, edges->at(i)-1);
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

void Map::DisplayAdjacencyMatrix() {
    cout << "\t\t\tNeighbours " << endl;
    cout << "\t\t\t";
    for(int i = 0; i < num_countries_; ++i) {
        cout << (i+1) << "\t";
    }
    cout << endl;

    for(int i = 0; i < num_countries_; ++i) {
        //debugging to print matrix
        cout << "country " << (i + 1) << ":\t";
        for(int j = 0; j < num_countries_; ++j) {
            cout << adjacency_matrix_[i][j] << '\t';
        }
        cout << endl;
        //debug end
    }

    cout << endl;
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
    for(int i = 0; i<countries_in_continent_->size(); i++)
    {
        if(countries_in_continent_->at(i) == country){
            cout<<"Country already in continent";
            return;
        }
    }
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
    country_owner_ = new Player("new player");
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