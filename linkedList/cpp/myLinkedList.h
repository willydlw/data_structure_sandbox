#pragma once 

#include <iostream>

struct Node{
    int data;
    Node* next;

    Node() : data(0), next(nullptr) {}
    Node(int val) : data(val), next(nullptr) {}
};


class MyLinkedList{
    public:

    MyLinkedList();
    ~MyLinkedList();

    void insertAtHead(int val);
    void insertAtTail(int val);
    void insertAtIndex(int index, int val);

    void deleteAtHead();
    void deleteAtIndex(int index);

    // returns pointer to node at index location
    // return nullptr for invalid index (index > list length)
    const Node* get(int index);  

    friend std::ostream& operator << (std::ostream& os, const MyLinkedList& list);

    const Node* head() const;

    private:

    Node* headptr = nullptr;
};