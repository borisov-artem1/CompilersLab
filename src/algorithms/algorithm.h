#pragma once
#include "../automat/base_automat/automat.h"
#include "../automat/DFA/DFA.h"
namespace automat {

    class algForAuto {
      public:
        algForAuto() = default;
        [[nodiscard]] static automat buildNFAfromPostfixString(std::string& baseString);
        [[nodiscard]] static DFA buildDFAfromNFA(automat& NFA);
        void printNFA(State* state, std::set<int>& visited) const;
        [[nodiscard]] static std::set<State*> epsilonClosure(std::set<State*> states);
        [[nodiscard]] static bool acceptStringForDFA(State* state, const std::string& baseString);
    };
}




