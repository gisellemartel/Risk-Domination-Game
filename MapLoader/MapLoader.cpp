/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include <fstream>
#include <string>
#include <map>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "MapLoader.h"
#include "../Map/Map.h"

using namespace std;
//forward declarations
class Map;
class Country;
class Continent;

class Boarder;

//constructors
MapLoader::MapLoader() {
    continents_ = new vector<Continent *>;
    countries_ = new vector<Country *>;
    boarders_ = new vector<Boarder *>;
}

MapLoader::MapLoader(string file_name) {
    ParseMap(file_name);
}

//deconstructor
MapLoader::~MapLoader() {
    //delete map_;
}

// Helper function for getting whole lines without carriage returns
string MapLoader::ReadLine(ifstream &fileReader) {
    string line;
    if (getline(fileReader, line)) {
        return this->strip(line);
    } else {
        return "";
    }
}

// Helper function to strip \r or \n at the right end of the string
string MapLoader::strip(string s) {
    while (s[s.length() - 1] == '\r' || s[s.length() - 1] == '\n') {
        s.pop_back();
    }
    return s;
}

// Helper function to split strings
vector<string> MapLoader::split(string s, char delim) {
    stringstream ss(s);
    string input;
    vector<string> result;

    while (getline(ss, input, delim)) {
        result.push_back(input);
    }

    return result;
}

Map* MapLoader::GetMap() const {
    return map_;
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
            std::vector<string> continentData = this->split(line, ' ');
            string continentName = continentData[0];
            //cout << line << continentData[1] << endl;
            int continentValue = stoi(continentData[1]);
            string continentColor = continentData[2];
            //Continent* continent= new Continent(continentName,continentValue,continentColor);
            //this->continents_->push_back(continent);

            //for testing
            cout << line << endl;

        } else if (section.find("[countries]") != -1) {
            std::vector<string> countriesData = this->split(line, ' ');
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
            std::vector<string> boardersData = this->split(line, ' ');
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