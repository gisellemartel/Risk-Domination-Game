/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include "MapLoader.h"

#include <iostream>
using namespace std;


int main()
{
    cout << "Map Loader Driver" << endl;

    MapLoader* map_to_load = new MapLoader("test-map-files/bigeurope.map");


    delete map_to_load;
    return 0;
}
