#include "node.h"
#include "value.h"

#ifndef STACK_H
#define STACK_H

typedef struct stack {
    Node *top;
    int priority;
} Stack;

extern void push(Stack *, Value *);
extern Value *pop(Stack *top);
extern Stack *newStack(void);

#endif
