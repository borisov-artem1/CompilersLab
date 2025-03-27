#include <gtest/gtest.h>
#include "../automat/NFA/NFA.h"
#include "../algorithms/algorithm.h"
#include "../prep/preprocessing.h"
#include "../visualization/visualizer.h"


TEST(NFABuildTest, BuildPlusRegex) {
    std::string regex = "a+";
    automat::NFA graph;
    automat::automat nfa;
    EXPECT_NO_THROW({
        nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    });
    automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
    automat::DFA minDfa = automat::algForAuto::minimizationDFA(dfa, regex);
    automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(regex);
    automat::visualizer::exportToDot(nfa.start, nfa.accept,"NFA");
    automat::visualizer::exportToDot(dfa.start, nullptr, "DFA");
    automat::visualizer::exportToDot(minDfa.start, nullptr, "MinDFA");
    EXPECT_FALSE(graph.acceptString(nfa, ""));
    EXPECT_TRUE(graph.acceptString(nfa, "a"));
    EXPECT_TRUE(graph.acceptString(nfa, "aa"));
    EXPECT_TRUE(graph.acceptString(nfa, "aaa"));
    EXPECT_FALSE(graph.acceptString(nfa, "b"));
    EXPECT_FALSE(graph.acceptString(nfa, "ba"));

    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, ""));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "a"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aa"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aaa"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ba"));

    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, ""));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "a"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "aa"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "aaa"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "ba"));

    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, ""));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA( dfaFromRGX.start, "a"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA( dfaFromRGX.start, "aa"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA( dfaFromRGX.start, "aaa"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "ba"));
    nfa.clearAuto();
}

TEST(NFABuildTest, BuildKleeneRegex)
{
    std::string regex = "a*";
    automat::NFA graph;
    automat::automat nfa;
    EXPECT_NO_THROW({
        nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    });

    EXPECT_TRUE(graph.acceptString(nfa, ""));
    EXPECT_TRUE(graph.acceptString(nfa, "a"));
    EXPECT_TRUE(graph.acceptString(nfa, "aa"));
    EXPECT_TRUE(graph.acceptString(nfa, "aaa"));
    EXPECT_FALSE(graph.acceptString(nfa, "b"));
    EXPECT_FALSE(graph.acceptString(nfa, "bb"));
    EXPECT_FALSE(graph.acceptString(nfa, "cc"));

    automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
    automat::DFA minDfa = automat::algForAuto::minimizationDFA(dfa, regex);
    automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(regex);
    automat::visualizer::exportToDot(nfa.start, nfa.accept,"NFA");
    automat::visualizer::exportToDot(dfa.start, nullptr, "DFA");
    automat::visualizer::exportToDot(minDfa.start, nullptr, "MinDFA");
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "a"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aa"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aaa"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, ""));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ba"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "cc"));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "a"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "aa"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "aaa"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, ""));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "ba"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "cc"));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "a"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "aa"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "aaa"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, ""));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "ba"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "cc"));
    nfa.clearAuto();
}

TEST(NFABuildTest, BuildConcatRegex)
{
    std::string regex = "a.b";
    automat::NFA graph;
    automat::automat nfa;
    EXPECT_NO_THROW({
        nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    });
    EXPECT_TRUE(graph.acceptString(nfa, "ab"));
    EXPECT_FALSE(graph.acceptString(nfa, "b"));
    EXPECT_FALSE(graph.acceptString(nfa, "bb"));
    EXPECT_FALSE(graph.acceptString(nfa, "cc"));
    EXPECT_FALSE(graph.acceptString(nfa, "a"));

    automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
    automat::DFA minDfa = automat::algForAuto::minimizationDFA(dfa, regex);
    automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(regex);
    automat::visualizer::exportToDot(nfa.start, nfa.accept,"NFA");
    automat::visualizer::exportToDot(dfa.start, nullptr, "DFA");
    automat::visualizer::exportToDot(minDfa.start, nullptr, "MinDFA");
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "ab"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ba"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "cc"));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "ab"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "ba"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "cc"));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "ab"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "ba"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "cc"));

    nfa.clearAuto();
}

TEST(NFABuildTest, BuildAlternateRegex) {
    std::string regex = "a|b";
    automat::NFA graph;
    automat::automat nfa;
    EXPECT_NO_THROW({
        nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    });
    EXPECT_TRUE(graph.acceptString(nfa, "a"));
    EXPECT_TRUE(graph.acceptString(nfa, "b"));
    EXPECT_FALSE(graph.acceptString(nfa, "ab"));
    EXPECT_FALSE(graph.acceptString(nfa, "ba"));
    EXPECT_FALSE(graph.acceptString(nfa, ""));

    automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
    automat::DFA minDfa = automat::algForAuto::minimizationDFA(dfa, regex);
    automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(regex);
    automat::visualizer::exportToDot(nfa.start, nfa.accept,"NFA");
    automat::visualizer::exportToDot(dfa.start, nullptr, "DFA");
    automat::visualizer::exportToDot(minDfa.start, nullptr, "MinDFA");
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "a"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ab"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ba"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "cc"));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "a"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "ab"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "ba"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "cc"));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA( dfaFromRGX.start, "a"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA( dfaFromRGX.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "ab"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "ba"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "cc"));

    nfa.clearAuto();
}


TEST(NFABuildTest, ComplexNFA_1)
{
    std::string regex = "(a|b).c*";
    EXPECT_NO_THROW({
        automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
        automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
        automat::DFA minDfa = automat::algForAuto::minimizationDFA(dfa, regex);
        automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(regex);
        automat::visualizer::exportToDot(nfa.start, nfa.accept,"NFA");
        automat::visualizer::exportToDot(dfa.start, nullptr, "DFA");
        automat::visualizer::exportToDot(minDfa.start, nullptr, "MinDFA");
        nfa.clearAuto();
        });
}

TEST(NFABuildTest, BuildComplexKleeneRegex) {
    std::string regex = "(a|b|c).d+.v*";
    automat::NFA graph;
    automat::automat nfa;
    EXPECT_NO_THROW({
        nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    });
    EXPECT_TRUE(graph.acceptString(nfa, "ad"));
    EXPECT_TRUE(graph.acceptString(nfa, "bd"));
    EXPECT_TRUE(graph.acceptString(nfa, "cd"));
    EXPECT_TRUE(graph.acceptString(nfa, "adv"));
    EXPECT_TRUE(graph.acceptString(nfa, "advvvv"));
    EXPECT_FALSE(graph.acceptString(nfa, "a"));
    EXPECT_FALSE(graph.acceptString(nfa, "b"));
    EXPECT_FALSE(graph.acceptString(nfa, ""));
    EXPECT_FALSE(graph.acceptString(nfa, "dd"));

    automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
    automat::DFA minDfa = automat::algForAuto::minimizationDFA(dfa, regex);
    automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(regex);
    automat::visualizer::exportToDot(nfa.start, nfa.accept,"NFA");
    automat::visualizer::exportToDot(dfa.start, nullptr, "DFA");
    automat::visualizer::exportToDot(minDfa.start, nullptr, "MinDFA");
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "ad"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "bd"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "cd"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "adv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "advvvv"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "a"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "b"));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "ad"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "bd"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "cd"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "adv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "advvvv"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "a"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "b"));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "ad"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "bd"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "cd"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "adv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "advvvv"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "a"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "b"));

    nfa.clearAuto();
}


TEST(NFABuildTest, EmptyString)
{
    std::string regex = "";
    EXPECT_THROW({
        automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
        automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
        automat::DFA minDfa = automat::algForAuto::minimizationDFA(dfa, regex);
        automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(regex);
        nfa.clearAuto();
    }, std::runtime_error);
}

TEST(NFABuildTest, WrongRegex_1) {
    std::string regex = "a|.*";
    EXPECT_THROW({
        automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
        automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
        automat::DFA minDfa = automat::algForAuto::minimizationDFA(dfa, regex);
        automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(regex);
        nfa.clearAuto();
    }, std::runtime_error);
}

TEST(NFABuildTest, WrongRegex_2) {
    std::string regex = "a.(+|c)*.+|d";
    EXPECT_THROW({
        automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
        automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
        automat::DFA minDfa = automat::algForAuto::minimizationDFA(dfa, regex);
        automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(regex);
        nfa.clearAuto();
    }, std::runtime_error);
}

TEST(NFABuildTest, WrongRegex_3) {
    std::string regex = "+c+a|b|b+|.c.*.*";
    EXPECT_THROW({
        automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
        automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
        automat::DFA minDfa = automat::algForAuto::minimizationDFA(dfa, regex);
        automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(regex);
        nfa.clearAuto();
    }, std::runtime_error);
}

TEST(NFABuildTest, BuildComplexRegex_1) {
    std::string regex = "b*.abb";
    automat::NFA graph;
    automat::automat nfa;
    EXPECT_NO_THROW({
        nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    });
    EXPECT_TRUE(graph.acceptString(nfa, "babb"));
    EXPECT_TRUE(graph.acceptString(nfa, "bbbabb"));
    EXPECT_TRUE(graph.acceptString(nfa, "abb"));
    EXPECT_FALSE(graph.acceptString(nfa, "a"));
    EXPECT_FALSE(graph.acceptString(nfa, "b"));
    EXPECT_FALSE(graph.acceptString(nfa, "ba"));
    EXPECT_FALSE(graph.acceptString(nfa, ""));

    automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
    automat::DFA minDfa = automat::algForAuto::minimizationDFA(dfa, regex);
    automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(regex);
    automat::visualizer::exportToDot(nfa.start, nfa.accept,"NFA");
    automat::visualizer::exportToDot(dfa.start, nullptr, "DFA");
    automat::visualizer::exportToDot(minDfa.start, nullptr, "MinDFA");
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "babb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "bbbabb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "abb"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "a"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ba"));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "babb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "bbbabb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "abb"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "a"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "ba"));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "babb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "bbbabb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "abb"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "a"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "b"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "ba"));

    nfa.clearAuto();
}

TEST(NFABuildTest, BuildComplexRegex_2) {
    std::string regex = "(aa|bb|cc)*vv+";
    automat::NFA graph;
    automat::automat nfa;
    EXPECT_NO_THROW({
        nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    });
    EXPECT_TRUE(graph.acceptString(nfa, "vv"));
    EXPECT_TRUE(graph.acceptString(nfa, "vvvv"));
    EXPECT_TRUE(graph.acceptString(nfa, "aavv"));
    EXPECT_TRUE(graph.acceptString(nfa, "bbbbvv"));
    EXPECT_TRUE(graph.acceptString(nfa, "vvv"));
    EXPECT_TRUE(graph.acceptString(nfa, "ccvvv"));
    EXPECT_FALSE(graph.acceptString(nfa, "ba"));
    EXPECT_FALSE(graph.acceptString(nfa, ""));
    EXPECT_FALSE(graph.acceptString(nfa, "vb"));

    automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
    automat::DFA minDfa = automat::algForAuto::minimizationDFA(dfa, regex);
    automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(regex);
    automat::visualizer::exportToDot(nfa.start, nfa.accept,"NFA");
    automat::visualizer::exportToDot(dfa.start, nullptr, "DFA");
    automat::visualizer::exportToDot(minDfa.start, nullptr, "MinDFA");
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "vv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "vvvv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aavv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "bbbbvv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "vvv"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ba"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, ""));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "vv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "vvvv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "aavv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "bbbbvv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "vvv"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "ba"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, ""));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "vv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "vvvv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "aavv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "bbbbvv"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "vvv"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "ba"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, ""));

    nfa.clearAuto();
}

TEST(NFABuildTest, ComplexNFA_3)
{
    std::string regex = "(a|b)*abb";
    automat::NFA graph;
    automat::automat nfa;
    EXPECT_NO_THROW({
        nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
        });
    EXPECT_TRUE(graph.acceptString(nfa, "aabb"));
    EXPECT_FALSE(graph.acceptString(nfa, "bb"));
    EXPECT_FALSE(graph.acceptString(nfa, ""));
    EXPECT_TRUE(graph.acceptString(nfa, "abb"));
    EXPECT_TRUE(graph.acceptString(nfa, "aabbabb"));
    EXPECT_TRUE(graph.acceptString(nfa, "ababb"));
    EXPECT_TRUE(graph.acceptString(nfa, "bbbbbabb"));
    EXPECT_TRUE(graph.acceptString(nfa, "babb"));


    automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
    automat::DFA minDfa = automat::algForAuto::minimizationDFA(dfa, regex);
    automat::DFA dfaFromRGX = automat::DFABuilder::buildMinimalDFA(regex);
    automat::visualizer::exportToDot(nfa.start, nfa.accept,"NFA");
    automat::visualizer::exportToDot(dfa.start, nullptr, "DFA");
    automat::visualizer::exportToDot(minDfa.start, nullptr, "MinDFA");
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aabb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "abb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aabbabb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "ababb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "bbbbbabb"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "bb"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, ""));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "aabb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "abb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "aabbabb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "ababb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(minDfa.start, "bbbbbabb"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, "bb"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(minDfa.start, ""));

    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "aabb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "abb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "aabbabb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "ababb"));
    EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "bbbbbabb"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, "bb"));
    EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfaFromRGX.start, ""));

    nfa.clearAuto();
}
