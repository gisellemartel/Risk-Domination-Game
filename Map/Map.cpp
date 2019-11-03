/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#include "Map.h"

using namespace std;

// START OF CONTINENT CLASS FUNCTIONS  -----------------------------------------------------------------

Continent::Continent(string* continent_name, int army_value, int continent_id){
    continent_name_ = continent_name;
    army_value_ = army_value;
    continent_ID_ = continent_id;
    color_= new string("");
    countries_in_continent_ = new vector<string*>;
}


Continent::Continent(const Continent &continent) {
    continent_name_ = continent.continent_name_;
    continent_ID_ = continent.continent_ID_;
    army_value_ = continent.army_value_;
    color_ = continent.color_;
    for(size_t i = 0; i < continent.countries_in_continent_->size(); ++i) {
       countries_in_continent_[i] = continent.countries_in_continent_[i];
    }
    countries_in_continent_ = continent.countries_in_continent_;
}

Continent::~Continent() {
    for(size_t i = 0; i < countries_in_continent_->size(); ++i) {
        delete (&countries_in_continent_[i]);
    }

    delete countries_in_continent_;
}

Continent& Continent::operator=(const Continent &continent) {
    continent_name_ = continent.continent_name_;
    continent_ID_ = continent.continent_ID_;
    army_value_ = continent.army_value_;
    color_ = continent.color_;
    for(size_t i = 0; i < continent.countries_in_continent_->size(); ++i) {
        countries_in_continent_[i] = continent.countries_in_continent_[i];
    }
    countries_in_continent_ = continent.countries_in_continent_;
    return *this;
}

void Continent::SetContinentName(string* in_continent_name) {
    continent_name_ = in_continent_name;
}

void Continent::SetContinentID(int in_continent_ID){
    continent_ID_ = in_continent_ID;
}

string* Continent::GetContinentName() const {
    return continent_name_;
}

int Continent::GetContinentArmyValue() const{
    return army_value_;
}

int Continent::GetContinentID() const{
    return continent_ID_;
}

void Continent::AddCountryToContinent(const string& country){
    //need to add condition to check if country is already in any other continent
    for(string* country_in_continent  : *countries_in_continent_) {
        if(*country_in_continent == country) {
            cout << "Country already in continent";
            return;
        }
    }
    countries_in_continent_->push_back(new string(country));
}

void Continent::DisplayInfo() const{
    cout
    <<"Continent ID: "<< GetContinentID() <<endl
    <<"Continent Name: "<< *GetContinentName()<<endl
    <<"Continent Army Value: "<< GetContinentArmyValue()<<endl<<endl;
}

//START OF COUNTRY CLASS FUNCTIONS ------------------------------------------------------------------------

//Constructors
Country::Country(int country_ID, string* country_name, int continent_ID) {

    country_ID_ = country_ID;
    country_name_ = country_name;
    continent_ID_ = continent_ID;
    number_of_armies_ = 0;
    coordinate_x_ = 0;
    coordinate_y_ = 0;
    country_owner_ = nullptr;
    continent_ = nullptr;
}

Country::Country(int country_ID, string* country_name, int continent_ID, int coordinate_x, int coordinate_y) {
    country_ID_ = country_ID;
    country_name_ = country_name;
    continent_ID_ = continent_ID;
    coordinate_x_ = coordinate_x;
    coordinate_y_ = coordinate_y;
    number_of_armies_ = 0;
    country_owner_ = nullptr;
    continent_ = nullptr;
}

Country::Country(const Country &country) {
    country_name_ = country.country_name_;
    continent_ID_ = country.continent_ID_;
    country_ID_ = country.country_ID_;
    number_of_armies_ = country.number_of_armies_;
    coordinate_x_ = country.coordinate_x_;
    coordinate_y_ = country.coordinate_y_;
    country_owner_ = country.country_owner_;
    continent_ = country.continent_;
}

Country::~Country() {
    delete continent_;
}

Country& Country::operator=(const Country &country) {
    country_name_ = country.country_name_;
    continent_ID_ = country.continent_ID_;
    country_ID_ = country.country_ID_;
    number_of_armies_ = country.number_of_armies_;
    coordinate_x_ = country.coordinate_x_;
    coordinate_y_ = country.coordinate_y_;
    country_owner_ = country.country_owner_;
    continent_ = country.continent_;
    return *this;
}

bool Country::operator==(const Country &country) {
    bool is_equal = true;
    is_equal &= country_name_ == country.country_name_;
    is_equal &= continent_ID_ == country.continent_ID_;
    is_equal &= country_ID_ == country.country_ID_;
    is_equal &= number_of_armies_ == country.number_of_armies_;
    is_equal &= coordinate_x_ == country.coordinate_x_;
    is_equal &= coordinate_y_ == country.coordinate_y_;
    is_equal &= country_owner_ == country.country_owner_;
    is_equal &= continent_ == country.continent_;

    return is_equal;
}

//Setters --------------------------------------------------

void Country::SetCountryName(string* in_country_name) {
    country_name_ = in_country_name;
}

void Country::SetNumberOfArmies(int in_number_of_armies) {
    number_of_armies_ = in_number_of_armies;
}

void Country::SetCountryOwner(Player* player) {
    country_owner_ = player;
}

//Getters --------------------------------------------------

string* Country::GetCountryName() const {
    return country_name_;
}

int Country::GetCountryID() const {
    return country_ID_;
}

int Country::GetNumberOfArmies() const {
    return number_of_armies_;
}

int Country::GetContinentID() const {
    return continent_ID_;
}

Player* Country::GetCountryOwner() const {
    return country_owner_;
}

//Methods------------------------------------------------------

//TODO implementation
bool Country::BelongsToContinent(const Continent* continent) {
    return GetContinentID() == continent->GetContinentID();
}

void Country::AddArmyToCountry() {
    if(number_of_armies_ < 0) {
        number_of_armies_ = 1;
    }
    ++number_of_armies_;
}

void Country::DisplayInfo() const{
    cout
            << "Country ID: " << GetCountryID() << endl
            << "Country Name: " << *GetCountryName() << endl
            << "Occupying Army Value: " << GetNumberOfArmies() << endl
            << "Continent: " << GetContinentID() << endl << endl;
}

// END OF COUNTRY CLASS ----------------------------------------------------------------------------------------

//START OF MAP CLASS FUNCTIONS ---------------------------------------------------------------------------------

Map::Map(const string& name) {
    map_name_ = new string(name);
    continents_ = new vector<Continent*>;
    countries_ = new vector<Country*>;
    num_countries_ = 0;
    num_continents_ = 0;
    adjacency_matrix_ = nullptr;
}

Map::Map(const Map &map) {
    map_name_ = map.map_name_;
    num_countries_ = map.num_countries_;
    num_continents_ = map.num_continents_;
    continents_ = map.continents_;
    countries_ = map.countries_;

    adjacency_matrix_ = map.adjacency_matrix_;
    for(size_t i = 0; i < map.num_countries_; ++i) {
        adjacency_matrix_[i] = map.adjacency_matrix_[i];
        for(size_t j = 0; j < map.num_countries_; ++j) {
            adjacency_matrix_[i][j] = map.adjacency_matrix_[i][j];
        }
    }
}

Map::~Map() {
    //delete all the country objects
    for (auto & i : (*countries_)) {
        delete i;
    }

    //delete all the continent objects
    for (auto & i : (*continents_)) {
        delete i;
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
    for(size_t i = 0; i < map.num_countries_; ++i) {
        adjacency_matrix_[i] = map.adjacency_matrix_[i];
        for(size_t j = 0; j < map.num_countries_; ++j) {
            adjacency_matrix_[i][j] = map.adjacency_matrix_[i][j];
        }
    }
    return *this;
}

int Map::GetNumCountries() const {
    return num_countries_;
}

int Map::GetNumContinents() const {
    return num_continents_;
}

string* Map::GetMapName() const {
    return map_name_;
}

Country* Map::GetCountryById(int id) const {
    if(id < 1 || id > countries_->size()) {
        cout << "Invalid Id given. Countries start from 1" << endl;
        return nullptr;
    }
    return (*countries_)[id - 1];
}

vector<Country*>* Map::GetCountries() const {
    return countries_;
}

void Map::SetTwoCountriesAsNeighbours(bool value, int country_index, int border_index) {

    if(country_index >= num_countries_ || border_index >= num_countries_ || country_index < 0 || border_index < 0) {
        cout << "error, invalid index given" << endl;
        return;
    }
    adjacency_matrix_[country_index][border_index] = value;
    adjacency_matrix_[border_index][country_index] = value;
}

//Methods--------------------------------------------------------------------------------------------

void Map::AddCountryToMap(int country_num, const string& continent_name, int continent_index, int x_coordinate, int y_coordinate){

    auto* country_to_add = new Country(country_num, new string(continent_name), continent_index, x_coordinate, y_coordinate);
    for(Country* country : *countries_){
        if(IsCountryDuplicate(country_to_add, country)){
            cout << "Duplicate country found. Aborting operation" << endl;
            return;
        }
    }

    countries_->push_back(country_to_add);
    ++num_countries_;
}


void Map::AddContinentToMap(const string& continent_name, int army_value, int id){
    if(army_value == 0) {
        cout << "Invalid Continent Army Value" << endl;
        return;
    }
    Continent* continent_to_add = new Continent(new string(continent_name), army_value, id);

    //check for continent duplicate
    if(!continents_->empty()) {
        for(auto continent_to_check : *continents_){
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

    for (size_t i = 0; i < num_countries_; ++i) {

        adjacency_matrix_[i] = new bool[num_countries_];

        for (int j = 0; j < num_countries_; ++j) {
            //a country is adjacent to itself
            adjacency_matrix_[i][j] = j == i;
        }
    }
}


void Map::DisplayContinents() const {
    for(Continent* continent : *continents_){
        continent->DisplayInfo();
    }
}

void Map::DisplayCountries() const {
    for(Country* country : *countries_){
        country->DisplayInfo();
    }
}

void Map::DisplayAdjacencyMatrix() const {
    cout << "\t\t\tNeighbours " << endl;
    cout << "\t\t\t";
    for(size_t i = 0; i < num_countries_; ++i) {
        cout << (i+1) << "\t";
    }
    cout << endl;

    for(size_t i = 0; i < num_countries_; ++i) {
        cout << "country " << (i + 1) << ":\t";

        for(size_t j = 0; j < num_countries_; ++j) {
            cout << adjacency_matrix_[i][j] << '\t';
        }

        cout << endl;
    }

    cout << endl;
}

void Map::DisplayGraphTraversal(Country* origin_country, Country* destination_country) const {
    int index_a = origin_country->GetCountryID() - 1;
    int index_b = destination_country->GetCountryID() - 1;

    if(index_a < 0 || index_a > num_countries_ || index_b < 0 || index_a > num_countries_) {
        cout << "Invalid country given. Please try again" << endl;
        return;
    }

    if(index_a == index_b) {
        cout << "Origin country and destination country are the same. No need to traverse\n\n";
        return;
    }

    cout << "Traversing from " << *origin_country->GetCountryName() << " to " << *destination_country->GetCountryName() << endl << endl;

    if (adjacency_matrix_[index_a][index_b]) {
        cout << *origin_country->GetCountryName() << " and " << *destination_country->GetCountryName() << " are neighbours\n";
        cout << "Success, we have found a path from " << *origin_country->GetCountryName() << " to " << *destination_country->GetCountryName() << ". Traversal complete\n";
        return;
    }

    if(index_a < index_b) {
        int current_country = index_a;

        for (size_t i = 0; i < num_countries_; ++i) {

            if (i == current_country) {
                continue;
            }

            //if the country at index i is a neighbour to origin country, then traverse to it
            if (adjacency_matrix_[current_country][i]) {
                cout << "Leaving " << *(*countries_)[current_country]->GetCountryName()
                     << " and traversing to neighbour " << *(*countries_)[i]->GetCountryName() << endl;

                if (adjacency_matrix_[current_country][index_b]) {
                    cout << "Success, we have found a path from " << *origin_country->GetCountryName() << " to "
                         << *destination_country->GetCountryName() << ". Traversal complete\n";
                    return;
                }
                current_country = i;
            }
        }

        //if we have reached this point we have failed to find a path
        cout << "Failed to find a path from " << *origin_country->GetCountryName() << " to " << *destination_country->GetCountryName() << endl;
    } else if (index_a > index_b) {
        int current_country = index_a;

        for(int i = num_countries_ - 1; i >= 0; --i) {

            if(i == current_country ) {
                continue;
            }

            //if the country at index i is a neighbour to origin country, then traverse to it
            if(adjacency_matrix_[current_country][i]) {
                cout << "Leaving " << *(*countries_)[current_country]->GetCountryName() << " and traversing to neighbour " << *(*countries_)[i]->GetCountryName() << endl;

                if (adjacency_matrix_[current_country][index_b]) {
                    cout << "Success, we have found a path from " << *origin_country->GetCountryName() << " to " << *destination_country->GetCountryName() << ". Traversal complete\n";
                    return;
                }
                current_country = i;
            }

        }

        //if we have reached this point we have failed to find a path
        cout << "Failed to find a path from " << *origin_country->GetCountryName() << " to " << *destination_country->GetCountryName() << endl;
    }
}

void Map::AddCountryEdges(vector<int> *edges){

    if(edges->size() <= 1){
        cout << "no neighbors found for country index " << edges->at(0) <<endl;
        return;
    }

    for(size_t i= 1; i< edges->size(); ++i){
        SetTwoCountriesAsNeighbours(true, edges->at(0)-1, edges->at(i)-1);
    }
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

//static functions
bool Map::IsContinentDuplicate(Continent* continent_a, Continent* continent_b){
    return(continent_a->GetContinentID() == continent_b->GetContinentID() || continent_a->GetContinentName() == continent_b->GetContinentName());
}

bool Map::IsCountryDuplicate(Country* country_a, Country* country_b){
    return (country_a->GetCountryID() == country_b->GetCountryID() || country_a->GetCountryName() == country_b->GetCountryName());
}

vector<Country*>* Map::GetNeighbouringCountries(Country* country) {
    int country_index = country->GetCountryID() - 1;
    vector<Country*>* neighbouring_countries = new vector<Country*>;
    vector<int> neighbouring_countries_indices;

    //need access to the map object
    if(country_index < 0 || country_index > num_countries_) {
        cout << "Country " << *country->GetCountryName() << " has no neighbours!\n";
    } else {
        //iterate over adjacency matrix to obtain the list of neighbours
        for(int row = 0; row < num_countries_; ++row) {
            //find the current country's neighbour list
            if(row == country_index) {
                for(int col = 0; col < num_countries_; ++col) {
                    //find the countries that are neighbours
                    if(adjacency_matrix_[row][col] && col != country_index) {
                        int id_of_neighbour = col + 1;
                        Country* neighbouring_country = GetCountryById(id_of_neighbour);
                        if(neighbouring_country) {
                            neighbouring_countries->push_back(neighbouring_country);
                        }
                    }
                }
            }
        }
    }

    return neighbouring_countries;
}
//--------------------------------------------------------------------------------------------