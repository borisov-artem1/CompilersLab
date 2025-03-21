#pragma once
#include "../base_automat/automat.h"
namespace automat {


    class NFA : public baseAutomat {
    public:
        automat createBaseAutomat(char symbol, int& counter) override;
        State* createState(int& counter) override;
        //automat createBaseNFA(char symbol);
        automat baseConcat(const automat& firsAutomat, const automat& secondAutomat) override;
        automat baseKleene(const automat& firsAutomat, int& counter) override;
        automat baseAlternate(const automat& firsAutomat, const automat& secondAutomat, int& counter) override;
        explicit NFA(State* start = nullptr, State* end = nullptr): baseAutomat(start, end) {};
        [[nodiscard]] bool acceptString(const automat& Automat, const std::string& baseString) override;
        void getEpsilonClojure(State* state, std::set<State*>& visitor) override;
    };

}




