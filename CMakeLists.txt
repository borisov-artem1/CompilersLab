cmake_minimum_required(VERSION 3.30)
project(testProject)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(testProject
        src/cmd/main.cpp
        src/prep/preprocessing.cpp
        src/prep/preprocessing.h
        src/automat/NFA/NFA.cpp
        src/automat/NFA/NFA.h
        src/automat/DFA/DFA.cpp
        src/automat/DFA/DFA.h
        src/automat/base_automat/automat.cpp
        src/automat/base_automat/automat.h
        src/algorithms/algorithm.cpp
        src/algorithms/algorithm.h
        src/visualization/visualizer.cpp
        src/visualization/visualizer.h
        src/tests/NFA_tests.cpp
        src/automat/base_automat/syntaxTree.cpp
        src/automat/base_automat/syntaxTree.h
        src/visualization/tree_visualization.cpp
        src/visualization/tree_visualization.h)

target_link_libraries(testProject
        ${GTEST_LIBRARIES}
        pthread
)