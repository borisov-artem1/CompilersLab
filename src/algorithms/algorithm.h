#pragma once
#include "../automat/base_automat/automat.h"
namespace automat {

    class algForAuto {
      public:
        algForAuto() = default;
        [[nodiscard]] static automat buildNFAfromPostfixString(const std::string& postfixString);
        automat buildDFAfromNFA(const automat& NFA);
        void printNFA(State* state, std::set<int>& visited) const;
        void printDFA(const automat& DFA) const;
    };
}




