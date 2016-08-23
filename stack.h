#include "value.h"

typedef struct Stack {
    struct Stack *below;
    char oper;
    int priority;
} Stack;

extern void push(char);
extern char pop();
