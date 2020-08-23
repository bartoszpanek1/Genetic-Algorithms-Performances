#include <iostream>
#include "headers/Graph.h"
#include "headers/BinaryKnapsack.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>
#include <math.h>
#include <bitset>
#include <random>

std::vector<std::string> splitByDelimiter(const std::string& toSplit,char delimiter){
    std::vector<std::string> retVec;
    std::string word;
    for(auto c : toSplit){
        if(c==delimiter){
            retVec.push_back(word);
            word="";
        }
        else{
            word+=c;
        }
    }
    retVec.push_back(word);
    return retVec;
}

Graph<std::string> graphFromFile(const std::string& fileName){
    Graph<std::string> g;
    std::ifstream inFile;
    inFile.open("data");
    if (inFile.is_open()) {
        std::string line;
        while(std::getline(inFile,line)){
            if(line=="directed"){
                std::getline(inFile,line);
                if(line=="true"){
                    g.directed=true;
                }
            }
            if(line=="cities"){
                while(std::getline(inFile,line)&&line!="edges"){
                    g.addNode(line);
                }
            }
            if(line=="edges"){
                while(std::getline(inFile,line)){
                    std::vector<std::string> s = splitByDelimiter(line,' ');
                    g.addEdge(s[0],s[1],std::stoi(s[2]));
                }
            }
        }

    }
    inFile.close();
    return g;
}



int main() {
int* vals = new int[3]{100,60,120};
int* wts = new int[3]{20,10,30};
int capacity = 50;
int n = 3;
BinaryKnapsack knapsack(vals,wts,capacity,n);
std::cout<<knapsack.solveGenetic(3,50,0.8,0.2);

return 0;
}
