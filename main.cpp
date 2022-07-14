#include "implementations.h"
#include <chrono>
#include <iostream>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::chrono::system_clock;

using namespace surd;

static const unsigned MAX_RADICAND = 999999;

int main() {
  vector<vector<Surd>> lukeResults;
  vector<vector<Surd>> jettResults;
  // Warm them both up.
  for (int i = 0; i < 10; i++) {
    luke::calculateSurds(MAX_RADICAND);
    jett::calculateSurds(MAX_RADICAND);
  }
  cout << "Testing luke's performance" << endl;
  auto lukeStart = system_clock::now();
  for (int radicand = 2; radicand <= MAX_RADICAND; radicand++) {
    lukeResults.push_back(luke::calculateSurds(radicand));
  }
  auto lukeTime = system_clock::now() - lukeStart;
  cout << "Luke's performance: " << lukeTime.count() << "ns" << endl;
  cout << "Testing jett's performance" << endl;
  auto jettStart = system_clock::now();
  for (int radicand = 2; radicand <= MAX_RADICAND; radicand++) {
    jettResults.push_back(jett::calculateSurds(radicand));
  }
  auto jettTime = system_clock::now() - jettStart;
  cout << "Jett's performance: " << jettTime.count() << "ns" << endl;
  if (jettResults.size() != lukeResults.size()) {
    cerr << "OOPS! The sizes don't match!" << endl;
  }
  for (unsigned i = 0; i < lukeResults.size(); i++) {
    if (jettResults[i] != lukeResults[i]) {
        cerr << "OOPS! The results don't match!" << endl;
        cerr << "Luke's:" << endl;
        for (const auto &surd : lukeResults[i]) {
            cerr << surd << endl;
        }
        cerr << "Jett's:" << endl;
        for (const auto &surd : jettResults[i]) {
            cerr << surd << endl;
        }
    }
  }
  return 0;
}
