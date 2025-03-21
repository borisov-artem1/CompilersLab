//
// Created by artemborisov on 3/14/25.
//

#include "syntaxTree.h"
#include "../../visualization/tree_visualization.h"


namespace automat
{
    syntaxTreeNode* TreeBuilder::buildSyntaxTree(std::string& regex, std::map<int, char>& positionToSymbol)
    {
        std::stack<syntaxTreeNode*> nodeStack;
        int positionCounter = 1;

        for (const char c : regex)
        {
            if (c == '*')
            {
                auto node = new syntaxTreeNode('*');
                node->left = nodeStack.top();
                nodeStack.pop();
                nodeStack.push(node);
            } else if (c == '.')
            {
                syntaxTreeNode* right = nodeStack.top();
                nodeStack.pop();
                syntaxTreeNode* left = nullptr;
                if (!nodeStack.empty())
                {
                    left = nodeStack.top();
                    nodeStack.pop();
                }
                auto node = new syntaxTreeNode('.');
                node->left = left;
                node->right = right;
                nodeStack.push(node);
            } else if (c == '|')
            {
                syntaxTreeNode* right = nodeStack.top();
                nodeStack.pop();
                syntaxTreeNode* left = nullptr;
                if (!nodeStack.empty())
                {
                    left = nodeStack.top();
                    nodeStack.pop();
                }
                auto node = new syntaxTreeNode('|');
                node->left = left;
                node->right = right;
                nodeStack.push(node);
            } else
            {
                auto node = new syntaxTreeNode(c);
                node->position = positionCounter;
                positionToSymbol[positionCounter] = c;
                positionCounter++;
                nodeStack.push(node);
            }
        }
        tree_visualization::exportTreeToDot(nodeStack.top());
        return nodeStack.top();
    }

    void TreeBuilder::computePositions(syntaxTreeNode* node, std::map<int, std::set<int>>& followPos)
    {
        if (!node) return;

        computePositions(node->left, followPos);
        computePositions(node->right, followPos);

        if (node->symbol == '*')
        {
            node->nullable = true;
            node->firstPos = node->left->firstPos;
            node->lastPos = node->left->lastPos;
            for (int pos : node->left->lastPos)
            {
                followPos[pos].insert(node->left->firstPos.begin(), node->left->firstPos.end());
            }
            node->isAccepted = !node->lastPos.empty();
        } else if (node->symbol == '.')
        {
            node->nullable = node->left->nullable && node->right->nullable;
            node->firstPos = node->left->firstPos;
            if (node->left->nullable)
            {
                node->firstPos.insert(node->right->firstPos.begin(), node->right->firstPos.end());
            }
            node->lastPos = node->right->lastPos;

            if (node->right->nullable)
            {
                node->lastPos.insert(node->left->lastPos.begin(), node->left->lastPos.end());
            }

            for (int pos : node->left->lastPos)
            {
                followPos[pos].insert(node->right->firstPos.begin(), node->right->firstPos.end());
            }
            node->isAccepted = node->right->isAccepted;
            if (node->right->nullable)
            {
                node->isAccepted |= node->left->isAccepted;
            }
        } else if (node->symbol == '|')
        {
            node->nullable = node->left->nullable || node->right->nullable;
            node->isAccepted = node->left->isAccepted || node->right->isAccepted;
            node->firstPos.insert(node->left->firstPos.begin(), node->left->firstPos.end());
            node->firstPos.insert(node->right->firstPos.begin(), node->right->firstPos.end());
            node->lastPos.insert(node->left->lastPos.begin(), node->left->lastPos.end());
            node->lastPos.insert(node->right->lastPos.begin(), node->right->lastPos.end());
        } else
        {
            node->nullable = false;
            node->firstPos.insert(node->position);
            node->lastPos.insert(node->position);
        }
    }


}