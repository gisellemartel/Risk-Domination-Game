//
// Created by Giselle Martel on 2019-09-13.
//

#include "Map.h"
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main()
{
    Map* test_map = new Map();
    delete test_map;
    list <int> numbers;
    numbers.push_back(4);
    numbers.push_back(10);
    numbers.push_back(22);

    list<int>::iterator searchedItem = find(numbers.begin(), numbers.end(), 10);

    cout << "Map Driver" << endl;
}
