#include "node.h"
#include "value.h"

#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue {
    Node *first;
    Node *last;
} Queue;

extern void enqueue(Queue *, Value *);
extern Value *dequeue(Queue *);
extern Queue *newQueue(void);

#endif
