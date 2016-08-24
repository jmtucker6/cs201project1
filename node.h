#include "value.h"

#ifndef NODE_H
#define NODE_H

typedef struct Node {
    Value *val;
    struct Node *next;
} Node;

extern Node *newNode(Value *);

#endif
