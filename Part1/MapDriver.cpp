/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include "Map.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    Map* test_map = new Map("test map", 5, 5);
    delete test_map;
    cout << "Map Driver" << endl;
}
