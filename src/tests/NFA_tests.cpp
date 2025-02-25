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
    EXPECT_FALSE(graph.acceptString(nfa, ""));
    EXPECT_TRUE(graph.acceptString(nfa, "a"));
    EXPECT_TRUE(graph.acceptString(nfa, "aa"));
    EXPECT_TRUE(graph.acceptString(nfa, "aaa"));
    EXPECT_FALSE(graph.acceptString(nfa, "b"));
    EXPECT_FALSE(graph.acceptString(nfa, "ba"));
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
}


TEST(NFABuildTest, ComplexNFA_1)
{
    std::string regex = "(a|b).c*";
    EXPECT_NO_THROW({
        const automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
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
}

TEST(NFABuildTest, EmptyString)
{
    std::string regex = "";
    EXPECT_THROW({
        const automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    }, std::runtime_error);
}

TEST(NFABuildTest, WrongRegex_1) {
    std::string regex = "a|.*";
    EXPECT_THROW({
        const automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    }, std::runtime_error);
}

TEST(NFABuildTest, WrongRegex_2) {
    std::string regex = "a.(+|c)*.+|d";
    EXPECT_THROW({
        const automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    }, std::runtime_error);
}

TEST(NFABuildTest, WrongRegex_3) {
    std::string regex = "+c+a|b|b+|.c.*.*";
    EXPECT_THROW({
        const automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);
    }, std::runtime_error);
}

TEST(NFAProcessingTest, AcceptValidStrings) {
    std::string regex = "a*";
    automat::NFA graph;
    const automat::automat nfa = automat::algForAuto::buildNFAfromPostfixString(regex);

}

TEST(NFABuildTest, BuildComplexRegex) {
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
}
