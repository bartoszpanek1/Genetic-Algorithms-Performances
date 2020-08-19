#include <iostream>
#include "headers/Graph.h"
#include "headers/BinaryKnapsack.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>
#include <math.h>
#include <bitset>


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

    int* val1=new int[3];
    int* wt1=new int[3];
    val1[0]=60;
    val1[1]=100;
    val1[2]=120;

    wt1[0]=10;
    wt1[1]=20;
    wt1[2]=30;
    int capacity=50;
int n=3;
BinaryKnapsack knapsack(val1,wt1,capacity,n);
std::cout<<knapsack.solveRecursion()<<std::endl;
return 0;
}
