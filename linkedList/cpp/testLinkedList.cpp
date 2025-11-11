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

void TestLinkedList::runInsertHeadTests(int numTests)
{
    for(int i = 0; i < numTests; i++)
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

void TestLinkedList::runInsertTailTests(int numTests)
{
    for(int i = 0; i < numTests; i++)
    {
        int length = m_rg.generate(MIN_ARRAY_SIZE, MAX_ARRAY_SIZE);
        std::vector<int> testVals(length);
        fillRandom(testVals);

        // make reversed copy of test value 
        // linked list will be in same order as testVals when adding at tail
        std::vector<int> expected(testVals);            // make copy

        testInsertTail(testVals, expected);
    }
}

void TestLinkedList::runInsertIndexTests(int numTests)
{
    #if 0
    {
        // empty list test, insert at index 0 
        std::vector<int> buildVals;         // empty vector should cause empty list

        int val = m_rg.generate(MIN_LIST_VALUE, MAX_LIST_VALUE);
        std::vector<int> expected = {val};
        std::pair<int, int> pair = {0, val}; 
        std::vector<std::pair<int,int>> insertVals;
        insertVals.push_back(pair);
        testInsertAtIndex(buildVals, expected, insertVals);
    }

    {
        // empty list test, insert at index 1 
        // should not insert value into list 
        std::vector<int> buildVals;         // empty vector should cause empty list

        int val = m_rg.generate(MIN_LIST_VALUE, MAX_LIST_VALUE);
        std::vector<int> expected;
        std::pair<int, int> pair = {1, val}; 
        std::vector<std::pair<int,int>> insertVals;
        insertVals.push_back(pair);
        testInsertAtIndex(buildVals, expected, insertVals);
    }
    #endif

    numTests = 1;

    // build list 
    for(int i = 0; i < numTests; i++)
    {
        std::vector<int> buildVals;
        std::vector<int> expectedVals;
        appendVals(buildVals, 1, 11, 2);
        appendVals(expectedVals, 0, 12, 1);

        std::vector<std::pair<int,int>> insertPairs;

        for(int i = 0; i < 6; i++)
        {
            std::pair<int,int> pair = {2*i, 2*i};
            insertPairs.push_back(pair);
        }
        testInsertAtIndex(buildVals, expectedVals, insertPairs);

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


void TestLinkedList::appendVals(std::vector<int>& array, int start, int stop, int step)
{
    for(int i = start; i <= stop; i += step)
    {
        array.push_back(i);
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


void TestLinkedList::testInsertTail(const std::vector<int>& testVals, const std::vector<int>& expected)
{
     size_t n = testVals.size();

    MyLinkedList list;
    for(size_t i = 0; i < n; i++)
    {
        list.insertAtTail(testVals[i]);
    }

    std::vector<Difference> differences;
    if(!compareResult(list, expected, differences))
    {
        std::cerr << "[FATAL] function: " << __func__ << ", line: " << __LINE__
                << "testInsertTail returned false\n";
        std::exit(-1);
    }  
}


void TestLinkedList::testInsertAtIndex(const std::vector<int>& buildVals, const std::vector<int>& expected,
                            const std::vector<std::pair<int,int>>& insertVals)
{
    // Build list 
    MyLinkedList list;
    for(auto v : buildVals)
    {
        list.insertAtTail(v);
    }

    for(auto pair : insertVals)
    {
        list.insertAtIndex(pair.first, pair.second);
    }

    std::vector<Difference> differences;
    if(!compareResult(list, expected, differences))
    {
        std::cerr << "[FATAL], function: " << __func__ << ", line: " << __LINE__ 
            << " comparison failed\n"; 
        std::cerr << "List    : " << list << "\n";
        std::cerr << "Expected: ";
        for(auto v : expected)
        {
            std::cerr << v << " ";
        }
        std::cerr << "\n\n";

        std::cerr << "Differences: ";
        for(auto d : differences)
        {
            std::cerr << d;
        }
        std::cerr << "\n";
        std::exit(-1);
    }
}



void TestLinkedList::runAllTests()
{
    runInsertHeadTests();
    runInsertTailTests();
    runInsertIndexTests();
}