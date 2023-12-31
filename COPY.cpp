#include "COPY.h"
#include "Receiver.h"
#include "MyLinkedList.h"
#include <stdexcept>
#include <string>
#include <memory>

COPY::COPY(const vector<string>& args) : Instruction(args) {}

void COPY::execute(Receiver& receiver) {
    if (args.size() != 2) {
        throw invalid_argument("COPY requires exactly two arguments");
    }

    const string& target_list_identifier = args[0];
    const string& source_list_identifier = args[1];

    DataType* source_data = receiver.getDataFromMemory(source_list_identifier);
    if (!source_data) {
        throw runtime_error("Source list not found: " + source_list_identifier);
    }

    MyLinkedList* source_list = dynamic_cast<MyLinkedList*>(source_data);
    if (!source_list) {
        throw runtime_error("Source identifier is not a list: " + source_list_identifier);
    }

    // Create a new list for the shallow copy
    unique_ptr<MyLinkedList> copied_list = make_unique<MyLinkedList>(*source_list);

    // Assign the shallow copied list to the target identifier
    receiver.updateDataMemory(target_list_identifier, move(copied_list));
}
