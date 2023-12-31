#include "VARLIST.h"
#include "Receiver.h"
#include "MyLinkedList.h"
#include "IntegerNode.h"
#include <stdexcept>
#include <iostream>
#include <string>

VARLIST::VARLIST(const vector<string>& args) : Instruction(args) {
   
}

void VARLIST::execute(Receiver& receiver) {
    if (args.empty()) {
        throw invalid_argument("VARLIST requires at least one argument");
    }

    const string& var_name = args[0];
    auto linked_list = make_unique<MyLinkedList>();

    for (size_t i = 1; i < args.size(); ++i) {
        string valueStr = args[i];

        // Remove trailing comma if present
        size_t commaPos = valueStr.find(',');
        if (commaPos != string::npos) {
            valueStr = valueStr.substr(0, commaPos);
        }

        int value = stoi(valueStr);
        linked_list->append(make_unique<IntegerNode>(value));
    }

    receiver.updateDataMemory(var_name, move(linked_list));
}
