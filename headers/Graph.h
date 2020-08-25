//
// This class is a graph representation and contains graph methods
//

#ifndef GENETIC_ALGORITHM_PERFORMANCES_GRAPH_H
#define GENETIC_ALGORITHM_PERFORMANCES_GRAPH_H


#include <unordered_set>
#include <unordered_map>
#include <map>
#include "Node.h"

template<typename T>
class Graph {
private:
    void naiveHelper(T current, std::unordered_set<T> visited, T start,int costSum, int& minSum);

public:
    //variables
    typedef std::unordered_map<T, Node<T> *> NodesMap;
    NodesMap nodes;
    bool directed;

    //constructors
    Graph();

    explicit Graph(bool directed);

    ~Graph();

    Graph(const Graph<T> &oldObj);

    //methods
    void addNode(const T &);

    void addEdge(const T &from, const T &to, int cost);

    int getDistance(T from, T to);

    bool isConnected();

    int size();

    int solveTSPNaive(T from); // naive solution to the traveling salesman problem

    std::vector<std::vector<T>> generateRandomPaths(T from,int noOfPaths);

    int calculateCostOfPath(std::vector<T> path);


    template<typename S>
    friend std::ostream &operator<<(std::ostream &out, const Graph<S> &g);
};


#endif //GENETIC_ALGORITHM_PERFORMANCES_GRAPH_H
