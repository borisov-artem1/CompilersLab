#include <gtest/gtest.h>
#include "../automat/NFA/NFA.h"
#include "../algorithms/algorithm.h"
#include "../prep/preprocessing.h"


TEST(NFABuildTest, BuildPlusRegex) {
    std::string regex = "a+";
    automat::NFA graph;
    automat::automat nfa;
    EXPECT_NO_THROW({
        nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    });
    automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
    EXPECT_FALSE(graph.acceptString(nfa, ""));
    EXPECT_TRUE(graph.acceptString(nfa, "a"));
    EXPECT_TRUE(graph.acceptString(nfa, "aa"));
    EXPECT_TRUE(graph.acceptString(nfa, "aaa"));
    EXPECT_FALSE(graph.acceptString(nfa, "b"));
    EXPECT_FALSE(graph.acceptString(nfa, "ba"));

    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, ""));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "a"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aa"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aaa"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "b"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ba"));
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
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "a"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aa"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aaa"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, ""));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "b"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ba"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "cc"));
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
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "ab"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "b"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ba"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "cc"));

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
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "a"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "b"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ab"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ba"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "cc"));

    nfa.clearAuto();
}


TEST(NFABuildTest, ComplexNFA_1)
{
    std::string regex = "(a|b).c*";
    EXPECT_NO_THROW({
        automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
        automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
        nfa.clearAuto();
        });
}

TEST(NFABuildTest, BuildComplexKleeneRegex) {
    std::string regex = "(a|b|c).(d|f)+.v*";
    automat::NFA graph;
    automat::automat nfa;
    EXPECT_NO_THROW({
        nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    });
    EXPECT_TRUE(graph.acceptString(nfa, "ad"));
    EXPECT_TRUE(graph.acceptString(nfa, "bf"));
    EXPECT_TRUE(graph.acceptString(nfa, "cd"));
    EXPECT_TRUE(graph.acceptString(nfa, "af"));
    EXPECT_TRUE(graph.acceptString(nfa, "advvvv"));
    EXPECT_FALSE(graph.acceptString(nfa, "a"));
    EXPECT_FALSE(graph.acceptString(nfa, "b"));
    EXPECT_FALSE(graph.acceptString(nfa, ""));
    EXPECT_FALSE(graph.acceptString(nfa, "dd"));

    automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "ad"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "bf"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "cd"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "af"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "advvvv"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "a"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "b"));

    nfa.clearAuto();
}

TEST(NFABuildTest, ComplexNFA_3)
{
    std::string regex = "a+.(w+.g+.f*|b+.(c*.(h|l+)|d+))";
    automat::NFA graph;
    automat::automat nfa;
    EXPECT_NO_THROW({
        nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
        });
    EXPECT_TRUE(graph.acceptString(nfa, "aaabh"));
    EXPECT_FALSE(graph.acceptString(nfa, "babah"));
    EXPECT_FALSE(graph.acceptString(nfa, "cabah"));
    EXPECT_FALSE(graph.acceptString(nfa, "awwf"));
    EXPECT_FALSE(graph.acceptString(nfa, "abbc"));
    EXPECT_TRUE(graph.acceptString(nfa, "awg"));
    EXPECT_TRUE(graph.acceptString(nfa, "aawwgg"));
    EXPECT_TRUE(graph.acceptString(nfa, "awggf"));
    EXPECT_TRUE(graph.acceptString(nfa, "aawwggffff"));
    EXPECT_TRUE(graph.acceptString(nfa, "abbbh"));
    EXPECT_TRUE(graph.acceptString(nfa, "abbcch"));
    EXPECT_TRUE(graph.acceptString(nfa, "abbccl"));
    EXPECT_TRUE(graph.acceptString(nfa, "abbll"));
    EXPECT_TRUE(graph.acceptString(nfa, "abbcccch"));
    EXPECT_TRUE(graph.acceptString(nfa, "abbddd"));

    automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
   //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "awg"));
   //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aawwgg"));
   //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "awggf"));
   //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "abbbh"));
   //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "abbccl"));
   //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "abbddd"));
   //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "cc"));

    nfa.clearAuto();
}

TEST(NFABuildTest, EmptyString)
{
    std::string regex = "";
    EXPECT_THROW({
        automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
        automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
        nfa.clearAuto();
    }, std::runtime_error);
}

TEST(NFABuildTest, WrongRegex_1) {
    std::string regex = "a|.*";
    EXPECT_THROW({
        automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
        automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
        nfa.clearAuto();
    }, std::runtime_error);
}

TEST(NFABuildTest, WrongRegex_2) {
    std::string regex = "a.(+|c)*.+|d";
    EXPECT_THROW({
        automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
        automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
        nfa.clearAuto();
    }, std::runtime_error);
}

TEST(NFABuildTest, WrongRegex_3) {
    std::string regex = "+c+a|b|b+|.c.*.*";
    EXPECT_THROW({
        automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
        automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
        nfa.clearAuto();
    }, std::runtime_error);
}

TEST(NFABuildTest, BuildComplexRegex_1) {
    std::string regex = "(a|b)*abb";
    automat::NFA graph;
    automat::automat nfa;
    EXPECT_NO_THROW({
        nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    });
    EXPECT_TRUE(graph.acceptString(nfa, "abb"));
    EXPECT_TRUE(graph.acceptString(nfa, "aabb"));
    EXPECT_TRUE(graph.acceptString(nfa, "babb"));
    EXPECT_TRUE(graph.acceptString(nfa, "bbbabb"));
    EXPECT_FALSE(graph.acceptString(nfa, "a"));
    EXPECT_FALSE(graph.acceptString(nfa, "b"));
    EXPECT_FALSE(graph.acceptString(nfa, "ba"));
    EXPECT_FALSE(graph.acceptString(nfa, ""));

    automat::DFA dfa = automat::algForAuto::buildDFAfromNFA(nfa);
   //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "abb"));
   //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aabb"));
   //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "babb"));
   //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "bbbabb"));
   //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "a"));
   //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "b"));
   //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ba"));

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
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "vv"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "vvvv"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "aavv"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "bbbbvv"));
    //EXPECT_TRUE(automat::algForAuto::acceptStringForDFA(dfa.start, "vvv"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, "ba"));
    //EXPECT_FALSE(automat::algForAuto::acceptStringForDFA(dfa.start, ""));

    nfa.clearAuto();
}