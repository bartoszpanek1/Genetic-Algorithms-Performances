cmake_minimum_required(VERSION 3.17)
project(Genetic_Algorithm_Performances)

set(CMAKE_CXX_STANDARD 20)

add_executable(Genetic_Algorithm_Performances main.cpp sources/Graph.cpp sources/Node.cpp headers/Graph.h headers/Node.h headers/BinaryKnapsack.h sources/BinaryKnapsack.cpp utils.cpp)