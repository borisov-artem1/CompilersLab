#pragma once
#include "automat.h"
namespace automat {

    class algForAuto {
      public:
        algForAuto() = default;
        [[nodiscard]] static automat buildNFAfromPostfixString(const std::string& postfixString);
        automat buildDFAfromNFA(const automat& nfa);
        void printNFA(State* state, std::set<int>& visited) const;
    };
}




