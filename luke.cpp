#include "surd.h"
#include <iostream>
#include <vector>

using namespace surd;
using namespace std;

static optional<Surd> testOfFour(unsigned int radicand,
                                 unsigned int previousCoefficient) {
    unsigned lastTwo = radicand % 100;
    if (lastTwo % 4 == 0) {
        // Rule of 4!
        return Surd{.radicand = radicand / 4,
                .coefficient = 2 * previousCoefficient,
                .workingStep =
                WorkingStep{.previousRadicand = radicand,
                        .divisibilityRule = DivisibilityRule::FOUR,
                        .squareNumber = 4}};
    }
    return {
    };
}

static optional<Surd> testOfTwentyFive(unsigned int radicand,
                                       unsigned int previousCoefficient) {
    if (radicand > 24) {
        auto lastTwo = radicand % 100;
        if (lastTwo == 0 || lastTwo == 25 || lastTwo == 50 || lastTwo == 75) {
            // Rule of 25!
            return Surd{.radicand = radicand / 25,
                    .coefficient = 5 * previousCoefficient,
                    .workingStep = WorkingStep{.previousRadicand = radicand,
                            .divisibilityRule =
                            DivisibilityRule::TWENTY_FIVE,
                            .squareNumber = 25}};
        }
    }
    return {};
}

static optional<Surd> testOfTrialAndError(unsigned int radicand,
                                          unsigned int previousCoefficient) {
    bool isEven = radicand % 2 == 0;
    for (unsigned int coefficient = 3; coefficient <= radicand;
         coefficient += isEven ? 1 : 2) {
        unsigned int square = coefficient * coefficient;
        if (square > radicand) {
            break;
        }
        if (radicand % square == 0) {
            return Surd{.radicand = radicand / square,
                    .coefficient = coefficient * previousCoefficient,
                    .workingStep = WorkingStep{
                            .previousRadicand = radicand,
                            .divisibilityRule = DivisibilityRule::TRIAL_AND_ERROR,
                            .squareNumber = square}};
        }
    }
    return {};
}

static optional<Surd> testOfNine(unsigned int radicand,
                                 unsigned int previousCoefficient) {

    unsigned int digitsTotal = 0;
    bool resolved = false;
    unsigned int radicandWork = radicand;
    while (!resolved) {
        while (radicandWork > 0) {
            auto workDigit = radicandWork % 10;
            radicandWork = radicandWork / 10;
            digitsTotal += workDigit;
        }
        if (digitsTotal < 10) {
            resolved = true;
        } else {
            radicandWork = digitsTotal;
            digitsTotal = 0;
        }
    }
    if (digitsTotal == 9) {
        return Surd{
                .coefficient = 3 * previousCoefficient,
                .radicand = radicand / 9,
                .workingStep = WorkingStep{
                        .previousRadicand = radicand,
                        .squareNumber = 9,
                        .divisibilityRule = surd::DivisibilityRule::NINE}};
    } else {
        return {};
    }
}

static optional<Surd> calculateNextSurd(Surd previousSurd) {
    optional<Surd> result = {};
    result = testOfFour(previousSurd.radicand, previousSurd.coefficient);
    if (!result) {
        result = testOfNine(previousSurd.radicand, previousSurd.coefficient);
    }
    if (!result) {
        result = testOfTwentyFive(previousSurd.radicand, previousSurd.coefficient);
    }
    if (!result) {
        result =
                testOfTrialAndError(previousSurd.radicand, previousSurd.coefficient);
    }
    return result;
}

namespace luke {
    vector<Surd> result = {};
    vector<Surd> calculateSurds(unsigned radicand) {
        result.clear();

        Surd initialSurd = Surd{.radicand = radicand};
        result.push_back(initialSurd);

        Surd previousSurd = initialSurd;
        while (true) {
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

} // namespace luke
