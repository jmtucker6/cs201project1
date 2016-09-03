#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "value.h"
#include "scanner.h"

int main (void) {

    printf("Enter an equation: ");
    char *s = NULL;
    Queue *queue = newQueue();
    while(!feof(stdin)) {
        s = readToken(stdin);
        if(s != NULL) {
           Value *v = newValueString(s);
           enqueue(queue, v);
        }
    }
    printf("Queue loaded\n");
    while(!isEmpty(queue)) {
        printf("%s\n", dequeue(queue) -> sval);

    }
    return 0;
};
