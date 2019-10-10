/**
 * Assignment #1 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */


#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "../Map/Map.h"

#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class MapLoader {

private:
    string file_name_;
    Map* parsed_map_;

public:
    MapLoader(string file_name);
    MapLoader(const MapLoader &map);
    ~MapLoader();

    MapLoader& operator=(const MapLoader& map);

    Map* GetParsedMap() const;

    void ParseMap();
    string StripString(string string_to_strip, string left_delim, string right_delim);
};

#endif //MAP_LOADER_H
