//
// Created by Luke Thompson on 14/7/2022.
//

#include "surd.h"
#include <iostream>

using namespace surd;
using namespace std;

int main() {
    Surd surds[] = {
            {
                    .coefficient=1,
                    .radicand=612,
                    .message=""

            },
            {
                .coefficient=2,
                .radicand=153,
                .message="612 divisible by first square number 4."
            },
            {
                .coefficient=6,
                .radicand=17,
                .message="153 divisible by second square number 9 (rule of 9)."
            }
    };
    for (const auto surd: surds) {
        cout << surd << endl;
    }
    return 0;
}