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
        auto start = std::make_shared<State>();
        auto accept = std::make_shared<State>();
        try
        {
            start.reset(this->createState());
            accept.reset(this->createState());
        } catch(const std::exception& e)
        {
            std::cout << "Error: in function baseAlternate" << e.what() << std::endl;
            throw;
        }
        start->transitions.insert({'\0', firsAutomat.start});
        start->transitions.insert({'\0', secondAutomat.start});
        firsAutomat.accept->transitions.insert({'\0', accept.get()});
        secondAutomat.accept->transitions.insert({'\0', accept.get()});
        return {start.get(), accept.get()};

    }

    automat NFA::baseConcat(const automat& firsAutomat, const automat& secondAutomat)
    {
        firsAutomat.accept->transitions.insert({'\0', secondAutomat.start});
        return {firsAutomat.start, secondAutomat.accept};
    }

    automat NFA::baseKleene(const automat& firsAutomat)
    {
        auto start = std::make_shared<State>();
        auto accept = std::make_shared<State>();
        try
        {
            start.reset(this->createState());
            accept.reset(this->createState());
        } catch (const std::exception& e)
        {
            std::cout << "Error: in function baseKleene" << e.what() << std::endl;
        }
        start->transitions.insert({'\0', firsAutomat.start});
        start->transitions.insert({'\0', accept.get()});
        firsAutomat.accept->transitions.insert({'\0', accept.get()});
        firsAutomat.accept->transitions.insert({'\0', firsAutomat.start});
        return {start.get(), accept.get()};
    }


}