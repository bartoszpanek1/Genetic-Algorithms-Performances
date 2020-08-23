#include <iostream>
#include "headers/BinaryKnapsack.h"
#include <bitset>

int main() {
int* vals = new int[3]{100,60,120};
int* wts = new int[3]{20,10,30};
int capacity = 50;
int n = 3;
BinaryKnapsack knapsack(vals,wts,capacity,n);
std::cout<<knapsack.solveGenetic(3,50,0.8,0.2);

return 0;
}
