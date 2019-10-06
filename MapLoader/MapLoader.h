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
    vector<Continent*>* continents_;
    vector<Country*>* countries_;
    vector<Border*>* borders_;

    //helper functions
    void ParseMap(string file_name);

public:
    //Constructor
    MapLoader(string file_name);
    MapLoader(const MapLoader &map_loader);
    ~MapLoader();
    MapLoader& operator=(const MapLoader &map_loader);

    //methods
    Map* GetParsedMap() const;
};

#endif //MAP_LOADER_H
