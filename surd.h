//
// Created by Luke Thompson on 14/7/2022.
//

#ifndef SURD_SIMPLIFIER_SURD_H
#define SURD_SIMPLIFIER_SURD_H
#include <string>
#include <iostream>

namespace surd {

    struct Surd {
        unsigned coefficient;
        unsigned radicand;
        std::string message;
    };
    static std::ostream& std::ostream::operator<<(const Surd& surd) {

    }



} // surd

#endif //SURD_SIMPLIFIER_SURD_H
