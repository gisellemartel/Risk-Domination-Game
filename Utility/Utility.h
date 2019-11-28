#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <random>
#include <iostream>
using namespace std;

class Utility {
public:
    static int GenerateRandomNumInRange(int lower_bound, int upper_bound);
    static bool HasValue(const vector<int>& values, const int value);
    static bool ContainsAllZeros(const vector<int> &vector_to_check);
    static string StripString(string string_to_strip, const string &left_delim, const string &right_delim);

    static void ClearScreen();
};

#endif //UTILITY_H