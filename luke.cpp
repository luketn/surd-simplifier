#include "surd.h"
#include <iostream>
#include <vector>

using namespace surd;
using namespace std;

static optional<Surd> testOfFour(unsigned int radicand,
                                 unsigned int previousCoefficient) {
    string stringRadicand = to_string(radicand);
    unsigned stringRadicandLength = stringRadicand.length();
    string lastTwoChars;
    if (stringRadicandLength >= 2) {
        lastTwoChars = stringRadicand.substr(stringRadicandLength - 2);
    } else {
        lastTwoChars = stringRadicand;
    }
    unsigned lastTwo = stoi(lastTwoChars);
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
    string stringRadicand = to_string(radicand);
    unsigned stringRadicandLength = stringRadicand.length();
    if (stringRadicandLength >= 2) {
        string lastTwoChars = stringRadicand.substr(stringRadicandLength - 2);
        if (lastTwoChars == "00" || lastTwoChars == "25" || lastTwoChars == "50" ||
            lastTwoChars == "75") {
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
    unsigned int originalRadicand = radicand;
    while (true) {
        string stringRadicand = to_string(radicand);
        unsigned stringRadicandLength = stringRadicand.length();
        if (stringRadicandLength > 1) {
            radicand = 0;
            for (int i = 0; i < stringRadicandLength; i++) {
                unsigned charInt = stringRadicand[i] - '0';
                radicand += charInt;
            }
        } else {
            break;
        }
    }
    if (radicand == 9) {
        return Surd{.radicand = originalRadicand / 9,
                .coefficient = 3 * previousCoefficient,
                .workingStep = WorkingStep{
                        .squareNumber = 9,
                        .divisibilityRule = surd::DivisibilityRule::NINE,
                        .previousRadicand = originalRadicand}};
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
    vector<Surd> calculateSurds(unsigned radicand) {
        vector<Surd> result = {};

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

    int main() {
        cout << "Enter a whole number value to simplify a surd: √";
        int radicand;
        cin >> radicand;
        cout << "Calculating the simplified surd for the sqrt(" << radicand << ")"
             << endl;
        vector<Surd> surds = calculateSurds(radicand);
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
} // namespace luke
