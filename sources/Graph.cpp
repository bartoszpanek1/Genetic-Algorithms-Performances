//
// Created by bartosz on 16.08.2020.
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
    std::cout << "Graph destructor" << std::endl;
    for (std::pair<const T, Node<T> *> &p:nodes) {
        delete p.second;
        p.second = nullptr;
    }
}

template<typename T>
Graph<T>::Graph(const Graph<T> &oldObj) {
    std::cout << "Graph copy constructor" << std::endl;
}

template<typename T>
Graph<T>::Graph() {
    std::cout << "Graph default constructor" << std::endl;
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
    std::cout << "Graph parametrized constructor" << std::endl;
    this->directed = directed;
}

template<typename T>
int Graph<T>::size() {
    return nodes.size();
}

template<typename T>
bool Graph<T>::isConnected() { //using BFS to check if graph is connected
    if(nodes.empty()){
        return false;
    }
    Node<T>* n = nodes.begin()->second;
    std::queue<Node<T>*> queue;
    std::unordered_map<T, bool> visited;
    queue.push(n);;
    while(!queue.empty()){
        Node<T>* n = queue.front();
        visited[n->getVal()]=true;
        queue.pop();
        for(auto pair : n->adj){
            if(!visited[pair.first->getVal()]){
                queue.push(pair.first);
            }
        }
    }
    return visited.size()==nodes.size();
}

template<typename T>
int Graph<T>::getDistance(T from, T to) {
    int dist = INT_MAX;
    if(nodes.contains(from)&&nodes.contains(to)){
        for(const auto& node:nodes[from]->adj){
            if(node.first->getVal()==to){
                return node.second;
            }
        }
    }
    return dist;
}


template class Graph<std::string>;
template std::ostream &operator<<(std::ostream &out, const Graph<std::string> &g);