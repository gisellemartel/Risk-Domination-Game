
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
    owner_id_ = 0;
}

Country::Country(int country_ID, string* country_name, int continent_ID, int coordinate_x, int coordinate_y) {
    country_ID_ = country_ID;
    country_name_ = country_name;
    continent_ID_ = continent_ID;
    coordinate_x_ = coordinate_x;
    coordinate_y_ = coordinate_y;
    number_of_armies_ = 0;
    owner_id_ = 0;
}

Country::Country(const Country &country) {
    *country_name_ = *country.country_name_;
    continent_ID_ = country.continent_ID_;
    country_ID_ = country.country_ID_;
    number_of_armies_ = country.number_of_armies_;
    coordinate_x_ = country.coordinate_x_;
    coordinate_y_ = country.coordinate_y_;
    owner_id_ = country.owner_id_;

    delete country.country_name_;
}

Country::~Country() {
    if(country_name_) {
        delete country_name_;
        country_name_ = nullptr;
    }
}

Country& Country::operator=(const Country &country) {
   if(this != &country) {
       *country_name_ = *country.country_name_;
       continent_ID_ = country.continent_ID_;
       country_ID_ = country.country_ID_;
       number_of_armies_ = country.number_of_armies_;
       coordinate_x_ = country.coordinate_x_;
       coordinate_y_ = country.coordinate_y_;
       owner_id_ = country.owner_id_;

       delete country.country_name_;
   }

    return *this;
}

bool Country::operator==(const Country &country) {
    return country.country_ID_ == country_ID_
        && *country.country_name_ == *country_name_
        && country.owner_id_ == owner_id_;
}

//Setters --------------------------------------------------

void Country::SetCountryName(string* in_country_name) {
    country_name_ = in_country_name;
}

void Country::SetNumberOfArmies(int in_number_of_armies) {
    number_of_armies_ = in_number_of_armies;
}

void Country::SetCountryOwner(int id) {
    owner_id_ = id;
}

void Country::SetContinentID(int id) {
    continent_ID_ = id;
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

int Country::GetOwnerID() const {
    return owner_id_;
}

//Methods------------------------------------------------------
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
    if(country_name_) {
        return "Country ID: " + to_string(GetCountryID()) + "\n"
               + "Country Name: " + *country_name_  + "\n"
               + "Occupying Army Value: " + to_string(GetNumberOfArmies()) + "\n"
               + "Continent: " + to_string(GetContinentID()) + "\n";
    } else {
        return "";
    }

}

// END OF COUNTRY CLASS ----------------------------------------------------------------------------------------