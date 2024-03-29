#include <stdlib.h>
#include "stack.h"
#include "fatal.h"

/*
 * stack.c
 *
 * Implementation of stack objects
 * Written by Jacob Tucker
 */

/*
 * PUBLIC FUNCTIONS
 */

/*
 * Push onto front of stack
 */
void push(Stack *s, Value *v) {
    Node *stackTop = s -> top;
    Node *node = newNode(v);
    node -> next = stackTop == NULL ? NULL : stackTop;
    s -> top = node;
};

/*
 * Pop from front of stack
 */
Value *pop(Stack *s) {
    if (isEmptyStack(s))
        Fatal("Cannot pop from an empty stack");
    Value *v = s -> top -> val;
    Node *temp = s -> top;
    s -> top = s -> top -> next;
    free(temp);
    return v;
};

/*
 * Creates a new stack
 */
Stack *newStack(void) {
    Stack *s = malloc(sizeof(Stack));
    if (s == NULL)
        Fatal("Out of Memory\n");
    s -> top = NULL;
    return s;
};

/*
 * Returns if the stack is empty
 */
bool isEmptyStack(Stack *s) {
    return (s -> top == NULL) ? true : false;
};

