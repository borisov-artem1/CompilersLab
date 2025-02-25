#pragma once
#include <iostream>
#include <memory>
#include <set>
#include <vector>


namespace automat {
    static int counter = 0;
    struct State
    {
        int id = 0;
        std::set<std::pair<char, State*>> transitions;
    };

    struct automat
    {
        State* start;
        State* accept;
    };

    class baseAutomat {
    friend class algForAuto;
    public:
        virtual ~baseAutomat() = default;
        explicit baseAutomat(State* start, State* end);
        virtual State* createState() = 0;
        virtual automat createBaseAutomat(char symbol) = 0;
        virtual automat baseConcat(const automat& firsAutomat, const automat& secondAutomat) = 0;
        virtual automat baseKleene(const automat& Automat) = 0;
        virtual automat baseAlternate(const automat& firsAutomat, const automat& secondAutomat) = 0;
        virtual bool acceptString(const automat& Automat, const std::string& baseString) = 0;
        virtual void getEpsilonClojure(State* state, std::set<State*>& visitor) = 0;

    protected:
        State* start;
        State* accept;
    };
}