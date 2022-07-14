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
           .radicand = 7,
           .workingStep = WorkingStep{.radicand = 1}}};
}

int main() {
  vector<Surd> surds = calculateSurds(612);
  for (const auto &surd : surds) {
    cout << surd << endl;
  }
  return 0;
}