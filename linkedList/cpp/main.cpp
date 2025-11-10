#include "test.h"

// g++ -Wall -Wextra -pedantic -g main.cpp test.cppp myLinkedList.cpp
// valgrind --leak-check=yes --log-file=valgrind.rpt ./a.out
// valgrind -s ./a.out


int main()
{
    runTests();
    return 0;
}
