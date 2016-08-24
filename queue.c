#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "fatal.h"

static bool isEmpty(Queue *);

/*
 * PUBLIC FUNCTIONS
 */

void enqueue(Queue *q, Value *v) {
    Node *node = newNode(v);
    if (q -> first == NULL)
        q -> first = node;
    if (q -> last != NULL)
        q -> last -> next = node;
    q -> last = node;    
};

Value *dequeue(Queue *q) {
    if (isEmpty(q))
        Fatal("Cannot dequeue from empty queue");
    Value *v = q -> first -> val;
    Node *temp = q -> first;
    if (q -> first != q -> last)
        q -> first = q -> first -> next;
    else {
        q -> first = NULL;
        q -> last = NULL;
    }
    free(temp);
    return v;
};

Queue *newQueue(void) {
    Queue *q = malloc(sizeof(Queue));
    q -> first = NULL;
    q -> last = NULL;
    return q;
};

/*
 * PRIVATE FUNCTIONS
 */

static bool isEmpty(Queue *q) {
    return (q -> first == NULL && q -> last == NULL) ? true : false;
};
