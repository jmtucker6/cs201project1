#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "stack.h"
#include "queue.h"
#include "value.h"
#include "scanner.h"

static Value *readValue(FILE *);
static void printValue(Value *);

int main (void) {

    printf("Enter an equation: ");
    Queue *inputQueue = newQueue();
    Value *tempValue = NULL;
    while(!feof(stdin)) {
        if ((tempValue = readValue(stdin)) != NULL)
            enqueue(inputQueue, tempValue);
    }
    printf("Queue loaded\n");
    while(!isEmpty(inputQueue)) {
        printValue(dequeue(inputQueue));
    }
    return 0;
};

/*
 * Reads in a value from a file
 *
 * Adapted from example function by John Lusth
 */
static Value *readValue(FILE *fp) {
    Value *v;
    if (stringPending(fp))
        v = newValueString(readToken(fp));
    else {
        char *token = readToken(fp);
        if (token == NULL)
            return NULL;
        if (strchr(token, '.') != 0)
            v = newValueDouble(atof(token));
        else if (*token == '-' || isdigit(*token))
            v = newValueInt(atoi(token));
        else if (isalpha(*token))
            v = newValueVariable(token);
        else if (*token == ';')
            v = newValueSemicolon(token);
        else
            v = newValueOperator(token);
    }
    return v;
};

/*
 * Prints a value objects contents and its type
 *
 * Adapted from example function by John Lusth
 */
static void printValue(Value *value) {
    if (value -> type == INTEGER)
        printf("%d\n", value -> ival);
    else if (value -> type == DOUBLE)
        printf ("%f\n", value -> dval);
    else
        printf("%s\n", value -> sval);
    printf("Type: %d\n", value -> type);
};
