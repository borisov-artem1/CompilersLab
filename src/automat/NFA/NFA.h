#pragma once
#include "../base_automat/automat.h"
namespace automat {


    class NFA : public baseAutomat {
    public:
        automat createBaseAutomat(char symbol) override;
        State* createState() override;
        //automat createBaseNFA(char symbol);
        automat baseConcat(const automat& firsAutomat, const automat& secondAutomat) override;
        automat baseKleene(const automat& firsAutomat) override;
        automat baseAlternate(const automat& firsAutomat, const automat& secondAutomat) override;
        explicit NFA(State* start = nullptr, State* end = nullptr): baseAutomat(start, end) {};
        [[nodiscard]] bool acceptString(const automat& Automat, const std::string& baseString) override;
        [[nodiscard]] std::set<State*> getEpsilonClojure(State* state) override;
    };

}




