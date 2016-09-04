#include "equationConverter.h"
#include "queue.h"
#include "stack.h"
#include <stdlib.h>

Queue *convertToPostfix(Queue *inFixQueue) {
    Stack *stack = NULL;
    stack = newStack();
    Queue *postFixQueue = NULL;
    postFixQueue = newQueue();
    Value *tempValue = NULL;
    while (!isEmptyQueue(inFixQueue)) {
        tempValue = dequeue(inFixQueue);
        if (tempValue -> type == SEMICOLON)
            return postFixQueue;
        else if (tempValue -> type != OPERATOR) 
            enqueue(postFixQueue, tempValue);
        else
            if (isEmptyStack(stack) || *(stack -> top -> val -> sval) == '(')
                push(stack, tempValue);
            else if (stack -> top -> val -> ival > tempValue -> ival) {
                enqueue(postFixQueue, pop(stack));
                push(stack, tempValue);
            }
            else
                push(stack, tempValue);
    }
    while (!isEmptyStack(stack))
        enqueue(postFixQueue, pop(stack));
    return postFixQueue;
};
