
#include "Utility.h"

int Utility::GenerateRandomNumInRange(int lower_bound, int upper_bound) {
    uniform_real_distribution<double> distribution(lower_bound, upper_bound);
    random_device rd;
    default_random_engine generator( rd() );
    return distribution(generator);
}

//returns true if finds passed value within passed vector
bool Utility::HasValue(const vector<int>& values, const int value) {
    for(int i : values) {
        if(i == value) {
            return true;
        }
    }
    return false;
}

//returns true if all values in passed vector are 0
bool Utility::ContainsAllZeros(const vector<int> &vector_to_check) {
    bool result = std::all_of(vector_to_check.begin(), vector_to_check.end(), [](int i) {
        return i == 0;
    });

    return result;
}

void Utility::ClearScreen() {
    cout << string(100, '\n');
}

