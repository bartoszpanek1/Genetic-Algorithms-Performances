//
// Created by bartosz on 19.08.2020.
//

#ifndef GENETIC_ALGORITHM_PERFORMANCES_BINARYKNAPSACK_H
#define GENETIC_ALGORITHM_PERFORMANCES_BINARYKNAPSACK_H
class BinaryKnapsack{
private:
    //variables
    int* values;
    int* weights;
    int capacity;
    int size;

    //methods
    int recursionHelper(int,int);
public:
    //constructor
    BinaryKnapsack(int* values, int* weights, int capacity, int size);

    //destructor
    ~BinaryKnapsack();

    //getters
    int* getValues();
    int* getWeights();

    //methods
    int solveRecursion(); // slowest method using Recursion O(2^n)
    int solveDP(); // method using dynamic programming
    int solveGenetic(); // method using genetic algorithm
};
#endif //GENETIC_ALGORITHM_PERFORMANCES_BINARYKNAPSACK_H
