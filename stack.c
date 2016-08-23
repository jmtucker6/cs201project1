#include <stdlib.h>
#include "stack.h"

Stack *top = NULL;

/*
 * PUBLIC FUNCTIONS
 */

void push(char c) {
    Stack *s = malloc(sizeof(Stack));
    s -> oper = c;
    if (top == NULL)
        s -> below = NULL;
    else 
        s -> below = top;
    top = s;
};

char pop() {
    char c = top -> oper;
    Stack *temp = top;
    top = top -> below;
    free(temp);
    return c;
};

/*
 * PRIVATE FUNCTIONS
 */

void create() {
    top = NULL;
};
