#include "node.h"
#include "value.h"
#include <stdbool.h>

#ifndef STACK_H
#define STACK_H

typedef struct stack {
    Node *top;
} Stack;

extern void push(Stack *, Value *);
extern Value *pop(Stack *);
extern bool isEmptyStack(Stack *);
extern Stack *newStack(void);

#endif
