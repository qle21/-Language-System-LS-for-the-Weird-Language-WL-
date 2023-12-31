#include "IF.h"
#include "Receiver.h"
#include "MyLinkedList.h"
#include "IntegerNode.h"
#include <stdexcept>

IF::IF(const vector<string>& args) : Instruction(args), jumpLine(-1) {}

void IF::execute(Receiver& receiver) {
    if (args.size() != 2) {
        throw invalid_argument("IF requires exactly two arguments");
    }

    const string& x_identifier = args[0];
    jumpLine = stoi(args[1]);

    // Retrieve data from receiver
    DataType* x_value = receiver.getDataFromMemory(x_identifier);

    if (!x_value) {
        throw runtime_error("Identifier not found: " + x_identifier);
    }

    // Check if x is an empty list or zero
    MyLinkedList* list = dynamic_cast<MyLinkedList*>(x_value);
    IntegerNode* intNode = dynamic_cast<IntegerNode*>(x_value);
    if ((list && list->is_empty()) || (intNode && intNode->value == 0)) {
        // jumpLine is already set
    } else {
        jumpLine = -1; // No jump required
    }
}

int IF::getJumpLine() const {
    return jumpLine;
}
