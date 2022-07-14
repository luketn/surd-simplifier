#include "surd.h"
#include <iostream>
#include <vector>

using namespace surd;
using namespace std;


optional<Surd> testOfFour(unsigned int radicand) {
    string stringRadicand = to_string(radicand);
    unsigned stringRadicandLength = stringRadicand.length();
    if (stringRadicandLength >= 2) {
        string lastTwoChars = stringRadicand.substr(stringRadicandLength - 2);
        unsigned lastTwo = stoi(lastTwoChars);
        if (lastTwo % 4 == 0) {
            //Rule of 4!
            return Surd{
                    .radicand = radicand / 4,
                    .coefficient = 2,
                    .workingStep = WorkingStep{
                            .previousRadicand = radicand,
                            .divisibilityRule =DivisibilityRule::FOUR,
                            .squareNumber = 4
                    }
            };
        }
    }
    return {};
}

optional<Surd> testOfNine(unsigned int radicand) {
    unsigned int originalRadicand = radicand;
    while(true) {
        string stringRadicand = to_string(radicand);
        unsigned stringRadicandLength = stringRadicand.length();
        if (stringRadicandLength > 1) {
            radicand = 0;
            for (int i = 0; i < stringRadicandLength; i++) {
                unsigned charInt = stringRadicand[i] - '0';
                radicand+=charInt;
            }
        } else {
            break;
        }
    }
    if (radicand == 9) {
        return Surd{
            .radicand = originalRadicand / 9,
            .coefficient = 3,
            .workingStep = WorkingStep{
                    .squareNumber = 9,
                    .divisibilityRule = surd::DivisibilityRule::NINE,
                    .previousRadicand = originalRadicand
            }
        };
    } else {
        return {};
    }
}

optional<Surd> calculateNextSurd(Surd previousSurd) {
    optional<Surd> result = {};
    result = testOfFour(previousSurd.radicand);
    if (!result) {
        result = testOfNine(previousSurd.radicand);
    }

    return result;
}

vector<Surd> calculateSurds(unsigned radicand) {
    vector<Surd> result = {};

    Surd initialSurd = Surd{
            .radicand=radicand
    };
    result.push_back(initialSurd);

    Surd previousSurd = initialSurd;
    while(true) {
        auto nextSurd = calculateNextSurd(previousSurd);
        if (nextSurd) {
            result.push_back(nextSurd.value());
            previousSurd = nextSurd.value();
        } else {
            break;
        }
    }
    return result;
}

int main() {
    cout << "Enter a whole number value to simplify a surd: √";
    int radicand;
    cin >> radicand;
    cout << "Calculating the simplified surd for the sqrt(" << radicand << ")" << endl;
    vector<Surd> surds = calculateSurds(radicand);
    for (const auto &surd: surds) {
        if (surd.workingStep) {
            cout << surd << endl;
        }
    }
    return 0;
}