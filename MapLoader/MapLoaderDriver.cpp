/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */
#include <iostream>

#include "MapLoader.h"
using namespace std;

int main()
{
    cout << "Testing MapLoader Driver" << endl << endl;
    cout << "\nLoading various map files to generate maps...\n**************************************************************************************************\n\n";

//    TEST CASES ASSIGNMENT 1 ******************************************************************************************

//    //various custom test cases
//    MapLoader* testmap1 = new MapLoader("domination-map-files/generaltest.map");
//    if(testmap1->ParseMap()) {
//        cout << "Success! Generated map for file generaltest.map!" << endl << "\nHere is the resulting graph:\n";
//        testmap1->GetParsedMap()->DisplayAdjacencyMatrix();
//        cout << "**************************************************************************************************\n\n\n";
//    }
//
//    MapLoader* testmap2 = new MapLoader("domination-map-files/emptyfiletest.map");
//    testmap2->ParseMap();
//
//    MapLoader* testmap3 = new MapLoader("domination-map-files/invalidContinentFormat.map");
//    testmap3->ParseMap();
//
//    MapLoader* testmap4 = new MapLoader("domination-map-files/invalidCountryFormat.map");
//    testmap4->ParseMap();
//
//    MapLoader* testmap5 = new MapLoader("domination-map-files/invalidBorderFormat.map");
//    testmap5->ParseMap();
//
//    MapLoader* testmap6 = new MapLoader("domination-map-files/invalidHeaders.map");
//    testmap6->ParseMap();
//
//    MapLoader* testmap7 = new MapLoader("domination-map-files/missingborder.map");
//    testmap7->ParseMap();
//
//    MapLoader* testmap8 = new MapLoader("domination-map-files/missingcontinents.map");
//    testmap8->ParseMap();
//
//    MapLoader* testmap9 = new MapLoader("domination-map-files/missingcountries.map");
//    testmap9->ParseMap();
//
//    MapLoader* testmap10 = new MapLoader("domination-map-files/random.map");
//    testmap10->ParseMap();
//
//    MapLoader* testmap11 = new MapLoader("domination-map-files/countriesNotInOrder.map");
//    testmap11->ParseMap();
//
//    //testing some of the provided maps from soundforge
//    MapLoader* testmap12 = new MapLoader("domination-map-files/bigeurope.map");
//    testmap12->ParseMap();
//
//    MapLoader* testmap13 = new MapLoader("domination-map-files/Falkland-Islands.map");
//    testmap13->ParseMap();
//
//    MapLoader* testmap14 = new MapLoader("domination-map-files/google.map");
//    testmap14->ParseMap();
//
//    MapLoader* testmap15 = new MapLoader("domination-map-files/solar.map");
//    testmap15->ParseMap();
//
//    MapLoader* testmap16 = new MapLoader("domination-map-files/kosova.map");
//    testmap16->ParseMap();
//
//    cout << "\n----------------------------------------------------" << endl;
//    cout << "Testing that graph is connected:\n\n";
//    testmap16->GetParsedMap()->DisplayGraphTraversal( testmap16->GetParsedMap()->GetCountryById(30));
//    cout << endl << endl;
//    testmap16->GetParsedMap()->DisplayGraphTraversal( testmap16->GetParsedMap()->GetCountryById(1));

//    delete all map loader objects
//    testmap1 = testmap2 = testmap3 = testmap4 = testmap5 = testmap6 = testmap7 = testmap8 = testmap9 = testmap10 = testmap11 = testmap12 = testmap13 = testmap14 = testmap15 = testmap16 = nullptr;
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
