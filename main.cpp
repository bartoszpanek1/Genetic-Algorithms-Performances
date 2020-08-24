#include <iostream>
#include "headers/BinaryKnapsack.h"
#include "headers/Graph.h"
#include <bitset>
#include <chrono>

int main() {
    int *vals = new int[30]{100, 60, 120, 50, 80, 30, 20, 40, 50, 10, 20, 40, 30, 40, 70, 120, 50, 20, 40, 40, 100, 60,
                            120, 50, 80, 30, 20, 40, 50, 10};
    int *wts = new int[30]{20, 10, 30, 40, 10, 60, 20, 10, 50, 70, 10, 30, 40, 20, 10, 20, 10, 30, 20, 30, 20, 10, 30,
                           40, 10, 60, 20, 10, 50, 70};
    int capacity = 300;
    int n = 30;
    int sizeOfPop = 100;
    int numOfGenerations = 100;
    double crossoverRate = 0.8;
    double mutationRate = 0.2;
    BinaryKnapsack knapsack(vals, wts, capacity, n);
    std::chrono::steady_clock::time_point beginRecursion = std::chrono::steady_clock::now();
    int resultRecursion = knapsack.solveRecursion();
    std::chrono::steady_clock::time_point endRecursion = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point beginDP = std::chrono::steady_clock::now();
    int resultDP = knapsack.solveDP();
    std::chrono::steady_clock::time_point endDP = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point beginGenetic = std::chrono::steady_clock::now();
    int resultGenetic = knapsack.solveGenetic(sizeOfPop, numOfGenerations, crossoverRate, mutationRate);
    std::chrono::steady_clock::time_point endGenetic = std::chrono::steady_clock::now();

    std::cout << "-----------------BINARY KNAPSACK PROBLEM-----------------" << std::endl;
    std::cout << "capacity: " << capacity << std::endl;
    std::cout << "number of items: " << n << std::endl;
    std::cout << "values: ";
    for (int i = 0; i < n; i++) {
        std::cout << vals[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "weights: ";
    for (int i = 0; i < n; i++) {
        std::cout << wts[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "----KNAPSACK RECURSION----" << std::endl;
    std::cout << "RESULT: " << resultRecursion << std::endl;
    std::cout << "TIME ELAPSED: "
              << std::chrono::duration_cast<std::chrono::microseconds>(endRecursion - beginRecursion).count() << "[μs]"
              << std::endl;

    std::cout << "----KNAPSACK DYNAMIC PROGRAMMING----" << std::endl;
    std::cout << "RESULT: " << resultDP << std::endl;
    std::cout << "TIME ELAPSED: " << std::chrono::duration_cast<std::chrono::microseconds>(endDP - beginDP).count()
              << "[μs]" << std::endl;

    std::cout << "----KNAPSACK GENETIC ALGORITHM----" << std::endl;
    std::cout << "Size of population: " << sizeOfPop << std::endl;;
    std::cout << "Number of generations: " << numOfGenerations << std::endl;;
    std::cout << "Crossover rate: " << crossoverRate << std::endl;;
    std::cout << "Mutation rate: " << mutationRate << std::endl;;
    std::cout << "RESULT: " << resultGenetic << std::endl;
    std::cout << "TIME ELAPSED: "
              << std::chrono::duration_cast<std::chrono::microseconds>(endGenetic - beginGenetic).count() << "[μs]"
              << std::endl;
//    Graph<std::string> graph;
//    graph.addNode("A");
//    graph.addNode("B");
//    graph.addNode("C");
//    graph.addNode("D");
//    graph.addEdge("A","B",20);
//    graph.addEdge("B","D",30);
//    graph.addEdge("D","C",35);
//    graph.addEdge("C","A",10);
//    graph.addEdge("A","D",15);
//    graph.addEdge("B","C",25);
//    int result = graph.solveNaive("A");
//    std::cout<<result<<std::endl;
    return 0;
}
