//
// Created by Giselle Martel on 2019-11-26.
//

#include "Country.h"

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
    *country_name_ = *country.country_name_;
    continent_ID_ = country.continent_ID_;
    country_ID_ = country.country_ID_;
    number_of_armies_ = country.number_of_armies_;
    coordinate_x_ = country.coordinate_x_;
    coordinate_y_ = country.coordinate_y_;
    *country_owner_ = *country.country_owner_;
    *continent_ = *country.continent_;

    delete country.continent_;
    delete country.country_owner_;
    delete country.country_name_;
}

Country::~Country() {

    country_owner_ = nullptr;
    country_name_ = nullptr;
    continent_ = nullptr;

    delete country_owner_;
    delete country_name_;
    delete continent_;
}

Country& Country::operator=(const Country &country) {
    *country_name_ = *country.country_name_;
    continent_ID_ = country.continent_ID_;
    country_ID_ = country.country_ID_;
    number_of_armies_ = country.number_of_armies_;
    coordinate_x_ = country.coordinate_x_;
    coordinate_y_ = country.coordinate_y_;
    *country_owner_ = *country.country_owner_;
    *continent_ = *country.continent_;

    delete country.continent_;
    delete country.country_owner_;
    delete country.country_name_;

    return *this;
}

bool Country::operator==(const Country &country) {
    return country.country_ID_ == continent_ID_
        && *country.continent_ == *continent_
        && *country.country_owner_ == *country_owner_
        && *country.country_name_ == *country_name_;
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

void Country::SetContinent(Continent *continent) {
    continent_ = continent;
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

void Country::RemoveArmiesFromCountry(int num_armies_to_remove) {

    if(num_armies_to_remove > number_of_armies_ || num_armies_to_remove < 1) {
        cout << "Invalid number of armies to remove. Aborting operation\n";
        return;
    }
    number_of_armies_ -= num_armies_to_remove;
}

void Country::DisplayInfo() const{
    cout
            << "Country ID: " << GetCountryID() << endl
            << "Country Name: " << *GetCountryName() << endl
            << "Occupying Army Value: " << GetNumberOfArmies() << endl
            << "Continent: " << GetContinentID() << endl << endl;
}

string Country::GetDisplayInfo() const {
    return "Country ID: " + to_string(GetCountryID()) + "\n"
           + "Country Name: " + *GetCountryName() + "\n"
           + "Occupying Army Value: " + to_string(GetNumberOfArmies()) + "\n"
           + "Continent: " + to_string(GetContinentID()) + "\n";
}

// END OF COUNTRY CLASS ----------------------------------------------------------------------------------------