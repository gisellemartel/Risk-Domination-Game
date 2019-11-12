
#include <random>

using namespace std;
#include "Utility.h"

int Utility::GenerateRandomNumInRange(int lower_bound, int upper_bound) {
    uniform_real_distribution<double> distribution(lower_bound, upper_bound);
    random_device rd;
    default_random_engine generator( rd() );
    return distribution(generator);
}