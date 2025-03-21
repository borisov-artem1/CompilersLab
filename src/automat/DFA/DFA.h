#pragma once
#include "../base_automat/automat.h"
#include <set>
#include <map>
#include <queue>
#include <vector>

namespace automat {

    struct NodeInfo
    {
        bool nullable;
        std::set<int> firstPos, lastPos;
    };

    class DFABuilder {
    private:
        std::set<State*> states;
    public:
        void addState(State* s);
        [[nodiscard]] static DFA buildMinimalDFA(std::string& regex);
        [[nodiscard]] static std::map<int, char> alCounter(const std::string& regex);
        [[nodiscard]] static std::set<int> findEndingPositions(const std::string& postfix);
    };


}
