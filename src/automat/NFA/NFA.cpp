#include "NFA.h"


namespace automat
{
    State* NFA::createState()
    {
        return baseAutomat::createState();
    }
    automat NFA::createBaseAutomat(const char symbol)
    {
        try
        {
            const automat a = baseAutomat::createBaseAutomat(symbol);
            return a;
        } catch(const std::exception& e)
        {
            std::cout << "Error: in function createBaseNFA" << e.what() << std::endl;
            throw;
        }
    }

    automat NFA::baseAlternate(const automat& firsAutomat, const automat& secondAutomat)
    {
        start = createState();
        accept = createState();
        accept->isAccept = true;
        start->transitions.insert({'\0', firsAutomat.start});
        start->transitions.insert({'\0', secondAutomat.start});
        firsAutomat.accept->transitions.insert({'\0', accept});
        secondAutomat.accept->transitions.insert({'\0', accept});
        firsAutomat.accept->isAccept = false;
        secondAutomat.accept->isAccept = false;
        return {start, accept};

    }

    automat NFA::baseConcat(const automat& firsAutomat, const automat& secondAutomat)
    {
        firsAutomat.accept->transitions.insert({'\0', secondAutomat.start});
        firsAutomat.accept->isAccept = false;
        secondAutomat.accept->isAccept = true;
        return {firsAutomat.start, secondAutomat.accept};
    }

    automat NFA::baseKleene(const automat& firsAutomat)
    {
        start = createState();
        accept = createState();
        accept->isAccept = true;
        start->transitions.insert({'\0', firsAutomat.start});
        start->transitions.insert({'\0', accept});
        firsAutomat.accept->transitions.insert({'\0', accept});
        firsAutomat.accept->transitions.insert({'\0', firsAutomat.start});
        firsAutomat.accept->isAccept = false;
        return {start, accept};
    }

    bool NFA::acceptString(const automat& Automat, const std::string& baseString)
    {
        std::set<State*> currentStates;
        getEpsilonClojure(Automat.start, currentStates);

        for (const auto& c : baseString)
        {
            std::set<State*> nextStates;
            for (State* s : currentStates)
            {
                for (auto& [symbol, nextState] : s->transitions)
                {
                    if (symbol == c)
                    {
                        nextStates.insert(nextState);
                    }
                }
            }

            std::set<State*> epsilonExpanded;
            for (State* s : nextStates)
            {
                getEpsilonClojure(s, epsilonExpanded);
            }
            currentStates = epsilonExpanded;
        }
        return currentStates.contains(Automat.accept);
    }

    void NFA::getEpsilonClojure(State* state, std::set<State*>& visitor)
    {
        if (visitor.contains(state)) { return; }
        visitor.insert(state);

        for (const auto& [symbol, nextState] : state->transitions)
        {
            if (symbol == '\0')
            {
                getEpsilonClojure(nextState, visitor);
            }
        }
    }



}