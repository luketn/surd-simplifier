#include "implementations.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::chrono::duration;
using std::chrono::system_clock;

using namespace surd;

static const unsigned MAX_RADICAND = 999999;

int main() {

    cout << "Enter a whole number value to simplify a surd: √";
    int radicand;
    std::cin >> radicand;
    cout << "Calculating the simplified surd for the sqrt(" << radicand << ")"
         << endl;
    vector<Surd> surds = luke::calculateSurds(radicand);
    if (surds.size() > 1) {
        for (const auto &surd: surds) {
            if (surd.workingStep) {
                cout << surd << endl;
            }
        }
    } else {
        cout << "Could not be simplified.";
    }
    return 0;

}