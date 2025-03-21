#include "DFA.h"

#include "../../algorithms/algorithm.h"
#include "../../prep/preprocessing.h"
#include "../../visualization/visualizer.h"
#include "../base_automat/syntaxTree.h"

namespace automat
{
    void DFABuilder::addState(State* s)
    {
        states.insert(s);
    }

    std::map<int, char> DFABuilder::alCounter(const std::string& regex)
    {
        std::map<int, char> counterMap;
        int counter = 1;
        for (const char p : regex)
        {
            if (std::isalnum(p))
            {
                counterMap[counter] = p;
                counter++;
            }
        }
        return counterMap;
    }

    std::set<int> DFABuilder::findEndingPositions(const std::string& postfix) {
        std::stack<std::set<int>> stack;  // Стек для анализа позиций
        int position = 1;  // Нумерация символов с 1

        for (char c : postfix) {
            if (std::isalpha(c)) {
                // Символы алфавита добавляем как {position}
                stack.push({position});
                position++;
            } else if (c == '.') {
                // Конкатенация: объединение множества правого операнда и левого (если nullable)
                std::set<int> right = stack.top(); stack.pop();
                std::set<int> left = stack.top(); stack.pop();
                if (!right.empty()) {
                    left.insert(right.begin(), right.end());
                }
                stack.push(left);
            } else if (c == '|') {
                // Объединение: просто объединяем два множества
                std::set<int> set1 = stack.top(); stack.pop();
                std::set<int> set2 = stack.top(); stack.pop();
                set1.insert(set2.begin(), set2.end());
                stack.push(set1);
            } else if (c == '*') {
                // Замыкание: добавляем само множество на стек, так как * повторяет символы
                std::set<int> topSet = stack.top();
                stack.push(topSet);
            }
        }

        // Множество на вершине стека - это множество возможных конечных позиций
        return stack.top();
    }



    DFA DFABuilder::buildMinimalDFA(std::string& regex)
    {
        // regex = (a|b)*abb
        // postfix = ab|*a.b.b - wrong
        prep::preprocessing::replacementPlus(regex);
        std::map<int, char> counterMap = alCounter(regex);
        auto p = prep::preprocessing(regex);
        std::string postfixString = p.normalizeString();
        std::map<int, char> positionToSymbol;
        std::map<int, std::set<int>> followPos;

        syntaxTreeNode* root = TreeBuilder::buildSyntaxTree(postfixString, positionToSymbol);

        TreeBuilder::computePositions(root, followPos);

        std::map<std::set<int>, State*> dfaStates;
        std::queue<std::set<int>> processingQueue;

        for (const auto& [pos, sym] : counterMap)
        {
            if (!followPos.contains(pos))
            {
                followPos[pos] = {};
            }
        }

        const std::set<int> startSet = root->firstPos;
        processingQueue.push(startSet);

        int stateId = 0;
        State* startState = new State{stateId++, {}, false};
        dfaStates[startSet] = startState;


        while (!processingQueue.empty())
        {
            std::set<int> currentSet = processingQueue.front();
            processingQueue.pop();
            State* currentState = dfaStates[currentSet];

            std::map<char, std::set<int>> moveTable;

            for (int pos: currentSet)
            {
                if (positionToSymbol.contains(pos))
                {
                    moveTable[positionToSymbol[pos]].insert(followPos[pos].begin(), followPos[pos].end());
                }
            }


            for (const auto& [symbol, nextSet] : moveTable)
            {
                if (!dfaStates.contains(nextSet))
                {
                    dfaStates[nextSet] = new State{stateId++, {}, false};
                    processingQueue.push(nextSet);
                }
                currentState->transitions.insert({symbol, dfaStates[nextSet]});
            }
        }

        DFA dfa;
        dfa.start = startState;
        int maxStateId = -2;
        for (const auto& [set, nextSet] : dfaStates)
        {
            for (auto pos : set)
            {
                if (pos > maxStateId)
                {
                    maxStateId = pos;
                }
            }
        }

        int position = 0;
        for (const auto& [pos, set] : followPos)
        {
            if (position < pos)
            {
                position = pos;
            }
        }


        for (const auto& [set, state] : dfaStates)
        {
            bool noTransitions = state->transitions.empty();
            bool selfLoopWhithTrans = false;
            if (state->transitions.size() == 2)
            {
                for (auto st : state->transitions)
                {
                    if (st.second == state && st.second != dfa.start)
                    {
                        selfLoopWhithTrans = true;
                        break;
                    }
                }
            }
            bool onlySelfLoop = (state->transitions.size() == 1 || state->transitions.size() == 2) && (state->transitions.begin()->second == state || selfLoopWhithTrans);
            if (set.empty() || onlySelfLoop || noTransitions) // set.empty() || set.contains(maxStateId)
            {
                state->isAccept = true;
            }

            dfa.states.push_back(state);
        }



        visualizer::exportToDot(dfa.start, nullptr, "DFA_from_rgx");
        return dfa;
    }

}
