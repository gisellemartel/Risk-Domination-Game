/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../Map/Map.h"

class MapLoader {
private:
    Map* map_;
    string ReadLine(ifstream&);
    string strip(string);
    vector<string> split(string,char);

    vector<Continent *> *continents_;
    vector<Country *> *countries_;
    vector<Boarder *> *boarders_;

public:
    //Constructor
    MapLoader();
    MapLoader(string);
    ~MapLoader();

    //methods
    Map* GetMap() const;
    void ParseMap(string);
};

#endif //MAPLOADER_H
