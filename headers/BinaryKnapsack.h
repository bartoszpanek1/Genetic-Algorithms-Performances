//
// This class contains declarations of all methods needed for solving a binary knapsack problem
//

#ifndef GENETIC_ALGORITHM_PERFORMANCES_BINARYKNAPSACK_H
#define GENETIC_ALGORITHM_PERFORMANCES_BINARYKNAPSACK_H

class BinaryKnapsack {
private:
    //variables
    int *values;
    int *weights;
    int capacity;
    int size;

    //methods
    int recursionHelper(int, int);

    int *fitness(int **population, int popSize);

    int **selection(int *fitness, int **population, int numOfParents, int sizeOfPop) const;

    int **crossover(int **parents, int numOfChildren, double crossoverRate, int numOfParents) const;

    void mutation(int **children, int numOfChildren, double mutationRate) const;

public:
    //constructor
    BinaryKnapsack(int *values, int *weights, int capacity, int size);

    //destructor
    ~BinaryKnapsack();

    //getters
    int *getValues();

    int *getWeights();

    //methods
    int solveRecursion(); // slowest method using Recursion O(2^n)
    int solveDP(); // method using dynamic programming
    int solveGenetic(int sizeOfPop, int numOfGenerations, double crossoverRate,
                     double mutationRate); // method using genetic algorithm
};

#endif //GENETIC_ALGORITHM_PERFORMANCES_BINARYKNAPSACK_H
