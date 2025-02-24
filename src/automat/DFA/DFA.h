#pragma once
#include "../base_automat/automat.h"
#include <set>
#include <map>

namespace automat {
    struct DFAState {
        std::set<State*> nfaStates;
        std::map<char, DFAState*> transitions;
        bool isAccept;
    };

    struct DFA {
        DFAState* start;
        std::set<DFAState*> states;
    };


}
