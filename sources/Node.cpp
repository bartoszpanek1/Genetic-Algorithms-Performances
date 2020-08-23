//
// Created by bartosz on 16.08.2020.
//

#include <iostream>
#include <unordered_map>
#include "../headers/Node.h"

template<typename T>
Node<T>::Node(T val) {
    this->val = val;

}

template<typename T>
Node<T>::~Node() {

}

template<typename T>
T Node<T>::getVal() {
    return val;
}

template<typename S>
std::ostream &operator<<(std::ostream &out, const Node<S> &n) {
    std::cout < n.val << std::endl;
    return out << n.val;
}


template
class Node<std::string>;