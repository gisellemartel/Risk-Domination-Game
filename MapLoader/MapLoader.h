/**
 * Assignment #1 COMP345, FALL 2019, Dr. Joey Paquet
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include <string>
#include <fstream>

#include "../Map/Map.h"

class MapLoader {
private:
    Map* parsed_map_;

    //helper functions
    string ReadLine(ifstream&);
    void ParseMap(string file_name);


public:
    //Constructor
    MapLoader(string file_name);
    ~MapLoader();

    //methods
    Map* GetParsedMap() const;
};

#endif //MAP_LOADER_H
