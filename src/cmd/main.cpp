#include <iostream>
#include <utility>
#include <vector>
#include <set>

#include "../algorithms/algorithm.h"
#include "../prep/preprocessing.h"
#include "../automat/base_automat/automat.h"




struct NFA
{   //    Q           Sigma
    // 0 .. n - 1, 0 .. c - 1

    int start;
    std::vector<bool> t;
    std::vector<std::vector<std::set<int>>> transitionsFunc;

};

class ThompsonAlgorithm
{

};

int main() {

    using namespace prep;
    try
    {
        std::string Regex;
        std::cin >> Regex;
        preprocessing regString(Regex);
        const automat::algForAuto alg;
        auto [start, accept] = automat::algForAuto::buildNFAfromPostfixString(regString.normalizeString());
        std::set<int> visited;
        alg.printNFA(start, visited);

    } catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

}
