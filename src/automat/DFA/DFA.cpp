#include "DFA.h"

#include "../../algorithms/algorithm.h"
#include "../../prep/preprocessing.h"
#include "../../visualization/visualizer.h"
#include "../base_automat/syntaxTree.h"

namespace automat
{
    void DFABuilder::addState(State* s)
    {
        states.insert(s);
    }


    DFA DFABuilder::buildMinimalDFA(std::string& regex)
    {
        automat nfa = algForAuto::buildNFAfromPostfixString(regex);
        DFA dfa = algForAuto::buildDFAfromNFA(nfa);
        DFA minDfa = algForAuto::minimizationDFA(dfa, regex);

        visualizer::exportToDot(minDfa.start, nullptr, "DFA_from_rgx");
        return dfa;
    }

}

