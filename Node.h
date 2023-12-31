#ifndef NODE_H
#define NODE_H

#include <memory>
#include "DataType.h"

class Node {
public:
    unique_ptr<DataType> value;
    Node* next_node;

    Node(unique_ptr<DataType> val) : value(move(val)), next_node(nullptr) {}
};

#endif // NODE_H
