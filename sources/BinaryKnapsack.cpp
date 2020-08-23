//
// Created by bartosz on 19.08.2020.
//

#include <algorithm>
#include <iostream>
#include "../headers/BinaryKnapsack.h"
#include <random>
#include <bits/stdc++.h>

BinaryKnapsack::BinaryKnapsack(int *values, int *weights, int capacity, int size) {
    this->values = values;
    this->weights = weights;
    this->capacity = capacity;
    this->size = size;
}

BinaryKnapsack::~BinaryKnapsack() {
    delete[] values;
    delete[] weights;
}

int *BinaryKnapsack::getValues() {
    return values;
}

int *BinaryKnapsack::getWeights() {
    return weights;
}

int BinaryKnapsack::solveRecursion() {
    return recursionHelper(size, capacity);
}

int BinaryKnapsack::recursionHelper(int i, int c) {
    if (i == 0 || c == 0) {
        return 0;
    }
    if (weights[i - 1] > c) {
        return recursionHelper(i - 1, c);
    } else {
        return std::max(values[i - 1] + recursionHelper(i - 1, c - weights[i - 1]),
                        recursionHelper(i - 1, c));
    }


}

int BinaryKnapsack::solveDP() {
    //dynamic programming memoization table
    int **dp = new int *[size + 1];
    for (int i = 0; i < size + 1; i++) {
        dp[i] = new int[capacity + 1];
    }
    for (int i = 0; i < size + 1; i++) {
        for (int j = 0; j < capacity + 1; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (weights[i - 1] <= j) {
                dp[i][j] = std::max(values[i - 1] + dp[i - 1][j - weights[i - 1]],
                                    dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    int answer = dp[size][capacity];
    //deletion of the dynamic table
    for (int i = 0; i < size + 1; i++) {
        delete[] dp[i];
    }
    delete[] dp;

    return answer;
}

int BinaryKnapsack::solveGenetic(int sizeOfPop, int numOfGenerations, double crossoverRate, double mutationRate) {
    // initialize random starting population
    int **population = new int *[sizeOfPop];
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 1);
    for (int i = 0; i < sizeOfPop; i++) {
        population[i] = new int[size];
        for (int j = 0; j < size; j++) {
            population[i][j] = dist(mt);
        }
    }

    std::vector<int> fitnessHistory;
    int numOfParents = sizeOfPop / 2;
    int numOfChildren = sizeOfPop - numOfParents;
    for (int i = 0; i < numOfGenerations; i++) {
        std::cout<<"POPULATION "<<i<<std::endl;
        for(int k=0;k<sizeOfPop;k++){
            for(int s=0;s<size;s++){
                std::cout<<population[k][s]<<" ";
            }
            std::cout<<std::endl;
        }
        int *fitness = this->fitness(population, sizeOfPop);
        int max = 0;
        for (int j = 0; j < sizeOfPop; j++) {
            max = fitness[j] > max ? fitness[j] : max;
        }
        fitnessHistory.push_back(max);
        int **parents = selection(fitness, population, numOfParents,sizeOfPop);
        int **children = crossover(parents, numOfChildren, crossoverRate,numOfParents);
        mutation(children,numOfChildren,mutationRate);

        int idx=0;
        for(int j=0;j<numOfParents;j++,idx++){
            for(int k=0;k<size;k++){
                population[idx][k]=parents[j][k];
            }
        }
        for(int j=0;j<numOfChildren;j++,idx++){
            for(int k=0;k<size;k++){
                population[idx][k]=children[j][k];
            }
        }
        delete[] fitness;
        for (int j = 0; j < numOfParents; j++) {
            delete[] parents[j];
        }
        delete[] parents;
        for (int j = 0; j < numOfChildren; j++) {
            delete[] children[j];
        }
        delete[] children;

    }
    int* fitnessLastGen = fitness(population,sizeOfPop);
    int maxFitness = 0;
    for (int j = 0; j < sizeOfPop; j++) {
        maxFitness = fitnessLastGen[j] > maxFitness ? fitnessLastGen[j] : maxFitness;
    }
    delete[] fitnessLastGen;
    for(int i=0;i<sizeOfPop;i++){
        delete[] population[i];
    }
    delete[] population;

    return maxFitness;
}

// if sum(gene*weight)<=capacity: fitness=sum(gene*weight), else: fitness=0
int *BinaryKnapsack::fitness(int **population, int popSize) {
    int *fitness = new int[popSize];
    for (int i = 0; i < popSize; i++) {
        int totalVal = 0;
        int totalWeight = 0;
        for (int j = 0; j < size; j++) {
            totalVal += population[i][j] * values[j];
            totalWeight += population[i][j] * weights[j];
        }
        if (totalWeight <= capacity) {
            fitness[i] = totalVal;
        } else {
            fitness[i] = 0;
        }

    }
    return fitness;
}

int **BinaryKnapsack::selection(int *fitness, int **population, int numOfParents,int sizeOfPop) const {
    int **parents = new int *[numOfParents];
    for (int i = 0; i < numOfParents; i++) {
        parents[i] = new int[size];
    }
    for (int i = 0; i < numOfParents; i++) {
        int maxFitnessIdx = 0;
        int maxFitness = 0;
        for (int j = 0; j < sizeOfPop; j++) {
            if (fitness[j] > maxFitness) {
                maxFitnessIdx = j;
                maxFitness = fitness[j];
            }
        }
        for (int j = 0; j < size; j++) {
            parents[i][j] = population[maxFitnessIdx][j];
        }
        fitness[maxFitnessIdx] = INT_MIN;
    }
    return parents;
}

int **BinaryKnapsack::crossover(int **parents, int numOfChildren, double crossoverRate, int numOfParents) const {
    int **children = new int *[numOfChildren];
    for (int i = 0; i < numOfChildren; i++) {
        children[i] = new int[size];
    }
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 1);
    int crossoverPoint = size / 2;
    int i = 0;
    while (i < numOfChildren) {
        double randomVal = dist(mt);
        if (randomVal <= crossoverRate) {
            int parent1Index = i % numOfParents;
            int parent2Index = (i + 1) % numOfParents;
            for (int j = 0; j < size; j++) {
                if(j<crossoverPoint){
                    children[i][j]=parents[parent1Index][j];
                }
                else{
                    children[i][j]=parents[parent2Index][j];
                }
            }
            i++;
        }
    }
    return children;
}

void BinaryKnapsack::mutation(int **children, int numOfChildren, double mutationRate) const {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distDouble(0, 1);
    std::uniform_int_distribution<int> distInt(0, size - 1);
    for (int i = 0; i < numOfChildren; i++) {
        int randomVal = distDouble(mt);
        if (randomVal <= mutationRate) {
            int randIndex = distInt(mt);
            children[i][randIndex] = !children[i][randIndex]; //mutate (change) random chromosome to 1 or 0
        }
    }
}
