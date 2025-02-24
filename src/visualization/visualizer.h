#pragma once
#include <fstream>
#include <functional>


#include "visualizer.h"
#include "../automat/base_automat/automat.h"

namespace automat
{
    class visualizer {
    public:
        static void exportToDot(const automat& Automat, const std::string& filename);
    };
}


