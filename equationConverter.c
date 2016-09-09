#include "equationConverter.h"
#include "queue.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * equationConverter.c
 *
 * Takes an infix queue and returns its equivalent postfix queue
 * Written by Jacob Tucker
 *
 */
Queue *convertToPostfix(Queue *inFixQueue) {
    Stack *stack = NULL;
    stack = newStack();
    Queue *postFixQueue = NULL;
    postFixQueue = newQueue();
    Value *tempValue = NULL;
    while (!isEmptyQueue(inFixQueue)) {
        tempValue = dequeue(inFixQueue);
        if (tempValue -> type == SEMICOLON) {
            while (!isEmptyStack(stack)) {
                enqueue(postFixQueue, pop(stack));
            }
            return postFixQueue;
        } else if (tempValue -> type != OPERATOR) {
            enqueue(postFixQueue, tempValue);
        } else
            if (isEmptyStack(stack) || *(stack -> top -> val -> sval) == '(') {
                push(stack, tempValue);
            } 
        /* Checks if operator on top of the stack has a higher precedence */
            else if (stack -> top -> val -> ival >= tempValue -> ival) {
                enqueue(postFixQueue, pop(stack));
                push(stack, tempValue);
            } else if (*(tempValue -> sval) == ')') {
                while (*(stack -> top -> val -> sval) != '(')
                    enqueue(postFixQueue, pop(stack));
                pop(stack);
            } else {
                push(stack, tempValue);
            }
    }
    /* Appends the remainder of the stack to the postfix queue */
    while (!isEmptyStack(stack))
        enqueue(postFixQueue, pop(stack));
    return postFixQueue;
};
