//
// This class is used only in Graph class
//

#ifndef GENETIC_ALGORITHM_PERFORMANCES_NODE_H
#define GENETIC_ALGORITHM_PERFORMANCES_NODE_H

#include <utility>
#include <vector>

template<typename T>
class Node {
private:
    T val;

public:
    //variables
    typedef std::pair<Node<T> *, int> v;
    std::vector<v> adj;

    //constructors
    explicit Node(T);

    ~Node();

    //methods
    T getVal();

    template<typename S>
    friend std::ostream &operator<<(std::ostream &out, const Node<S> &n);
};


#endif //GENETIC_ALGORITHM_PERFORMANCES_NODE_H
