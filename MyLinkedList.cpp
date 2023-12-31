#include "MyLinkedList.h"
#include "IntegerNode.h"

MyLinkedList::MyLinkedList() : head(nullptr), tail(nullptr) {
    
}

// Copy constructor - performing a shallow copy
MyLinkedList::MyLinkedList(const MyLinkedList& other) : head(nullptr), tail(nullptr) {
    Node* current_node = other.head;
    while (current_node != nullptr) {
        // Check the actual type of current_node->value and clone accordingly
        if (auto intNode = dynamic_cast<IntegerNode*>(current_node->value.get())) {
            append(make_unique<IntegerNode>(*intNode));
        } else if (auto listNode = dynamic_cast<MyLinkedList*>(current_node->value.get())) {
            append(make_unique<MyLinkedList>(*listNode)); // This will call MyLinkedList's copy constructor
        }
        current_node = current_node->next_node;
    }
}

// Destructor
MyLinkedList::~MyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next_node;
        delete current;
        current = next;
    }
}

// Append method
void MyLinkedList::append(unique_ptr<DataType> value) {
    Node* new_node = new Node(move(value));
    if (!head) {
        head = new_node;
        tail = head;
    } else {
        tail->next_node = new_node;
        tail = new_node;
    }
}

// Concat method - performing deep copies of the elements
MyLinkedList MyLinkedList::concat(const MyLinkedList& other_list) const {
    MyLinkedList concatenated_list;
    for (Node* current_node = head; current_node != nullptr; current_node = current_node->next_node) {
        if (auto intNode = dynamic_cast<IntegerNode*>(current_node->value.get())) {
            concatenated_list.append(make_unique<IntegerNode>(*intNode));
        } else if (auto listNode = dynamic_cast<MyLinkedList*>(current_node->value.get())) {
            concatenated_list.append(listNode->deep_copy());  // Call deep_copy for nested lists
        }
    }
    for (Node* current_node = other_list.head; current_node != nullptr; current_node = current_node->next_node) {
        if (auto intNode = dynamic_cast<IntegerNode*>(current_node->value.get())) {
            concatenated_list.append(make_unique<IntegerNode>(*intNode));
        } else if (auto listNode = dynamic_cast<MyLinkedList*>(current_node->value.get())) {
            concatenated_list.append(listNode->deep_copy());  // Call deep_copy for nested lists
        }
    }
    return concatenated_list;
}

// Check if the list is empty
bool MyLinkedList::is_empty() const {
    return head == nullptr;
}

// Get value at index
DataType* MyLinkedList::get_at_index(int index) const {
    if (index < 0 || is_empty()) {
        throw out_of_range("Index out of bounds");
    }

    Node* current_node = head;
    for (int current_index = 0; current_node != nullptr && current_index < index; ++current_index) {
        current_node = current_node->next_node;
    }

    if (current_node == nullptr) {
        throw out_of_range("Index out of bounds");
    }
    return current_node->value.get();
}

// Set value at index
void MyLinkedList::set_at_index(int index, unique_ptr<DataType> value) {
    if (index < 0) {
        throw out_of_range("Index out of bounds");
    }

    Node* current = head;
    for (int idx = 0; current != nullptr && idx < index; ++idx) {
        current = current->next_node;
    }

    if (current == nullptr) {
        throw out_of_range("Index out of bounds");
    }
    current->value = move(value);
}

unique_ptr<DataType> MyLinkedList::deep_copy() const {
    auto copied_list = make_unique<MyLinkedList>();
    for (Node* current_node = head; current_node != nullptr; current_node = current_node->next_node) {
        copied_list->append(current_node->value->deep_copy());
    }
    return copied_list;
}

string MyLinkedList::to_string() const {
    ostringstream oss;
    for (Node* current_node = head; current_node; current_node = current_node->next_node) {
        oss << current_node->value->to_string();  // Assuming DataType has to_string()
        if (current_node->next_node) {
            oss << ", ";
        }
    }
    return "(" + oss.str() + ")";
}
