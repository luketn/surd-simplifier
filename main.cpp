//
// Created by Luke Thompson on 14/7/2022.
//

#include "surd.h"
#include <iostream>
#include <vector>

using namespace surd;
using namespace std;

vector<Surd> calculateSurds(unsigned radicand) {
    return {
            {
                    .coefficient=1,
                    .radicand=radicand
            },
            {
                    .coefficient=2,
                    .radicand=153,
                    .workingStep={
                            .previousRadicand=radicand,
                            .coefficient=2,
                            .squareNumber=4,
                            .radicand=153,
                            .divisibilityRule=DivisibilityRule::FOUR
                    }
            }
    };
}

int main() {
    vector<Surd> surds = calculateSurds(612);
    for (const auto surd: surds) {
        cout << surd << endl;
    }
    return 0;
}