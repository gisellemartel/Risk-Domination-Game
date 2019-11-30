
#include "Utility.h"

int Utility::GenerateRandomNumInRange(int lower_bound, int upper_bound) {
    uniform_real_distribution<double> distribution(lower_bound, upper_bound + 1);
    random_device rd;
    default_random_engine generator( rd() );
    return distribution(generator);
}

int Utility::PromptUserNumericalInput(int lower_bound, int upper_bound) {
    int user_selection = -1;
    while (!(cin >> user_selection) || user_selection < lower_bound || user_selection > upper_bound) {
        cout << "Invalid selection! Please try again: ";
        cin.clear();
        cin.ignore(132, '\n');
    }
    return user_selection;
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

string Utility::StripString(string string_to_strip, const string &left_delim, const string &right_delim) {
    if (
            (left_delim.length() == 0 && right_delim.length() == 0)
            || (string_to_strip.length() < 2)
            || (!string_to_strip.find(left_delim) && !string_to_strip.find(right_delim))
            ) {
        return string_to_strip;
    }

    if (left_delim.length() == 0) {
        return string_to_strip.substr(0, string_to_strip.find(right_delim));
    }

    if (right_delim.length() == 0) {
        return string_to_strip.substr(string_to_strip.find(left_delim) + 1, string_to_strip.length() - 1);
    }

    if (string_to_strip.length() > 2) {
        int left_index = string_to_strip.find(left_delim);
        if (left_index > -1 && left_index < string_to_strip.length()) {
            string_to_strip = string_to_strip.substr(left_index);
        }

        int right_index = string_to_strip.find(right_delim) - 1;
        if (right_index > -1 && right_index < string_to_strip.length() - 1) {
            return string_to_strip.substr(1, right_index);
        }
    }
    return string_to_strip;
}
