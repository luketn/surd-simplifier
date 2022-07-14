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
  duration<double, std::milli> lukeTime = system_clock::now() - lukeStart;
  cout << "Luke's performance: " << lukeTime.count() << "ms" << endl;
  cout << "Testing jett's performance" << endl;
  auto jettStart = system_clock::now();
  for (int radicand = 2; radicand <= MAX_RADICAND; radicand++) {
    jettResults.push_back(jett::calculateSurds(radicand));
  }
  duration<double, std::milli> jettTime = system_clock::now() - jettStart;
  cout << "Jett's performance: " << jettTime.count() << "ms" << endl;
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
  double lukePercentage = (double)lukeTime.count() / jettTime.count();
  double jettPercentage = (double)jettTime.count() / lukeTime.count();
  if (lukePercentage > 1) {
    cout << "Luke's performance is " << lukePercentage
         << " times slower than Jett's." << endl;
  } else {
    cout << "Jett's performance is " << jettPercentage
         << " times faster than Luke's." << endl;
  }
  uint64_t lukeMeanOperationDurationNanos =
      (double)lukeTime.count() / lukeResults.size() * 1000000000;
  uint64_t jettMeanOperationDurationNanos =
      (double)jettTime.count() / jettResults.size() * 1000000000;
  cout << "Luke's mean operation duration: " << lukeMeanOperationDurationNanos
       << "ns" << endl;
  cout << "Jett's mean operation duration: " << jettMeanOperationDurationNanos
       << "ns" << endl;
  return 0;
}
