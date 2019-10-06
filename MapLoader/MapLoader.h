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

using namespace std;

class MapLoader {

private:
    Map* parsed_map_;
    void ParseMap(string file_name);

public:
    //Constructor
    MapLoader(string file_name);
};

#endif //MAP_LOADER_H
