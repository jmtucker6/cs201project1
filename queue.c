#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "fatal.h"

/*
 * queue.c
 *
 * Implements queue objects
 * Written by Jacob Tucker
 */

/*
 * PUBLIC FUNCTIONS
 */

/*
 * Enqueues onto back (tail) of linked list
 */
void enqueue(Queue *q, Value *v) {
    Node *node = newNode(v);
    if (q -> head == NULL)
        q -> head = node;
    if (q -> tail != NULL)
        q -> tail -> next = node;
    q -> tail = node;    
};

/*
 * Dequeues from front (head) of linked list
 */
Value *dequeue(Queue *q) {
    if (isEmptyQueue(q))
        Fatal("Cannot dequeue from empty queue\n");
    Value *v = q -> head -> val;
    Node *temp = q -> head;
    if (q -> head != q -> tail)
        q -> head = q -> head -> next;
    else {
        q -> head = NULL;
        q -> tail = NULL;
    }
    free(temp);
    return v;
};

/*
 * Duplicates a queue
 */
Queue *duplicateQueue(Queue *q) {
    Queue *newQ = NULL;
    newQ = newQueue();
    Node *node = q -> head;
    while (node != NULL) {
        enqueue(newQ, node -> val);
        node = node -> next;
    }
    return newQ;
};

/*
 * Returns an empty queue
 */
Queue *newQueue(void) {
    Queue *q = malloc(sizeof(Queue));
    if (q == 0)
        Fatal("Insufficient space for new queue\n");
    q -> head = NULL;
    q -> tail = NULL;
    return q;
};


/*
 * Checks if queue is empty
 */
bool isEmptyQueue(Queue *q) {
    return (q -> head == NULL && q -> tail == NULL) ? true : false;
};

