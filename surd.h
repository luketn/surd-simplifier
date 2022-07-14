#ifndef SURD_SIMPLIFIER_SURD_H
#define SURD_SIMPLIFIER_SURD_H
#include <iostream>
#include <string>

namespace surd {

struct Surd {
  unsigned coefficient;
  unsigned radicand;
  std::string message;
};
static std::ostream &operator<<(std::ostream &out, const Surd &surd) {
    if (surd.message.length() != 0) {
        out << surd.message << " ";
    }
    if (surd.coefficient > 1) {
        out << surd.coefficient << "x ";
    }
    out << "sqrt(" << surd.radicand << ")";
    return out;
}

} // namespace surd

#endif // SURD_SIMPLIFIER_SURD_H
