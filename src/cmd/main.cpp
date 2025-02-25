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
        // //std::cin >> Regex;
        // const automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(Regex);
        // const std::string filename = "graph.dot";
        // automat::visualizer::exportToDot(nfa, filename);
        // system("dot -Tpng graph.dot -o graph.png");
        // std::string inputString;
        // automat::NFA graph;

        //std::cin >> inputString;
        // std::cin.clear();
        // while (true)
        // {
        //     std::getline(std::cin, inputString);
        //     if (inputString == "exit") break;
        //     std::cout << (graph.acceptString(nfa, inputString) ? "Accepted\n" : "Rejected\n");
        // }



    } catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

}
