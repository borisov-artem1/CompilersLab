#pragma once
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <stack>

#include "automat.h"
#include "../DFA/DFA.h"

namespace automat
{
    struct syntaxTreeNode
    {
        char symbol;
        int position;
        bool nullable;
        bool isAccepted = false;
        std::set<int> firstPos, lastPos;
        syntaxTreeNode* left;
        syntaxTreeNode* right;

        explicit syntaxTreeNode(const char symbol) : symbol(symbol), position(-1), nullable(false), left(nullptr), right(nullptr) {}
    };

    class TreeBuilder
    {
    public:
        [[nodiscard]] static syntaxTreeNode* buildSyntaxTree(std::string& regex, std::map<int, char>& positionToSymbol);
        static void computePositions(syntaxTreeNode* node, std::map<int, std::set<int>>& followPos);
    };
}


