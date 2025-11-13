#pragma once 

#include <utility>              // std::pair
#include <vector>
#include "myLinkedList.h"
#include "randomGenerator.hpp"

struct Difference{
    int listVal;
    int expectedVal;
    size_t index;

    friend std::ostream& operator << (std::ostream& os, const Difference& diff);
};

class TestLinkedList
{
    static constexpr int MIN_ARRAY_SIZE = 1;
    static constexpr int MAX_ARRAY_SIZE = 1000;

    static constexpr int NUM_TESTS = 10;

    static constexpr int MIN_LIST_VALUE = -9999;
    static constexpr int MAX_LIST_VALUE = +9999;

    static constexpr int MIN_INSERTIONS = 1;
    static constexpr int MAX_INSERTIONS = 100;

    public:

    void runAllTests();
    void runInsertHeadTests(int numTests = NUM_TESTS);
    void runInsertTailTests(int numTests = NUM_TESTS);
    void runInsertIndexTests(int numTests = NUM_TESTS);
    void runGetTests(int numTests = NUM_TESTS);


    private:

    RandomNumberGenerator m_rg;

    bool compareResult(const MyLinkedList& list, const std::vector<int>& expected, std::vector<Difference>& diff);

    void fillRandom(std::vector<int>& testVals, int min = MIN_LIST_VALUE, int max = MAX_LIST_VALUE);

    // Creates array of valid index locations for insertion 
    // Values to be inserted are random
    void generateValidInsertionPairs(std::vector<std::pair<int,int>>& pairs, int numPairs, int maxIndex);

    // appends values from start to stop (inclusive), increments by step 
    // to end of array 
    void appendVals(std::vector<int>& array, int start, int stop, int step);
   

    void testInsertHead(const std::vector<int>& testVals, const std::vector<int>& expected);
    void testInsertTail(const std::vector<int>& testVals, const std::vector<int>& expected);
    void testInsertAtIndex(const std::vector<int>& buildVals, const std::vector<int>& expected,
                            const std::vector<std::pair<int,int>>& insertVals);
    
    void testGet(const std::vector<int>& listVals, const std::vector<int>& expected, const std::vector<int>& testIndices);

};






