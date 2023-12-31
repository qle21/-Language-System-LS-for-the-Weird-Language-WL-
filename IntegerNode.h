#ifndef INTEGER_NODE_H
#define INTEGER_NODE_H

#include <string>
#include "DataType.h"

class IntegerNode : public DataType {
public:
    int value;

    IntegerNode(int val) : value(val) {}

    unique_ptr<DataType> deep_copy() const override {
        return make_unique<IntegerNode>(value);
    }

    string to_string() const override {
        return std::to_string(value);
    }
};

#endif // INTEGER_NODE_H
