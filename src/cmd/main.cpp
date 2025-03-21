#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <gtest/gtest.h>

#include "../algorithms/algorithm.h"
#include "../prep/preprocessing.h"
#include "../automat/base_automat/automat.h"
#include "../automat/NFA/NFA.h"
#include "../visualization/visualizer.h"


int main(int argc, char **argv) {

    using namespace prep;
    try
    {

        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();

        // std::string Regex;
        // std::getline(std::cin, Regex);
        // automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(Regex);
        // automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
        // automat::DFA dfaMin = automat::algForAuto::minimizationDFA(dfa, Regex);
        // automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(Regex);
        // automat::NFA graph;
        //
        // std::string inputString;
        // std::cin.clear();
        //
        // while (true)
        // {
        //     std::getline(std::cin, inputString);
        //     if (inputString == "exit") break;
        //     std::cout << (graph.acceptString(nfa, inputString) ? "Accepted NFA\n" : "Rejected NFA\n");
        //     std::cout << (automat::algForAuto::acceptStringForDFA(dfa.start, inputString) ? "Accepted DFA\n" : "Rejected DFA\n");
        //     std::cout << (automat::algForAuto::acceptStringForDFA(dfaMin.start, inputString) ? "Accepted MinDFA\n" : "Rejected MinDFA\n");
        //     std::cout << (automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, inputString) ? "Accepted DFAfromRGX\n" : "Rejected DFAfromRGX\n");
        //
        // }

         // std::string Regex;
         // std::cin >> Regex;
         // automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(Regex);
         // automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
         // automat::DFA dfaMin = automat::algForAuto::minimizationDFA(dfa, Regex);


    } catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

}
