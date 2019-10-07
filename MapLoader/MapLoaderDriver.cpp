/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

#include <iostream>

#include "MapLoader.h"
using namespace std;


int main()
{
    cout << "Testing MapLoader Driver" << endl << endl;
    cout << endl << "Loading various map files to generate maps... " << endl << "----------------------------------------" << endl << endl;
    //various custom test cases
    MapLoader* testmap1 = new MapLoader("test-map-files/generaltest.map");
    testmap1->ParseMap();

    MapLoader* testmap2 = new MapLoader("test-map-files/emptyfiletest.map");
    testmap2->ParseMap();

    MapLoader* testmap3 = new MapLoader("test-map-files/invalidContinentFormat.map");
    testmap3->ParseMap();

    MapLoader* testmap4 = new MapLoader("test-map-files/invalidCountryFormat.map");
    testmap4->ParseMap();

    MapLoader* testmap5 = new MapLoader("test-map-files/invalidBorderFormat.map");
    testmap5->ParseMap();

    MapLoader* testmap6 = new MapLoader("test-map-files/invalidHeaders.map");
    testmap6->ParseMap();

    MapLoader* testmap7 = new MapLoader("test-map-files/missingborder.map");
    testmap7->ParseMap();

    MapLoader* testmap8 = new MapLoader("test-map-files/missingcontinents.map");
    testmap8->ParseMap();

    MapLoader* testmap9 = new MapLoader("test-map-files/missingcountries.map");
    testmap9->ParseMap();

    MapLoader* testmap10 = new MapLoader("test-map-files/random.map");
    testmap10->ParseMap();

    MapLoader* testmap11 = new MapLoader("test-map-files/countriesNotInOrder.map");
    testmap11->ParseMap();

    //testing some of the provided maps from soundforge
    MapLoader* testmap12 = new MapLoader("test-map-files/bigeurope.map");
    testmap12->ParseMap();

    MapLoader* testmap13 = new MapLoader("test-map-files/Falkland-Islands.map");
    testmap13->ParseMap();

    MapLoader* testmap14 = new MapLoader("test-map-files/google.map");
    testmap14->ParseMap();

    MapLoader* testmap15 = new MapLoader("test-map-files/solar.map");
    testmap15->ParseMap();

    MapLoader* testmap16 = new MapLoader("test-map-files/kosova.map");
    testmap16->ParseMap();


    //TODO figure out why exit code 11 when deleting pointers
//    delete testmap1;
//    delete testmap2;
//    delete testmap3;
//    delete testmap4;
//    delete testmap5;
//    delete testmap6;
//    delete testmap7;
//    delete testmap8;
//    delete testmap9;
//    delete testmap10;
//    delete testmap11;
//    delete testmap12;
//    delete testmap13;
//    delete testmap14;
//    delete testmap15;
//    delete testmap16;

    return 0;
}
