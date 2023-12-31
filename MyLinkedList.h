#ifndef MYLINKEDLIST_H
#define MYLINKEDLIST_H

#include "Node.h"
#include <memory>
#include <sstream>

class MyLinkedList : public DataType {
private:
    Node* head;
    Node* tail;

public:
    MyLinkedList();
    MyLinkedList(const MyLinkedList& other);
    ~MyLinkedList();
    MyLinkedList& operator=(const MyLinkedList& other);

    void append(unique_ptr<DataType> value);
    MyLinkedList concat(const MyLinkedList& other_list) const;

    bool is_empty() const;
    DataType* get_at_index(int index) const;
    void set_at_index(int index, unique_ptr<DataType> value);

    string to_string() const override;
    unique_ptr<DataType> deep_copy() const override;

};

#endif // MYLINKEDLIST_H
