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
         // std::cin >> Regex;
         // automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(Regex);
         // automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
         // automat::DFA dfaMin = automat::algForAuto::minimizationDFA(dfa, Regex);


    } catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

}
