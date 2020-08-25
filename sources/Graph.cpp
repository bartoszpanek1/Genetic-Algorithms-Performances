//
// This file contains code of all graph methods
//
#include <vector>
#include <ostream>
#include <iostream>
#include <queue>
#include "unordered_set"
#include "../headers/Graph.h"
#include <bits/stdc++.h>

template<typename T>
void Graph<T>::addNode(const T &val) {
    auto itr = nodes.find(val);

    if (itr == nodes.end()) {
        Node<T> *newNode;
        newNode = new Node<T>(val);
        nodes[val] = newNode;
    } else {
        std::cout << "Node already exists" << std::endl;
    }
}

template<typename T>
Graph<T>::~Graph() {
    for (std::pair<const T, Node<T> *> &p:nodes) {
        delete p.second;
        p.second = nullptr;
    }
}

template<typename T>
Graph<T>::Graph(const Graph<T> &oldObj) {
}

template<typename T>
Graph<T>::Graph() {
    directed = false;
}

template<typename S>
std::ostream &operator<<(std::ostream &out, const Graph<S> &g) {
    for (auto &pair : g.nodes) {
        out << pair.first << " is connected to: " << std::endl;
        for (auto &node_dist : pair.second->adj) {
            out << node_dist.first->getVal() << " (" << node_dist.second << ") ";
        }
        out << std::endl;
        out << "----------------------" << std::endl;

    }
    return out;
}

template<typename T>
void Graph<T>::addEdge(const T &from, const T &to, int cost) {
    Node<T> *f = nodes.find(from)->second;
    Node<T> *t = nodes.find(to)->second;
    f->adj.push_back(make_pair(t, cost));
    if (!directed) {
        t->adj.push_back(make_pair(f, cost));
    }
}

template<typename T>
Graph<T>::Graph(bool directed) {
    this->directed = directed;
}

template<typename T>
int Graph<T>::size() {
    return nodes.size();
}

template<typename T>
bool Graph<T>::isConnected() { //using BFS to check if graph is connected
    if (nodes.empty()) {
        return false;
    }
    Node<T> *n = nodes.begin()->second;
    std::queue<Node<T> *> queue;
    std::unordered_map<T, bool> visited;
    queue.push(n);;
    while (!queue.empty()) {
        Node<T> *n = queue.front();
        visited[n->getVal()] = true;
        queue.pop();
        for (auto pair : n->adj) {
            if (!visited[pair.first->getVal()]) {
                queue.push(pair.first);
            }
        }
    }
    return visited.size() == nodes.size();
}

template<typename T>
int Graph<T>::getDistance(T from, T to) {
    int dist = INT_MAX;
    if (nodes.contains(from) && nodes.contains(to)) {
        for (const auto &node:nodes[from]->adj) {
            if (node.first->getVal() == to) {
                return node.second;
            }
        }
    }
    return dist;
}

template<typename T>
int Graph<T>::solveTSPNaive(T from) {
    int minSum = INT_MAX;
    std::unordered_set<T> visited;
    visited.insert(from);
    naiveHelper(from, visited, from, 0, minSum);
    return minSum;
}

template<typename T>
void Graph<T>::naiveHelper(T current, std::unordered_set<T> visited, T start,int costSum, int& minSum) {
    if(visited.size()==nodes.size()){
        int finalSum = costSum+getDistance(current, start);
        minSum = finalSum < minSum ? finalSum : minSum;
    }
    for(auto pair : nodes[current]->adj){
        if(!visited.contains(pair.first->getVal())){
            visited.insert(pair.first->getVal());
            naiveHelper(pair.first->getVal(),visited,start,costSum+pair.second,minSum);
            visited.erase(pair.first->getVal());
        }
    }
}

template<typename T>
std::vector<std::vector<T>> Graph<T>::generateRandomPaths(T from,int noOfPaths) {
    std::vector<T> initialPath;
    initialPath.push_back(from);
    for(const auto& node : nodes){
        if(node.first!=from){
            initialPath.push_back(node.first);
        }
    }
    std::vector<std::vector<T>> paths;
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};
    std::shuffle(std::next(std::begin(initialPath)),std::end(initialPath),rng);
    for(int i=0;i<noOfPaths;i++){
        std::vector<T> path = initialPath;
        std::shuffle(std::next(std::begin(path)),std::end(path),rng);
        paths.push_back(path);
    }
    return paths;
}

template<typename T>
int Graph<T>::calculateCostOfPath(std::vector<T> path) {
    int cost = 0;
    for(int i=0;i<path.size()-1;i++){
        int d = getDistance(path[i],path[i+1]);
        if(d==INT_MAX){
            return INT_MAX;
        }
        cost+=d;
    }
    return cost;
}


template
class Graph<std::string>;

template std::ostream &operator<<(std::ostream &out, const Graph<std::string> &g);