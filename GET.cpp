#include "GET.h"
#include "Receiver.h"
#include "MyLinkedList.h"
#include "DataType.h"
#include <stdexcept>

GET::GET(const vector<string>& args) : Instruction(args) {
    // Constructor implementation (if needed)
}

void GET::execute(Receiver& receiver) {
    if (args.size() != 3) {
        throw invalid_argument("GET requires exactly three arguments");
    }

    const string& var_name = args[0];
    int index = stoi(args[1]);
    const string& list_name = args[2];

    // Retrieve data from receiver
    DataType* list_data = receiver.getDataFromMemory(list_name);

    if (!list_data) {
        throw runtime_error("List not found: " + list_name);
    }

    MyLinkedList* linked_list = dynamic_cast<MyLinkedList*>(list_data);

    if (!linked_list) {
        throw runtime_error("Identifier is not a list: " + list_name);
    }

    DataType* data_at_index = linked_list->get_at_index(index);

    if (!data_at_index) {
        throw runtime_error("Index out of bounds in list: " + list_name);
    }

    // Update the receiver's data memory to reference the data_at_index directly
    receiver.updateDataMemory(var_name, unique_ptr<DataType>(data_at_index)); // PLEASE NOTE THAT THIS PERFORMS SHALLOW COPY AS PER THE PROJECT INSTRUCTIONS
}
