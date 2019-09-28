/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "MapLoader.h"

using namespace std;
//forward declarations
class Country;
class Continent;

//helper functions
string MapLoader::ReadLine(ifstream&) {
    return "";
}

void MapLoader::ParseMap(string file_name) {
    string line;
    ifstream file_to_load(file_name);
    bool file_is_valid = true;
    vector<Country*>* countries;
    vector<Continent*>* continents;

    if(file_to_load.is_open()) {

        //read contents of .map file line by line
        while ( getline (file_to_load,line) )
        {
            //if line is empty or line is comment, skip it
           if(line.length() == 0 ||  line.at(0) == ';') {
               continue;
           }

           if(line.find("[continents]")) {
               //get the next line
               while(getline (file_to_load,line)) {
                   int n = line.length();
                   bool b = line.find("[");
                   //we have reached the end of the continents section
                   if(line.length() == 0 || line.find("[")) {
                       break;
                   } else {
                       string continent_data = line;
                       cout << continent_data << endl;
                   }
               }
           }

           if(line.find("[countries]")) {
               //get the next line
               while(getline (file_to_load,line)) {
                   //we have reached the end of the continents section
                   if(line.length() == 0 || line.find("[")) {
                       break;
                   } else {
                       string country_data = line;
                       cout << country_data << endl;
                   }
               }
           }

           if(line.find("[borders]")) {
               //get the next line
               while(getline (file_to_load,line)) {
                   //we have reached the end of the continents section
                   if(line.length() == 0 || line.find("[")) {
                       break;
                   } else {
                       string border_data = line;
                       cout << border_data << endl;
                   }
               }
           }
        }

        file_to_load.close();
    } else {
        //throw an error
        cout << "unable to open the file " << file_name << ". Please try again" << endl;
    }


}

//Constructor
MapLoader::MapLoader(string file_name) {

    ParseMap(file_name);
}

MapLoader::~MapLoader() {
    //delete parsed_map_;
}

//methods
Map* MapLoader::GetParsedMap() const {
    return parsed_map_;
}