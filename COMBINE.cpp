#include "COMBINE.h"
#include "Receiver.h"
#include "MyLinkedList.h"
#include <iostream>
#include <stdexcept>

COMBINE::COMBINE(const vector<string>& args) : Instruction(args) {}

void COMBINE::execute(Receiver& receiver) {
    if (args.size() != 2) {
        throw invalid_argument("COMBINE requires exactly two arguments");
    }

    const string& list1Name = args[0];
    const string& list2Name = args[1];

    DataType* data1 = receiver.getDataFromMemory(list1Name);
    DataType* data2 = receiver.getDataFromMemory(list2Name);

    if (!data1 || !data2) {
        throw runtime_error("One or both lists not found");
    }

    MyLinkedList* list1 = dynamic_cast<MyLinkedList*>(data1);
    MyLinkedList* list2 = dynamic_cast<MyLinkedList*>(data2);

    if (!list1 || !list2) {
        throw runtime_error("One or both identifiers are not lists");
    }

    // Create a new combined list and update list2 in identifiers
    MyLinkedList combinedList = list1->concat(*list2);
    receiver.updateDataMemory(list2Name, make_unique<MyLinkedList>(combinedList));
}
