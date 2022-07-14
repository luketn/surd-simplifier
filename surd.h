#ifndef SURD_SIMPLIFIER_SURD_H
#define SURD_SIMPLIFIER_SURD_H

#include <iostream>
#include <map>
#include <optional>
#include <string>

namespace surd {
    enum class DivisibilityRule {
        TRIAL_AND_ERROR, FOUR, NINE, TWENTY_FIVE
    };
    static std::map<DivisibilityRule, std::string> divisibilityRuleNames = {
            {DivisibilityRule::TRIAL_AND_ERROR, "trial and error"},
            {DivisibilityRule::FOUR,            "4"},
            {DivisibilityRule::NINE,            "9"},
            {DivisibilityRule::TWENTY_FIVE,     "25"}};

    struct WorkingStep {
        unsigned previousRadicand;
        unsigned squareNumber;
        DivisibilityRule divisibilityRule;
    };
    static std::ostream &operator<<(std::ostream &out, const WorkingStep &step) {
        out << step.previousRadicand << " was divisible by " << step.squareNumber
            << " (found using the rule of " << divisibilityRuleNames[step.divisibilityRule]
            << ")";
        return out;
    }

    struct Surd {
        unsigned coefficient = 0;
        unsigned radicand = 0;
        std::optional<WorkingStep> workingStep = {};
    };

    static std::ostream &operator<<(std::ostream &out, const Surd &surd) {
        if (surd.workingStep) {
            out << surd.workingStep.value();
        }
        if (surd.coefficient > 1) {
            out << " giving a simplified surd of " << surd.coefficient << " * sqrt(" << surd.radicand << ")";
        }
        return out;
    }

} // namespace surd

#endif // SURD_SIMPLIFIER_SURD_H
