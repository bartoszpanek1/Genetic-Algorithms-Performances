//
// Created by bartosz on 19.08.2020.
//

#include <algorithm>
#include <iostream>
#include "../headers/BinaryKnapsack.h"


BinaryKnapsack::BinaryKnapsack(int *values, int *weights, int capacity, int size) {
    this->values=values;
    this->weights=weights;
    this->capacity=capacity;
    this->size=size;
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

int BinaryKnapsack::recursionHelper(int i,int c) {
    if(i==0 || c==0){
        return 0;
    }
    if(weights[i-1]>capacity){
        return recursionHelper(i-1,c);
    }
    else{
        return std::max(values[i-1]+recursionHelper(i-1,c-weights[i-1]),
                        recursionHelper(i-1,c));
    }


}

