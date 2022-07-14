#include "surd.h"
#include <iostream>
#include <vector>

using namespace surd;
using namespace std;

vector<Surd> calculateSurds(unsigned radicand) {
    return {Surd{
            .coefficient = 1,
            .radicand = radicand,
    },
            Surd{.coefficient = 2,
                    .radicand = 153,
                    .workingStep = WorkingStep{.squareNumber = 4, .divisibilityRule = surd::DivisibilityRule::FOUR, .previousRadicand = radicand}
            },
            Surd{.coefficient = 6,
                    .radicand = 17,
                    .workingStep = WorkingStep{.squareNumber = 9, .divisibilityRule = surd::DivisibilityRule::NINE, .previousRadicand = 153}
            }
    };
}

int main() {
    cout << "Enter a whole number value to simplify a surd: √";
    int radicand; cin >> radicand;
    cout << "Calculating the simplified surd for the sqrt(" << radicand << ")" << endl;
    vector<Surd> surds = calculateSurds(radicand);
    for (const auto &surd: surds) {
        if (surd.workingStep) {
            cout << surd << endl;
        }
    }
    return 0;
}