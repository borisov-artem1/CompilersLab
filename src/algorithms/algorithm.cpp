#include <stack>
#include "../automat/NFA/NFA.h"
#include "algorithm.h"

#include <queue>

#include "../automat/DFA/DFA.h"
#include "../prep/preprocessing.h"
#include "../visualization/visualizer.h"


namespace automat
{
    automat algForAuto::buildNFAfromPostfixString(std::string& baseString)
    {
        prep::preprocessing regSeq(baseString);
        std::string postfixString = regSeq.normalizeString();
        std::stack<automat> nfaStack;
        NFA nfa;
        for (const auto& postfix : postfixString)
        {
            if (std::isalnum(postfix))
            {
                nfaStack.push(nfa.createBaseAutomat(postfix));
            } else if (postfix == '.')
            {
                automat secondAutomat = nfaStack.top();
                nfaStack.pop();
                automat firstAutomat = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(nfa.baseConcat(firstAutomat, secondAutomat));
            } else if (postfix == '*')
            {
                automat Automat = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(nfa.baseKleene(Automat));
            } else if (postfix == '|')
            {
                automat secondAutomat = nfaStack.top();
                nfaStack.pop();
                automat firstAutomat = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(nfa.baseAlternate(firstAutomat, secondAutomat));
            }
        }
        visualizer::exportToDot(nfaStack.top().start, nfaStack.top().accept,"NFA");
        return nfaStack.top();
    }

    void algForAuto::printNFA(State* state, std::set<int>& visited) const
    {
        if (visited.contains(state->id)) { return; }
        visited.insert(state->id);

        for (const auto& [symbol, nextState] : state->transitions)
        {
            std::cout << "State " << state->id << " --(" << (symbol == '\0' ? "e" : std::string(1, symbol)) << ")--> State " << nextState->id << std::endl;
            printNFA(nextState, visited);
        }
    }

    DFA algForAuto::buildDFAfromNFA(automat& NFA)
    {
        DFA dfa;
        std::queue<std::set<State*>> dfaQueue;
        std::map<std::set<State*>, State*> dfaStates;
        int stateCount = 0;

        const std::set<State*> startClosure = epsilonClosure({NFA.start});
        auto startState = new State{stateCount++, {}, false};
        dfaStates[startClosure] = startState;
        dfa.start = startState;
        dfa.states.push_back(startState);
        dfaQueue.push(startClosure);

        while (!dfaQueue.empty())
        {
            std::set<State*> currentClosure = dfaQueue.front();
            dfaQueue.pop();
            State* dfaState = dfaStates[currentClosure];

            for (const auto state : currentClosure)
            {
                if (state == NFA.accept)
                {
                    dfaState->isAccept = true;
                    break;
                }
            }

            std::map<char, std::set<State*>> moveTable;
            for (const auto state : currentClosure)
            {
                for (const auto& [symbol, nextState] : state->transitions)
                {
                    if (symbol != '\0')
                    {
                        moveTable[symbol].insert(nextState);
                    }
                }
            }

            for (const auto& [symbol, nextState] : moveTable)
            {
                std::set<State*> curSetClos = epsilonClosure(nextState);
                if (!dfaStates.contains(curSetClos))
                {
                    State* newState = new State{stateCount++, {}, false};
                    dfaStates[curSetClos] = newState;
                    dfa.states.push_back(newState);
                    dfaQueue.push(curSetClos);
                }
                dfaState->transitions.insert({symbol, dfaStates[curSetClos]});
            }
        }

        visualizer::exportToDot(dfa.start, nullptr, "DFA");
        return dfa;

    }

    std::set<State*> algForAuto::epsilonClosure(std::set<State*> states)
    {
        std::set<State*> closure = states;
        std::queue<State*> visited;

        for (const auto& state : states)
        {
            visited.push(state);
        }

        while (!visited.empty())
        {
            State* currentState = visited.front();
            visited.pop();
            for (const auto& [symbol, nextState] : currentState->transitions)
            {
                if (symbol == '\0' && !closure.contains(nextState))
                {
                    closure.insert(nextState);
                    visited.push(nextState);
                }
            }
        }
        return closure;
    }

    bool algForAuto::acceptStringForDFA(State* state, const std::string& baseString)
    {
        State* currentState = state;
        for (const auto& c : baseString)
        {
            std::map<char, State*> moveTable;
            for (const auto& [symbol, nextState] : currentState->transitions)
            {
                moveTable[symbol] = nextState;
            }
            if (moveTable.contains(c))
            {
                currentState = moveTable[c];
            } else
            {
                return false;
            }
        }

        return currentState->isAccept;
    }


    std::string algForAuto::formingAlphabet(const std::string& baseString)
    {
        std::string alphabet;
        for (const char symbol : baseString)
        {
            if (alphabet.find(symbol) == std::string::npos && std::isalnum(symbol))
            {
                alphabet += symbol;
            }
        }
        return alphabet;
    }


    DFA algForAuto::minimizationDFA(const DFA& dfa, const std::string& baseString)
    {
        std::set<State*> finalStates, nonFinalStates;

        for (State* s: dfa.states)
        {
            if (s->isAccept)
            {
                finalStates.insert(s);
            } else
            {
                nonFinalStates.insert(s);
            }
        }

        std::set<std::set<State*>> P;
        if (nonFinalStates.empty())
        {
            P = {finalStates};
        } else
        {
            P = {finalStates, nonFinalStates};
        }
        std::queue<std::set<State*>> W;
        W.push(finalStates);


        std::string alphabet = formingAlphabet(baseString);

        while (!W.empty())
        {
            std::set<State*> classToSplit = W.front();
            W.pop();

            for (const char& symbol : alphabet)
            {
                std::set<State*> affectingStates;

                for (State* s : dfa.states)
                {
                    for (const auto [transitionSymbol, nextState] : s->transitions)
                    {
                        if (symbol == transitionSymbol && classToSplit.contains(nextState))
                        {
                            affectingStates.insert(s);
                        }
                    }
                }

                for (const auto& subset : P)
                {
                    std::set<State*> intersection, difference;

                    for (State* s : subset)
                    {
                        if (affectingStates.contains(s))
                        {
                            intersection.insert(s);
                        } else
                        {
                            difference.insert(s);
                        }
                    }

                    if (!intersection.empty() && !difference.empty())
                    {
                        P.erase(subset);
                        P.insert(intersection);
                        P.insert(difference);

                        std::queue<std::set<State*>> Q;
                        bool found = false;

                        while (!W.empty())
                        {
                            auto curr = W.front();
                            W.pop();
                            if (curr == subset)
                            {
                                found = true;
                            } else
                            {
                                Q.push(curr);
                            }
                        }

                        if (found)
                        {
                            Q.push(intersection);
                            Q.push(difference);
                        } else
                        {
                            Q.push(intersection.size() <= difference.size() ? difference : intersection);
                        }
                        W = std::move(Q);
                        break;
                    }
                }
            }
        }

        DFA minDFA;
        std::map<std::set<State*>, State*> newStates;
        int idCounter = 0;


        for (const auto& subset : P)
        {
            auto newState = new State{idCounter++, {}, false};
            newStates[subset] = newState;
            minDFA.states.push_back(newState);

            for (State* oldState : subset)
            {
                if (oldState->isAccept)
                {
                    newState->isAccept = true;
                    break;
                }
            }
        }

        for (const auto& [oldSet, newSet] : newStates)
        {
            for (State* repr = *oldSet.begin(); auto [symbol, targetState] : repr->transitions)
            {
                for (const auto& [subset, newTargetSet] : newStates)
                {
                    if (subset.contains(targetState))
                    {
                        newSet->transitions.insert({symbol, newTargetSet});
                        break;
                    }
                }
            }
        }


        for (const auto& [oldSet, newSet] : newStates)
        {
            for (State* s : oldSet)
            {
                if (s == dfa.start)
                {
                    minDFA.start = newStates[oldSet];
                }
            }
        }

        visualizer::exportToDot(minDFA.start, nullptr, "MinDFA");
        return minDFA;

    }




}
