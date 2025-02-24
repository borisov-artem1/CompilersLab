#include <iostream>
#include <utility>
#include <vector>
#include <set>

#include "../algorithms/algorithm.h"
#include "../prep/preprocessing.h"
#include "../automat/base_automat/automat.h"
#include "../visualization/visualizer.h"


int main() {

    using namespace prep;
    try
    {
        std::string Regex;
        std::cin >> Regex;
        preprocessing regString(Regex);
        //const automat::algForAuto alg;
        const automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regString.normalizeString());
        const std::string filename = "graph.dot";
        automat::visualizer::exportToDot(nfa, filename);
        system("dot -Tpng graph.dot -o graph.png");

    } catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

}
