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

    {   // all insertions should be valid 
        // initial list 1, 3, 5, 7, 9, 11
        std::vector<int> buildVals;
        appendVals(buildVals, 1, 11, 2);

        // create pairs array <insert index, val to insert>
        // test values <0,0> <2,2> <4,4> <6,6> <8,8> <10,10>
        std::vector<std::pair<int,int>> insertPairs;
        for(int i = 0; i < 6; i++)
        {
            std::pair<int,int> pair = {2*i, 2*i};
            insertPairs.push_back(pair);
        }

        // expected list after insertions
        // 0 1 2 3 4 5 6 7 8 9 10
        std::vector<int> expectedVals;
        appendVals(expectedVals, 0, 11, 1);

        testInsertAtIndex(buildVals, expectedVals, insertPairs);        
    }

    {   // test insertion at negative index 
        std::vector<int> buildVals;
        appendVals(buildVals, 0,5,1);
        std::vector<int> expectedVals(buildVals);
        std::vector<std::pair<int,int>> insertPairs;
        std::pair<int,int> pair = {-1, -1};
        insertPairs.push_back(pair);
        testInsertAtIndex(buildVals, expectedVals, insertPairs);
    }

    {   // test insertion at index value equal to list length
        // should add at tail
        std::vector<int> buildVals;
        appendVals(buildVals, 0,5,1);
        std::vector<int> expectedVals;
        appendVals(expectedVals, 0, 6, 1);

        std::vector<std::pair<int,int>> insertPairs;
        std::pair<int,int> pair = {6, 6};
        insertPairs.push_back(pair);
        
        testInsertAtIndex(buildVals, expectedVals, insertPairs);
    }

    {   // test insertion at index value greater than list length
        // should not insert 
        std::vector<int> buildVals;
        appendVals(buildVals, 0,5,1);
        std::vector<int> expectedVals(buildVals);
       
        std::vector<std::pair<int,int>> insertPairs;
        std::pair<int,int> pair = {7, 6};
        insertPairs.push_back(pair);
        
        testInsertAtIndex(buildVals, expectedVals, insertPairs);
    }

    {   // test insertions at random valid index locations 
        for(int t = 0; t < numTests; t++)
        {
            // create array of random values for initial list 
            std::vector<int> buildVals;
            fillRandom(buildVals);

            std::vector<std::pair<int,int>> insertPairs;
            int numPairs = m_rg.generate(MIN_INSERTIONS, MAX_INSERTIONS);
            generateValidInsertionPairs(insertPairs, numPairs, static_cast<int>(buildVals.size()));

            std::vector<int> expectedVals(buildVals);
            for(auto pair : insertPairs)
            {
                std::vector<int>::iterator position = expectedVals.begin() + pair.first;
                expectedVals.insert(position, pair.second);
            }

            testInsertAtIndex(buildVals, expectedVals, insertPairs);
        }
    }
}

void TestLinkedList::runGetTests(int numTests)
{
    {
        // test empty list 
        std::vector<int> buildVals;
        std::vector<int> expectedVals;
        std::vector<int> testIndices = {0, 1};
    }

    {
        // test all indices of sequential list 
        std::vector<int> buildVals;    
        appendVals(buildVals, 0,10,1);

        // test list will be in reverse order of build vals
        std::vector<int> expected(buildVals);
        std::reverse(buildVals.begin(), buildVals.end());

        // yes, this is repetitive
        std::vector<int> testIndices(buildVals);

        testGet(buildVals, expected, testIndices);
    }

    {
        // test invalid indices 
        std::vector<int> buildVals;
        appendVals(buildVals, 0,10,1);
        
        // test list will be in reverse order of build vals
        std::vector<int> expected(buildVals);
        std::reverse(buildVals.begin(), buildVals.end());

        std::vector<int> testIndices = {-1, static_cast<int>(buildVals.size()), 
                static_cast<int>(buildVals.size()+1)};

        testGet(buildVals, expected, testIndices);
    }

    {
        // random testing 
        for(int i = 0; i < numTests; i++)
        {
            int n = m_rg.generate(MIN_ARRAY_SIZE, MAX_ARRAY_SIZE);
            std::vector<int> buildVals(n);
            fillRandom(buildVals);

            std::vector<int> expected(buildVals);
            std::reverse(expected.begin(), expected.end());

            std::vector<int> testIndices(2*n);
            fillRandom(testIndices, -2*n, 3*n);

            testGet(buildVals, expected, testIndices);
        }
    }
}

 void TestLinkedList::fillRandom(std::vector<int>& testVals, int min, int max)
 {
    size_t n = testVals.size();
    for(size_t i = 0; i < n; i++)
    {
        testVals[i] = m_rg.generate(min, max);
    }
 }

 void TestLinkedList::generateValidInsertionPairs(std::vector<std::pair<int,int>>& pairs, int numPairs, int maxIndex)
 {
    for(int i = 0; i < numPairs; i++)
    {
        int index = m_rg.generate(0, maxIndex);
        int val = m_rg.generate(MIN_LIST_VALUE, MAX_LIST_VALUE);
        std::pair<int,int> pair = {index, val};
        pairs.push_back(pair);

        // increment the max index value as list will grow in size by 1
        maxIndex++;
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

void TestLinkedList::testGet(const std::vector<int>& listVals, const std::vector<int>& expected, const std::vector<int>& testIndices)
{
    // Build list from listVals 
    MyLinkedList list;
    for(size_t i = 0; i < listVals.size(); i++)
    {
        list.insertAtHead(listVals[i]);
    }

    // Verify list matches expected
    std::vector<Difference> differences;
    if(!compareResult(list, expected, differences))
    {
        std::cerr << "[FATAL], function: " << __func__ << ", line: " << __LINE__ 
                << "list does not match expected\nDifferences\n";
        for(const auto& d : differences)
        {
            std::cerr << d;
        }
        std::cerr << "\n";
        std::exit(-1);
    }

    int listLength = static_cast<int>(expected.size());
    for(auto index : testIndices)
    {
        const Node* node = list.get(index);
        if(index >= 0 && index < listLength)
        {
            if(node->data != expected[index])
            {
                std::cerr << "[ERROR], function: " << __func__ << ", line: " << __LINE__ 
                        << ", list length: " << listLength << ", test index: " << index 
                        << ", node->data: " << node->data << " != expected[index]: " 
                        << expected[index] << "\n";
            }
        }
        else
        {
            if(node != nullptr)
            {
                std::cerr << "[ERROR], function: " << __func__ << ", line: " << __LINE__ 
                        << ", list length: " << listLength << ", test index: " << index 
                        << ", expected null ptr, but node address is " << node << "\n";
            }
        }
    }
}

void TestLinkedList::runAllTests()
{
    runInsertHeadTests();
    runInsertTailTests();
    runInsertIndexTests();
    runGetTests();
}