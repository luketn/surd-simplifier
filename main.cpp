#include "surd.h"
#include <iostream>
#include <vector>

using namespace surd;
using namespace std;

optional<Surd> calculateStep(unsigned radicand, unsigned coefficient) {
  unsigned lastTwoDigits = radicand % 100;
  // Try rule of four.
  if (lastTwoDigits % 4 == 0) {
    return Surd{.coefficient = 2 * coefficient,
                .radicand = radicand / 4,
                .workingStep =
                    WorkingStep{.previousRadicand = radicand,
                                .squareNumber = 4,
                                .divisibilityRule = DivisibilityRule::FOUR}};
  }
  // Rule of nine.
  // Find the digit sum by getting the remainder of a division by 10 until it is
  // zero. Do this on the digit sum until it is a single digit (< 10).
  unsigned remainingDigits = radicand;
  unsigned digitSum;
  do {
    digitSum = 0;
    while (remainingDigits) {
      digitSum += remainingDigits % 10;
      remainingDigits /= 10;
    }
    remainingDigits = digitSum;
  } while (digitSum >= 10);
  if (digitSum == 9) {
    return Surd{.coefficient = 3 * coefficient,
                .radicand = radicand / 9,
                .workingStep =
                    WorkingStep{.previousRadicand = radicand,
                                .squareNumber = 9,
                                .divisibilityRule = DivisibilityRule::NINE}};
  }
  // Rule of 25.
  if (lastTwoDigits == 0 || lastTwoDigits == 25 || lastTwoDigits == 50 ||
      lastTwoDigits == 75) {
    return Surd{.coefficient = 5 * coefficient,
                .radicand = radicand / 25,
                .workingStep = WorkingStep{.previousRadicand = radicand,
                                           .squareNumber = 25,
                                           .divisibilityRule =
                                               DivisibilityRule::TWENTY_FIVE}};
  }
  // The rule of trial and error.
  // Odd numbers can't be divided by even ones.
  unsigned increment = radicand % 2 == 1 ? 2 : 1;
  for (unsigned n = 3; n * n < radicand; n += increment) {
    if (radicand % (n * n) == 0) {
      return Surd{.coefficient = n * coefficient,
                  .radicand = radicand / n * n,
                  .workingStep = WorkingStep{
                      .previousRadicand = radicand,
                      .squareNumber = n * n,
                      .divisibilityRule = DivisibilityRule::TRIAL_AND_ERROR}};
    }
  }
  return {};
}

vector<Surd> calculateSurds(unsigned radicand) {
  unsigned coefficient = 1;
  vector<Surd> surds;
  surds.push_back(Surd{.coefficient = 1, .radicand = radicand});
  optional<Surd> nextSurd;
  while ((nextSurd = calculateStep(radicand, coefficient))) {
    auto &[nextCoefficient, nextRadicand, workingStep] = nextSurd.value();
    radicand = nextRadicand;
    coefficient = nextCoefficient;
    surds.push_back(nextSurd.value());
  }
  return surds;
}

int main() {
  cout << "Enter a whole number value to simplify a surd: √";
  int radicand;
  cin >> radicand;
  cout << "Calculating the simplified surd for the sqrt(" << radicand << ")"
       << endl;
  vector<Surd> surds = calculateSurds(radicand);
  for (const auto &surd : surds) {
    if (surd.workingStep) {
      cout << surd << endl;
    }
  }
  return 0;
}