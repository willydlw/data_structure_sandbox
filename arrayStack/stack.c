#include "stack.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void log_error_message(FILE* out, const char* msg, const char* file, const char* function, int line)
{
    fprintf(out, "%s, %s %s %d\n", msg, file, function, line);
}

Stack* createStack(unsigned capacity)
{
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    if(stack == NULL)
    {
        log_error_message(stderr, "Error: malloc failure", __FILE__, __FUNCTION__, __LINE__);
        
        // Using goto with caution to streamline the two instances within this function
        // where malloc may fail.
        goto memfail;
    }

    stack->data = (int*)malloc(capacity * sizeof(int));
    if(stack->data == NULL)
    {
        log_error_message(stderr, "Error: malloc failure", __FILE__, __FUNCTION__, __LINE__);
        goto memfail;
    }

    stack->capacity = capacity;
    stack->top = -1;
    return stack;

memfail:
    stack->capacity = 0;
    stack->top = -1;
    if(stack->data)
    {
        free(stack->data);
        stack->data = NULL;
    }
    if(stack)
    {
        free(stack);
    }
    return NULL;
}


void deleteStack(Stack* stack)
{
    if(stack->data)
    {
        free (stack->data);
        stack->data = NULL;
    }

    if(stack)
    {
        free(stack);
        stack = NULL;
    }

    stack->capacity = 0;
    stack->top = -1;
}

bool isFull(const Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

bool isEmtpy(const Stack* stack)
{
    return stack->top == -1;
}


void push(Stack* stack, int value)
{
    if(isFull(stack))
    {
        return;
    }

    /* top points to the current top of the stack. Increment it to
       point the the next array element and then store the data
       in the array.
    */
    stack->top += 1;
    stack->data[stack->top] = value; 
}

int pop(Stack* stack)
{
    int val;

    if(isEmtpy(stack))
    {
        val = INT_MIN;
    }
    else
    {
        val = stack->data[stack->top];
        stack->top -= 1;
    }

    return val;
}

int peek(const Stack* stack)
{
    if(isEmpty(stack))
    {
        return INT_MIN;
    }
    else
    {
        return stack->data[stack->top];
    }
}
