/**
 * Assignment #1 COMP345, FALL 2019, Dr. Joey Paquet
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../Map/Map.h"

class MapLoader {
private:
    Map* parsed_map_;

    //helper functions
    string ReadLine(ifstream&);
    void ParseMap(string file_name);


    vector<Continent *> *continents_;
    vector<Country *> *countries_;
    vector<Boarder *> *boarders_;

public:
    //Constructor
    MapLoader(string file_name);
    ~MapLoader();

    //methods
    Map* GetParsedMap() const;
};

#endif //MAP_LOADER_H
