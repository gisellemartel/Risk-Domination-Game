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
class Border;

//constructors
//MapLoader::MapLoader() {
//    continents_ = new vector<Continent *>;
//    countries_ = new vector<Country *>;
//    boarders_ = new vector<Boarder *>;
//}

MapLoader::MapLoader(string file_name) {
    ParseMap(file_name);
}

MapLoader& MapLoader::operator=(const MapLoader &map_loader) {
    continents_ = map_loader.continents_;
    countries_ = map_loader.countries_;
    borders_ = map_loader.borders_;
    return *this;
}

MapLoader::~MapLoader() {
   delete continents_;
   delete countries_;
   delete borders_;
}

MapLoader::MapLoader(const MapLoader &map_loader) {
    continents_ = map_loader.continents_;
    countries_ = map_loader.countries_;
    borders_ = map_loader.borders_;
}
//
//void MapLoader::ParseMap(string file_name) {
//    string line;
//    ifstream file_to_load(file_name);
//    bool file_is_valid = true;
//    vector<Country*>* countries;
//    vector<Continent*>* continents;
//
//    if(file_to_load.is_open()) {
//
//        //read contents of .map file line by line
//        while ( getline (file_to_load,line) )
//        {
//            //if line is empty or line is comment, skip it
//           if(line.length() == 0 ||  line.at(0) == ';') {
//               continue;
//           }
//
//           if(line.find("[continents]")) {
//               //get the next line
//               while(getline (file_to_load,line)) {
//                   int n = line.length();
//                   bool b = line.find("[");
//                   //we have reached the end of the continents section
//                   if(line.length() == 0 || line.find("[")) {
//                       break;
//                   } else {
//                       string continent_data = line;
//                       cout << continent_data << endl;
//                   }
//               }
//           }
//
//           if(line.find("[countries]")) {
//               //get the next line
//               while(getline (file_to_load,line)) {
//                   //we have reached the end of the continents section
//                   if(line.length() == 0 || line.find("[")) {
//                       break;
//                   } else {
//                       string country_data = line;
//                       cout << country_data << endl;
//                   }
//               }
//           }
//
//           if(line.find("[borders]")) {
//               //get the next line
//               while(getline (file_to_load,line)) {
//                   //we have reached the end of the continents section
//                   if(line.length() == 0 || line.find("[")) {
//                       break;
//                   } else {
//                       string border_data = line;
//                       cout << border_data << endl;
//                   }
//               }
//           }
//        }
//
//        file_to_load.close();
//    } else {
//        //throw an error
//        cout << "unable to open the file " << file_name << ". Please try again" << endl;
//    }
//
//
//}

//methods
Map* MapLoader::GetParsedMap() const {
    return parsed_map_;
}

// Helper function to strip \r or \n at the right end of the string
string MapLoader::Strip(string s) {
    while (s[s.length() - 1] == '\r' || s[s.length() - 1] == '\n') {
        s.pop_back();
    }
    return s;
}

// Helper function to split strings
vector<string> MapLoader::Split(string s, char delim) {
    stringstream ss(s);
    string input;
    vector<string> result;

    while (getline(ss, input, delim)) {
        result.push_back(input);
    }

    return result;
}

string MapLoader::ReadLine(ifstream &) {
    return "";
}


void MapLoader::ParseMap(string textFileName) {
    string line;
    ifstream fileReader(textFileName);

    bool file_is_valid = true;
    vector<Country *> *countries;
    vector<Continent *> *continents;
    string section = "";

    //// Verify that [Map] exists but skip over it to continents
    //if ((line = ReadLine(fileReader)) != "[Map]") {
    //   fileReader.close();
    //   throw invalid_argument("Map file is invalid, missing [Map] section.");
    //}

    //line = this->ReadLine(fileReader);
    while (!fileReader.eof()) {
        //parse stuff from file here
        line = ReadLine(fileReader);

        //if line is empty or line is comment, skip it
        if (line.length() == 0 || line.at(0) == ';') {
            continue;
        } else if (line.find("[") != -1) {
            section = line;
            continue;
        } else if (section.find("[continents]") != -1) {
            std::vector<string> continentData = this->Split(line, ' ');
            string continentName = continentData[0];
            //cout << line << continentData[1] << endl;
            int continentValue = stoi(continentData[1]);
            string continentColor = continentData[2];
            //Continent* continent= new Continent(continentName,continentValue,continentColor);
            //this->continents_->push_back(continent);

            //for testing
            cout << line << endl;

        } else if (section.find("[countries]") != -1) {
            std::vector<string> countriesData = this->Split(line, ' ');
            int country_ID = stoi(countriesData[0]);
            string country_name = countriesData[1];
            int continent_ID = stoi(countriesData[2]);
            int coordinate_x = stoi(countriesData[3]);
            int coordinate_y = stoi(countriesData[4]);
            //Country* country= new Country(country_ID,country_name,continent_ID,coordinate_x,coordinate_y);
            //this->countries_->push_back(country);

            //for testing
            cout << line << endl;

        } else if (section.find("[borders]") != -1) {
            std::vector<string> boardersData = this->Split(line, ' ');
            int country_ID = stoi(boardersData[0]);
            vector<int> boarder_ids;
            for (int i = 1; i < boardersData.size(); i++) {
                boarder_ids.push_back(stoi(boardersData[i]));
            }
            //Boarder* boarder = new Boarder(country_ID, &boarder_ids);

            //for testing
            cout << line << endl;

        } else {
            continue;
        }
//
//         else if (section.find("[borders]")){
//
//        } else if (section.find("files")){
//
//        }

    }

    fileReader.close();
}