#ifndef MYLINKEDLIST_H
#define MYLINKEDLIST_H

#include <sstream>

template <typename T>
class MyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    MyLinkedList() : head(nullptr), tail(nullptr) {}

    ~MyLinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next_node;
            delete current;
            current = next;
        }
    }

    void append(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (!head) {
            head = new_node;
            tail = head;
        } else {
            tail->next_node = new_node;
            tail = new_node;
        }
    }

    MyLinkedList<T> concat(const MyLinkedList<T>& other_list) {
        MyLinkedList<T> concatenated_list;
        for (Node<T>* current_node = head; current_node != nullptr; current_node = current_node->next_node) {
            concatenated_list.append(current_node->value);
        }
        for (Node<T>* current_node = other_list.head; current_node != nullptr; current_node = current_node->next_node) {
            concatenated_list.append(current_node->value);
        }
        return concatenated_list;
    }

    bool is_empty() const {
        return head == nullptr;
    }

    MyLinkedList<T> deep_copy() const {
        MyLinkedList<T> copied_list;
        for (Node<T>* current_node = head; current_node != nullptr; current_node = current_node->next_node) {
            copied_list.append(current_node->value);
        }
        return copied_list;
    }

    T get_at_index(int index) const {
        if (index < 0 || is_empty()) {
            throw out_of_range("Index out of bounds");
        }

        Node<T>* current_node = head;
        for (int current_index = 0; current_node != nullptr && current_index < index; ++current_index) {
            current_node = current_node->next_node;
        }

        if (current_node == nullptr) {
            throw out_of_range("Index out of bounds");
        }
        return current_node->value;
    }

    void set_at_index(int index, T value) {
        if (index < 0) {
            throw out_of_range("Index out of bounds");
        }

        Node<T>* current = head;
        for (int idx = 0; current != nullptr && idx < index; ++idx) {
            current = current->next_node;
        }

        if (current == nullptr) {
            throw out_of_range("Index out of bounds");
        }
        current->value = value;
    }

    string to_string() const {
        ostringstream oss;
        for (Node<T>* current_node = head; current_node != nullptr; current_node = current_node->next_node) {
            oss << current_node->value;
            if (current_node->next_node != nullptr) {
                oss << ", ";
            }
        }
        return "(" + oss.str() + ")";
    }

    // Functions for internal use
    Node<T>* get_head() const {
        return head;
    }
    Node<T>* get_tail() const {
        return tail;
    }

};

#endif // MYLINKEDLIST_H
