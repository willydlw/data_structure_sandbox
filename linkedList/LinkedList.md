# Linked List 

- Linear data structure composed of a sequence of nodes 
- Each node contains data and a pointer to the next node in the sequence 
- Nodes are not stored in contiguous memory 


## Node Structure 

Nodes are typically defined using a data structure that contains the data field and a pointer to a node. 

C Language example:

```C
typdef struct Node{
    data_type data;
    struct Node* next;
} Node;
``` 


## Head Pointer 

A Node* pointer, usually named head, points to the first node in the linked list. If the head pointer is NULL, the list is empty. 

## Dynamic Memory Allocation 

Nodes are created and destroyed using dynamic memory allocation, allowing the list to grow or shrink as needed during program execution. 

## Common List Operations 

### Insertion:

- Insert at beginning
    - Create new node 
    - Set new node pointer to the current head pointer
    - Update the head pointer to point to the new node
- Insert at end 
    - Creat new node
    - Traverse the list to find the last node.
    - Set last node's next pointer to new node 
    - Set the new node's next pointer to NULL 
- Insert before specific location
    - Create new node
    - Traverse the list to the node before the desired location 
    - Link the new node between the predecessor node and its successor 


### Deletion 

- Delete from beginning 
    - Update the head pointer to point to the second node 
    - Free memory of the original first node 
- Delete from end 
    - Traverse the list to the second to last node.
    - Set second to last node's next pointer to NULL
    - Free memory of last node 
- Delete from specific location 
    - Traverse to node before target node 
    - Link previous node's next pointer to target node's next pointer 
    - Free target node memory

### Traversal 

Iterate through the list from the head to the last node by following the next pointers.


## Advantages 
- Dynamic size allows efficient memory usage
- Efficient insertion and deletion operations compared to contiguous data structures like arrays 

## Disadvantages 
- Random access to data is not efficient, requiring traversal through the list 
- Requires more memory per element due to storage of pointers


## Singly Linked List Operations in C

The code examples below assume that dynamic memory is allocated and does not include code for safe-guarding against failure. This is done to focus on the linked list implementation.

### Define node data structure 

A list node has two components:
- Data: actual information or vale that the node represents 
- Next pointer: This is a reference or address to the next node in the sequence of the linked list. This pointer is what connects the nodes together, forming the list. The next pointer of the last list node points to null to signify the end of the list.

```c 
struct Node{
    int data;
    struct Node* next;
};

```

### Create new node function

List insert operations all require dynamically allocating memory for a new node. To reduce code repetition, we define a create node function.

```c
struct Node* createNode(int data){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct(Node)));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
```

### Create Head Pointer

The pointer to the first list node is called the head pointer. Upon definition, the head pointer is set to NULL because the list is empty. We have not yet allocated any list nodes to which it points.

```c
// Define the list head pointer
Node* headptr = NULL;
``` 

### Insert at head 

The Insert at Head list operation appends a new node at the start of the singly linked list. When performing this operation, there are two cases to consider: (1) list is empty, (2) list contains one or more nodes.

Case 1: Empty List 
- Head pointer is null
- Create new node 
- Store data in new node
- Set new node next pointer to null. Since head is null, we set new node's next to head.
- Set head pointer to new node 

Case 2: Non-Empty List 
- Head pointer is not null, points to first node in list 
- Create new node
- Store data in new node
- Set new node's next pointer to head pointer
- Set head pointer to new node 


```c 
void insertAtHead(struct Node** head, int data){
    // Create new node 
    struct Node* newNode = createNode(data);

    // set new node's next pointer to head 
    // Note that when list is empty (head is NULL), this is newNode->next = NULL
    newNode->next = *head; 

    // Set head pointer to new node         
    *head = newNode;
}
``` 


### Insert at tail 

The end of a linked list is often referred to as the tail. Inserting at tail means we add a new element at the list's end.

Case 1: Empty list 
- Head pointer is null 
- Create a new node 
- Set the head pointer to the new node 

Case 2: Non-empty list 
- Find pointer to the last node in list
- Create new node 
- Set last node pointer to new node

```c
void insertAtTail(Node** head, int data) {
    // Create new node 
    Node* newNode = createNode(data);

    // Case 1: empty list
    if(*head == NULL){
        *head = newNode;
        return;
    }

    // Case 2: Non-empty list
    // Iterate through the list to find the last node
    // The next pointer of the last node is null
    struct Node* tail = *head;
    while(tail->next != NULL){
        tail = tail->next;
    }

    // Set last node pointer to new node
    tail->next = newNode;
}
```