#include "surd.h"
#include <iostream>
#include <vector>

using namespace surd;
using namespace std;

static optional<Surd> calculateStep(unsigned radicand, unsigned coefficient) {
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
  // We only have to check the squares of prime numbers, since (ab)2 = a2b2.
  // This means that the square of a composite number is divisible by the square
  // of a prime number.
  // I couldn't get that to work efficiently so we just use the 6n+1 rule.
  unsigned squareNumber = 1;
  for (unsigned n = 1; squareNumber <= radicand; n++) {
    // 6n + 1 case.
    unsigned rootNumber = 6 * n - 1;
    squareNumber = rootNumber * rootNumber;
    if (radicand % squareNumber == 0) {
      return Surd{.coefficient = rootNumber * coefficient,
                  .radicand = radicand / squareNumber,
                  .workingStep = WorkingStep{
                      .previousRadicand = radicand,
                      .squareNumber = squareNumber,
                      .divisibilityRule = DivisibilityRule::TRIAL_AND_ERROR}};
    }
    // 6n - 1 case.
    rootNumber = 6 * n + 1;
    squareNumber = rootNumber * rootNumber;
    if (radicand % squareNumber == 0) {
      return Surd{.coefficient = rootNumber * coefficient,
                  .radicand = radicand / squareNumber,
                  .workingStep = WorkingStep{
                      .previousRadicand = radicand,
                      .squareNumber = squareNumber,
                      .divisibilityRule = DivisibilityRule::TRIAL_AND_ERROR}};
    }
  }
  return {};
}

namespace jett {
vector<Surd> calculateSurds(unsigned radicand) {
  unsigned coefficient = 1;
  vector<Surd> surds;
  surds.reserve(8);
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
} // namespace jett
