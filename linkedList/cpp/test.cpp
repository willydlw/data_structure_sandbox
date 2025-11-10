#include "test.h" 


bool compareResult(const int* expected, int n, const MyLinkedList& list)
{
    const Node* current = list.head();
    int i;
    for(i = 0; current != nullptr && i < n; i++)
    {
        if(expected[i] != current->data)
        {
            std::cerr << "[ERROR] expected[" << i << "]  " << expected[i] 
                    << " != " << current->data << "\n";
            return false;
        }

        current = current->next;
    }

    if(i != n)
    {
        std::cerr << "[ERROR], function: " << __func__ << ", iteration stopped at i: " << i 
                << ", length n: " << n << "\n";
        return false;
    }

    return true;
}

void testInsertHead()
{
    {
        const int testData[3] = {1, 2, 3};
        const int expected[3] = {3, 2, 1};
        MyLinkedList list;
        for(int i = 0; i < 3; i++){
            list.insertAtHead(testData[i]);
        }

        if(!compareResult(expected, 3, list))
        {
            std::cerr << "[ERROR], function: " << __func__ << "\n";
        }
    }
}

void testInsertTail()
{
    {
        const int testData[3] = {1, 2, 3};
        const int expected[3] = {1, 2, 3};
        MyLinkedList list;
        for(int i = 0; i < 3; i++){
            list.insertAtTail(testData[i]);
        }

        if(!compareResult(expected, 3, list))
        {
            std::cerr << "[ERROR], function: " << __func__ << "\n";
        }
    }
}
void testInsertAtIndex()
{
    {
        std::cerr << "Test 1\n";
        const int expected[3] = {1, 2, 3};

        MyLinkedList list;
        list.insertAtHead(1);
        list.insertAtTail(3);
        list.insertAtIndex(1, 2);
        compareResult(expected, 3, list);

        int val = list.get(1);
        if(val != 2){
            std::cerr << "ERROR, get(1) returned " << val << ", expected: " << expected << "\n";
            std::cerr << "List contents: " << list << "\n";
        }

        std::cerr << "Before deleting at index 0, list contents: " << list << "\n";

        list.deleteAtIndex(0);

        std::cerr << "After deleting at index 0, list contents: " << list << "\n";

        val = list.get(0);
        if(val != 2){
            std::cerr << "ERROR, line: " << __LINE__ << " get(0) returned " << val << ", expected: " << expected << "\n";
            std::cerr << "List contents: " << list << "\n";
        }

    }

    {
        std::cerr << "Test 2\n";

        const int expected[2] = {1,2};
        MyLinkedList list;
        list.insertAtHead(2);
        list.insertAtIndex(0,1);
        compareResult(expected, 2, list);

        std::cerr << "List contents: " << list;
        int val = list.get(1);
        if(val != 2){
            std::cerr << "ERROR, line: " << __LINE__ << ", get(0) returned " << val << ", expected: " << expected << "\n";
            std::cerr << "List contents: " << list << "\n";
        }
    }
}

void runTests()
{
    testInsertHead();
    testInsertTail();
    testInsertAtIndex();
}