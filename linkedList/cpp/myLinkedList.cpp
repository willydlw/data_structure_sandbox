#include "myLinkedList.h"


 MyLinkedList::MyLinkedList() : headptr(nullptr) 
 {  /* intentionally blank */ }

 MyLinkedList::~MyLinkedList()
 {
    while(headptr != nullptr)
    {
        Node* temp = headptr->next;
        delete headptr;
        headptr = temp;
    }
 }


 void MyLinkedList::insertAtHead(int val)
 {
    Node* newNode = new Node(val);
    newNode->next = headptr;
    headptr = newNode;
 }

 void MyLinkedList::insertAtTail(int val)
 {
    if(headptr == nullptr)
    {
        insertAtHead(val);
        return;
    }

    Node* tailptr = headptr;
    while(tailptr->next != nullptr)
    {
        tailptr = tailptr->next;
    }

    // tailptr points to last node in the list 
    Node* newNode = new Node(val);
    tailptr->next = newNode;
 }

 void MyLinkedList::insertAtIndex(int index, int val)
 {
    if(index < 0){
        //std::cerr << "function: " << __func__ << ", index " << index << " is invalid\n";
        return;
    }

    if(index == 0){
        insertAtHead(val);
        return;
    }

    Node* current = headptr;
    for(int i = 0; current != nullptr && i < index-1; i++)
    {
        current = current->next;
    }

    if(current == nullptr){
        //std::cerr << "function: " << __func__ << ", index " << index 
        //        << " is invalid, longer than list length, current == nullptr\n";
        return;
    }

    Node* newNode = new Node(val);
    newNode->next = current->next;
    current->next = newNode;
 }

const Node* MyLinkedList::get(int index)
{
    if(headptr == nullptr || index < 0){
        return nullptr;
    }

    if(index == 0){
        return headptr;
    }

    Node* current = headptr;
    int i;
    for(i = 0; current != nullptr && i < index; i++){
        current = current->next;
    }

    return current;
}


void MyLinkedList::deleteAtHead()
{
    if(headptr == nullptr){
        //std::cerr << "[WARNING], function: " << __func__ << " cannot delete from empty list\n";
        return;
    }

    Node* temp = headptr->next;
    delete headptr;
    headptr = temp;
}

void MyLinkedList::deleteAtIndex(int index)
{
    if(headptr == nullptr){
        //std::cerr << "[WARNING], function: " << __func__ << " cannot delete from empty list\n";
        return;
    }

    if(index < 0){
        //std::cerr << "[WARNING], function: " << __func__ << " invalid index: " << index << "\n";
        return;
    }

    if(index == 0){
        deleteAtHead();
        return;
    }

    Node* current = headptr;
    for(int i = 0; current != nullptr && i < index-1; i++)
    {
        current = current->next;
    }

    if(current == nullptr || current->next == nullptr){
        //std::cerr << "[WARNING], function: " << __func__ << " index: " << index << " out of range\n";
        return;
    }

    // current->next points to node to be deleted
    Node* next = current->next->next;
    delete current->next;
    current->next = next;
}

const Node* MyLinkedList::head() const
{
    return headptr;
}

int MyLinkedList::length() const
{
    int count = 0;
    Node* current = headptr;
    while(current != nullptr)
    {
        count++;
        current = current->next;
    }

    return count;
}


std::ostream& operator << (std::ostream& os, const MyLinkedList& list)
{
    Node* current = list.headptr;
    while(current != nullptr)
    {
        os << current->data << " ";
        current = current->next;
    }

    os << "\n";
    return os;
}