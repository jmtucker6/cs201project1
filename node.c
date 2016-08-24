#include "node.h"
#include <stdlib.h>

/*
 * PUBLIC FUNDTIONS
 */

Node *newNode(Value *v) {
    Node *node = malloc(sizeof(Node));
    node -> val = v;
    node -> next = NULL;
    return node;
};
