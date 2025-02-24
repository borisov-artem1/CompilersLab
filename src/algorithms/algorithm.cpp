#include <stack>
#include "../automat/NFA/NFA.h"
#include "algorithm.h"



namespace automat
{
    automat algForAuto::buildNFAfromPostfixString(const std::string& postfixString)
    {
        std::stack<automat> nfaStack;
        NFA nfa;
        for (const auto& postfix : postfixString)
        {
            if (std::isalnum(postfix))
            {
                nfaStack.push(nfa.createBaseAutomat(postfix));
            } else if (postfix == '.')
            {
                automat secondAutomat = nfaStack.top();
                nfaStack.pop();
                automat firstAutomat = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(nfa.baseConcat(firstAutomat, secondAutomat));
            } else if (postfix == '*')
            {
                automat Automat = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(nfa.baseKleene(Automat));
            } else if (postfix == '|')
            {
                automat secondAutomat = nfaStack.top();
                nfaStack.pop();
                automat firstAutomat = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(nfa.baseAlternate(firstAutomat, secondAutomat));
            } else if (postfix == '+')
            {

            }
        }
        return nfaStack.top();
    }

    void algForAuto::printNFA(State* state, std::set<int>& visited) const
    {
        if (visited.contains(state->id)) { return; }
        visited.insert(state->id);

        for (const auto& [symbol, nextState] : state->transitions)
        {
            std::cout << "State " << state->id << " --(" << (symbol == '\0' ? "e" : std::string(1, symbol)) << ")--> State " << nextState->id << std::endl;
            printNFA(nextState, visited);
        }
    }

    automat algForAuto::buildDFAfromNFA(const automat& NFA)
    {
    }

    void algForAuto::printDFA(const automat& DFA) const
    {

    }




}
