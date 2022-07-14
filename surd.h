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
    out << "Surd[coefficient=" << surd.coefficient << ", radicand=" << surd.radicand << ", message=" << surd.message << "]";
    return out;
}

} // namespace surd

#endif // SURD_SIMPLIFIER_SURD_H
