#include "SET.h"
#include "Receiver.h"
#include "MyLinkedList.h"
#include "IntegerNode.h"
#include <stdexcept>
#include <regex>

SET::SET(const vector<string>& args) : Instruction(args) {}

void SET::execute(Receiver& receiver) {
    if (args.size() != 3) {
        throw invalid_argument("SET requires exactly three arguments");
    }

    const string& value_or_identifier = args[0];
    int index = stoi(args[1]);
    const string& list_identifier = args[2];

    // Retrieve data from receiver
    DataType* list_data = receiver.getDataFromMemory(list_identifier);

    if (!list_data) {
        throw runtime_error("List not found: " + list_identifier);
    }

    MyLinkedList* list = dynamic_cast<MyLinkedList*>(list_data);

    if (!list) {
        throw runtime_error("Identifier is not a list: " + list_identifier);
    }

    regex integer_regex("^\\d+$");
    if (regex_match(value_or_identifier, integer_regex)) {
        // If value_or_identifier is an integer constant
        list->set_at_index(index, make_unique<IntegerNode>(stoi(value_or_identifier)));
    } else {
        // Check if value_or_identifier is another variable in receiver's data memory
        DataType* value_data = receiver.getDataFromMemory(value_or_identifier);

        if (!value_data) {
            throw runtime_error("Invalid identifier: " + value_or_identifier);
        }

        // Set the value at the specified index in the list
        list->set_at_index(index, value_data->deep_copy());
    }
}
