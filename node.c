#include "node.h"
#include "fatal.h"
#include <stdlib.h>

/*
 * PUBLIC FUNDTIONS
 */

Node *newNode(Value *v) {
    Node *node = malloc(sizeof(Node));
    if (node == 0)
        Fatal("Insufficient space for new node\n");
    node -> val = v;
    node -> next = NULL;
    return node;
};
