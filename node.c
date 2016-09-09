#include "node.h"
#include "fatal.h"
#include <stdlib.h>

/*
 * node.c
 *
 * Implementation of node objects
 * Written by Jacob Tucker
 */

/*
 * PUBLIC FUNCTIONS
 */

/*
 * Creates an empty node
 */
Node *newNode(Value *v) {
    Node *node = malloc(sizeof(Node));
    if (node == 0)
        Fatal("Insufficient space for new node\n");
    node -> val = v;
    node -> next = NULL;
    return node;
};
