#pragma once 

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

    public:

    //void runAllTests();
    void runInsertHeadTests();
    //void runInsertTailTests();


    private:

    RandomNumberGenerator m_rg;

    bool compareResult(const MyLinkedList& list, const std::vector<int>& expected, std::vector<Difference>& diff);

    void fillRandom(std::vector<int>& testVals);

    void testInsertHead(const std::vector<int>& testVals, const std::vector<int>& expected);
    //void testInsertTail();
    //void testInsertAtIndex();

};






