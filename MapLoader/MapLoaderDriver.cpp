/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include <iostream>

#include "MapLoader.h"
using namespace std;


int main()
{
    cout << "Map Loader Driver" << endl;
    // Classes within map cannot be linked from MapLoader
    // Map* america = new Map("America map", 2, 5);

    MapLoader* map_to_load = new MapLoader("test-map-files/bigeurope.map");

    delete map_to_load;
    return 0;
}
