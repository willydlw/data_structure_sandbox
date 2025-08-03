#ifndef STACK_ARRAY_H_INCLUDED
#define STACK_ARRAY_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>


typedef struct Stack {
    int top;
    int capacity;
    int* data;
} Stack;

/* Allocates memory for data.
*/
Stack* createStack(unsigned capacity);

/* Frees memory allocated for stack->data and stack.
   Sets capacity to zero and top to -1.
*/
void deleteStack(Stack* stack);

/*
    Returns true when stack data is at full capacity.
    Otherwise, returns false.
*/
bool isFull(const Stack* stack);

/*  Returns true when stack is empty.
    Otherwise, returns false
*/
bool isEmtpy(const Stack* stack);


void push(Stack* stack, int value);

/* If the stack is not empty, returns the data stored
   at the top of the stack. 
   If the stack is empty, returns INT_MIN.
*/
int pop(Stack* stack);

int peek(const Stack* stack);


inline void log_error_message(FILE* out, const char* msg, const char* file, const char* function, int line);

#endif 