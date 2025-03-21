#pragma once
#include "visualizer.h"
#include "../automat/base_automat/syntaxTree.h"

namespace automat
{
    class tree_visualization {
    public:
        static void exportTreeToDot(const syntaxTreeNode* node);
    };
}

