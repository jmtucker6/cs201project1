#include <stdlib.h>
#include "stack.h"

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
    s -> top = NULL;
    s -> priority = 0;
    return s;
};

/*
 * PRIVATE FUNCTIONS
 */

