#include "VARINT.h"
#include "Receiver.h"
#include "IntegerNode.h"
#include <stdexcept>

VARINT::VARINT(const vector<string>& args) : Instruction(args) {

}

void VARINT::execute(Receiver& receiver) {
    if (args.size() != 2) {
        throw invalid_argument("VARINT requires exactly two arguments");
    }

    const string& var_name = args[0];
    int value = stoi(args[1]); // Assuming args[1] is a string that can be converted to an integer

    // Create a new IntegerNode and assign the integer value to the variable in the receiver's data memory
    receiver.updateDataMemory(var_name, make_unique<IntegerNode>(value));
}
