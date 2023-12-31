#include "CHS.h"
#include "Receiver.h"
#include "IntegerNode.h"
#include <stdexcept>
#include <string>

CHS::CHS(const vector<string>& args) : Instruction(args) {}

void CHS::execute(Receiver& receiver) {
    if (args.size() != 1) {
        throw invalid_argument("CHS requires exactly one argument");
    }

    const string& var_name = args[0];

    DataType* data = receiver.getDataFromMemory(var_name);
    if (!data) {
        throw runtime_error("Variable not found: " + var_name);
    }

    IntegerNode* intNode = dynamic_cast<IntegerNode*>(data);
    if (!intNode) {
        throw runtime_error("Variable is not an integer: " + var_name);
    }

    intNode->value = -intNode->value;
    receiver.updateDataMemory(var_name, make_unique<IntegerNode>(intNode->value));
}
