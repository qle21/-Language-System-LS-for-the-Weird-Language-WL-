#include "ADD.h"
#include "Receiver.h"
#include "IntegerNode.h"
#include <stdexcept>
#include <string>

ADD::ADD(const vector<string>& args) : Instruction(args) {
    
}

void ADD::execute(Receiver& receiver) {
    if (args.size() != 2) {
        throw invalid_argument("ADD requires exactly two arguments");
    }

    const string& arg1 = args[0];
    const string& arg2 = args[1];

    // Retrieve data from receiver
    DataType* data1 = receiver.getDataFromMemory(arg1);
    DataType* data2 = receiver.getDataFromMemory(arg2);

    if (!data1 || !data2) {
        throw runtime_error("One or more identifiers not found in data memory");
    }

    IntegerNode* int1 = dynamic_cast<IntegerNode*>(data1);
    IntegerNode* int2 = dynamic_cast<IntegerNode*>(data2);

    if (!int1 || !int2) {
        throw runtime_error("One or more identifiers are not integers");
    }

    // Perform addition and update the value
    int1->value += int2->value;
    receiver.updateDataMemory(arg1, make_unique<IntegerNode>(int1->value));
}
