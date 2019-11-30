//
// Created by Giselle Martel on 2019-11-26.
//

#include "Continent.h"


// START OF CONTINENT CLASS FUNCTIONS  -----------------------------------------------------------------

Continent::Continent(string* continent_name, int army_value, int continent_id){
    continent_name_ = continent_name;
    army_value_ = army_value;
    continent_ID_ = continent_id;
    color_= new string("");
    countries_in_continent_ = new vector<Country*>;
}

Continent::Continent(const Continent &continent) {
    *continent_name_ = *continent.continent_name_;
    continent_ID_ = continent.continent_ID_;
    army_value_ = continent.army_value_;
    *color_ = *continent.color_;

    *countries_in_continent_ = *continent.countries_in_continent_;
    for(size_t i = 0; i < continent.countries_in_continent_->size(); ++i) {
        (*countries_in_continent_)[i] = (*continent.countries_in_continent_)[i];
        delete (*continent.countries_in_continent_)[i];
        (*continent.countries_in_continent_)[i] = nullptr;
    }

    delete continent.continent_name_;
    delete continent.color_;
    delete continent.countries_in_continent_;
}

Continent::~Continent() {
    if(continent_name_ && !continent_name_->empty()) {
        delete continent_name_;
        continent_name_ = nullptr;
    }

    if(color_){
        delete color_;
        color_ = nullptr;
    }

    if(!continent_name_) {
        return;
    }
}

Continent& Continent::operator=(const Continent &continent) {
    *continent_name_ = *continent.continent_name_;
    continent_ID_ = continent.continent_ID_;
    army_value_ = continent.army_value_;
    *color_ = *continent.color_;

    if(countries_in_continent_) {
        *countries_in_continent_ = *continent.countries_in_continent_;
        for(size_t i = 0; i < continent.countries_in_continent_->size(); ++i) {
            (*countries_in_continent_)[i] = (*continent.countries_in_continent_)[i];
            delete (*continent.countries_in_continent_)[i];
            (*continent.countries_in_continent_)[i] = nullptr;
        }
        delete continent.countries_in_continent_;
    }

    delete continent.continent_name_;
    delete continent.color_;

    return *this;
}

bool Continent::operator==(const Continent &continent) {
    bool is_equal = true;

    is_equal &= *continent_name_ == *continent.continent_name_;
    is_equal &= continent_ID_ == continent.continent_ID_;

    return is_equal;
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

vector<Country*>* Continent::GetCountriesInContinent() const{
    return countries_in_continent_;
}

void Continent::AddCountryToContinent(Country* country){
    //need to add condition to check if country is already in any other continent
    if(!countries_in_continent_) {
        countries_in_continent_ = new vector<Country*>;
    }
    if(!countries_in_continent_->empty()) {
        for(Country* country_in_continent :  *countries_in_continent_) {
            if(country_in_continent == country) {
                cout << "Country already in continent";
                return;
            }
        }
    }

    countries_in_continent_->push_back(country);
}

void Continent::DisplayInfo() const{
    cout
            <<"Continent ID: "<< GetContinentID() <<endl
            <<"Continent Name: "<< *GetContinentName()<<endl
            <<"Continent Army Value: "<< GetContinentArmyValue()<<endl<<endl;
}
