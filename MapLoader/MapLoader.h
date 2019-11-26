/**
 * Assignment #4 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "../Map/Map.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace std;

//MapLoader class (TARGET) ---------------------------------------------------------------------------------------------
class MapLoader {

private:
    string file_name_;
    Map* parsed_map_;

public:
    MapLoader();
    MapLoader(string file_name);
    MapLoader(const MapLoader& map);
    virtual ~MapLoader();

    MapLoader& operator=(const MapLoader& map);

    Map* GetParsedMap() const;

    virtual bool ParseMap();
};

#endif //MAP_LOADER_H
