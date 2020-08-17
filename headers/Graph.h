//
// Created by bartosz on 16.08.2020.
//

#ifndef GENETIC_ALGORITHM_PERFORMANCES_GRAPH_H
#define GENETIC_ALGORITHM_PERFORMANCES_GRAPH_H



#include <unordered_map>
#include "Node.h"
template<typename T>
class Graph {
public:
    //variables
    typedef std::unordered_map<T,Node<T>*> NodesMap;
    NodesMap nodes;
    bool directed;

    //constructors
    Graph();
    explicit Graph(bool directed);
    ~Graph();
    Graph(const Graph<T> &oldObj);

    //methods
    void addNode(const T&);
    void addEdge(const T& from, const T& to, int cost);
    int size();
    template<typename S>
    friend std::ostream &operator<<(std::ostream& out, const Graph<S>& g);
};


#endif //GENETIC_ALGORITHM_PERFORMANCES_GRAPH_H
