#include "NFA.h"


namespace automat
{
    State* NFA::createState()
    {
        return baseAutomat::createState();
    }
    automat NFA::createBaseAutomat(const char symbol) // TODO: maybe bug in there
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
        start->transitions.insert({'\0', firsAutomat.start});
        start->transitions.insert({'\0', secondAutomat.start});
        firsAutomat.accept->transitions.insert({'\0', accept});
        secondAutomat.accept->transitions.insert({'\0', accept});
        return {start, accept};

    }

    automat NFA::baseConcat(const automat& firsAutomat, const automat& secondAutomat)
    {
        firsAutomat.accept->transitions.insert({'\0', secondAutomat.start});
        return {firsAutomat.start, secondAutomat.accept};
    }

    automat NFA::baseKleene(const automat& firsAutomat)
    {
        start = createState();
        accept = createState();
        start->transitions.insert({'\0', firsAutomat.start});
        start->transitions.insert({'\0', accept});
        firsAutomat.accept->transitions.insert({'\0', accept});
        firsAutomat.accept->transitions.insert({'\0', firsAutomat.start});
        return {start, accept};
    }


}