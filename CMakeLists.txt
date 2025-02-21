cmake_minimum_required(VERSION 3.30)
project(testProject)

set(CMAKE_CXX_STANDARD 20)

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
        src/visualization/visualizer.h)
