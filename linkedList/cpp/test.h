#pragma once 

#include "myLinkedList.h"


bool compareResult(const int* expected, int n, const MyLinkedList& list);
void testInsertHead();
void testInsertTail();
void testInsertAtIndex();
void runTests();