#include <stack>
#include "NFA.h"
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
                automat firstAutomat = nfaStack.top();
                nfaStack.pop();
                automat secondAutomat = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(nfa.baseConcat(firstAutomat, secondAutomat));
            } else if (postfix == '*')
            {
                automat Automat = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(nfa.baseKleene(Automat));
            } else if (postfix == '|')
            {
                automat firstAutomat = nfaStack.top();
                nfaStack.pop();
                automat secondAutomat = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(nfa.baseAlternate(firstAutomat, secondAutomat));
            }
        }
        return nfaStack.top();
    }

    void algForAuto::printNFA(State* state, std::set<int>& visited) const
    {
        if (visited.find(state->id) != visited.end()) { return; }
        visited.insert(state->id);

        for (const auto& [symbol, nextState] : state->transitions)
        {
            std::cout << "State " << state->id << " --(" << (symbol == '\0' ? "ε" : std::string(1, symbol)) << ")--> State " << nextState->id << std::endl;
            printNFA(state, visited);
        }
    }
}
