#include "node.h"
#include "value.h"
#include <stdbool.h>

#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;

extern void enqueue(Queue *, Value *);
extern Value *dequeue(Queue *);
extern Queue *newQueue(void);
extern bool isEmpty(Queue *);

#endif
