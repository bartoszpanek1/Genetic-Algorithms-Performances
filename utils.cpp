//
//This is a file containing functions
//needed to correctly load the data or show results
//

#include <string>
#include <vector>
#include <fstream>
#include "headers/Graph.h"


std::vector<std::string> splitByDelimiter(const std::string &toSplit, char delimiter) {
    std::vector<std::string> retVec;
    std::string word;
    for (auto c : toSplit) {
        if (c == delimiter) {
            retVec.push_back(word);
            word = "";
        } else {
            word += c;
        }
    }
    retVec.push_back(word);
    return retVec;
}

Graph<std::string> graphFromFile(const std::string &fileName) {
    Graph<std::string> g;
    std::ifstream inFile;
    inFile.open("data");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (line == "directed") {
                std::getline(inFile, line);
                if (line == "true") {
                    g.directed = true;
                }
            }
            if (line == "cities") {
                while (std::getline(inFile, line) && line != "edges") {
                    g.addNode(line);
                }
            }
            if (line == "edges") {
                while (std::getline(inFile, line)) {
                    std::vector<std::string> s = splitByDelimiter(line, ' ');
                    g.addEdge(s[0], s[1], std::stoi(s[2]));
                }
            }
        }

    }
    inFile.close();
    return g;
}
