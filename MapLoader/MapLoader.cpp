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

//constructors
MapLoader::MapLoader() {
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

    // Verify that [Map] exists but skip over it to continents
    if ((line = ReadLine(fileReader)) != "[Map]") {
        fileReader.close();
        throw invalid_argument("Map file is invalid, missing [Map] section.");
    }

    line = ReadLine(fileReader);
    while (!fileReader.eof()) {
        //parse stuff from file here

        line = ReadLine(fileReader);
    }




    fileReader.close();
}