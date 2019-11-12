#ifndef UTILITY_H
#define UTILITY_H

class Utility {
public:
    static int GenerateRandomNumInRange(int lower_bound, int upper_bound);
    static bool HasValue(const vector<int>& values, const int value);
    static bool ContainsAllZeros(const vector<int> &vector_to_check);
};

#endif //UTILITY_H