#pragma once
#include <fstream>
#include <functional>


#include "visualizer.h"
#include "../automat/base_automat/automat.h"
#include "../automat/DFA/DFA.h"

namespace automat
{
    class visualizer {
    public:
        static void exportToDot(State* start, State* accept, const std::string& filename);
        static void exportDFAToDot(const DFA& dfa, const std::string& filename);
    };
}


