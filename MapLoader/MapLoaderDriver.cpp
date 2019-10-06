/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include <iostream>
#include "MapLoader.h"
#include "../Map/Map.h"

using namespace std;


int main()
{
    // Classes within map cannot be linked from MapLoader
    // Map* america = new Map("America map", 2, 5);


    MapLoader *m = new MapLoader();
    m->ParseMap("/Users/raniaAZ/Downloads/europass/europass.map");
}
