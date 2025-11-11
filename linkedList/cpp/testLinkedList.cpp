#include "testLinkedList.h" 
#include <algorithm>            // std::reverse

std::ostream& operator << (std::ostream& os, const Difference& diff)
{
    os << "index: " << diff.index << ", list: " << diff.listVal
        << ", expected: " << diff.expectedVal << "\n";
    return os;
}

bool TestLinkedList::compareResult(const MyLinkedList& list, const std::vector<int>& expected, std::vector<Difference>& diff)
{
    const Node* current = list.head();
    size_t n = expected.size();
    size_t i;
    for(i = 0; current != nullptr && i < n; i++)
    {
        if(expected[i] != current->data)
        {
            Difference d = {current->data, expected[i], i};
            diff.push_back(d);
        }

        current = current->next;
    }

    if(i != n)
    {
        std::cerr << "[ERROR], function: " << __func__ << ", iteration stopped at i: " << i 
                << ", expected length n: " << n << "\n";
        std::cerr << "List\n" << list << "Expected\n";
        for(auto val : expected)
        {
            std::cerr << val << " ";
        }
        std::cerr << "\n";
        return false;
    }
    else if(diff.size() > 0)
    {
        std::cerr << "[ERROR], function: " << __func__ << ", differences between list and expected\n";
        std::cerr << "Differences\n";
        for(auto d : diff)
        {
            std::cerr << d;
        }
        std::cerr << "\n";
        return false;
    }

    return true;
}

void TestLinkedList::runInsertHeadTests()
{
    for(int i = 0; i < NUM_TESTS; i++)
    {
        int length = m_rg.generate(MIN_ARRAY_SIZE, MAX_ARRAY_SIZE);
        std::vector<int> testVals(length);
        fillRandom(testVals);

        
        // make reversed copy of test value 
        // linked list will be in reverse order of test values
        std::vector<int> expected(testVals);            // make copy
        std::reverse(expected.begin(), expected.end()); 

        testInsertHead(testVals, expected);
    }
    
}

 void TestLinkedList::fillRandom(std::vector<int>& testVals)
 {
    size_t n = testVals.size();
    for(size_t i = 0; i < n; i++)
    {
        testVals[i] = m_rg.generate(MIN_LIST_VALUE, MAX_LIST_VALUE);
    }
 }

void TestLinkedList::testInsertHead(const std::vector<int>& testVals, const std::vector<int>& expected)
{
    size_t n = testVals.size();

    MyLinkedList list;
    for(size_t i = 0; i < n; i++)
    {
        list.insertAtHead(testVals[i]);
    }

    std::vector<Difference> differences;
    if(!compareResult(list, expected, differences))
    {
        std::cerr << "[FATAL] function: " << __func__ << ", line: " << __LINE__
                << "testInsertHead returned false\n";
        std::exit(-1);
    }
}

#if 0
void TestLinkedList::testInsertTail()
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
void TestLinkedList::testInsertAtIndex()
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

void TestLinkedList::runAllTests()
{
    testInsertHead();
    testInsertTail();
    testInsertAtIndex();
}

#endif