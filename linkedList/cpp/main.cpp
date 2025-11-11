#include "testLinkedList.h"

// g++ -Wall -Wextra -pedantic -g main.cpp testLinkedList.cpp myLinkedList.cpp randomGenerator.hpp
// valgrind --leak-check=yes --log-file=valgrind.rpt ./a.out
// valgrind -s ./a.out


int main()
{
    TestLinkedList test;
    test.runInsertHeadTests();
    return 0;
}
