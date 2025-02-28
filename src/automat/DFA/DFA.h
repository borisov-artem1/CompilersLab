#pragma once
#include "../base_automat/automat.h"
#include <set>
#include <map>

namespace automat {
    struct DFAState: public State {
        //bool isAccept;
    };

    struct DFA {
        State* start;
        std::vector<State*> states;
    };


}
