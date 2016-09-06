#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "stack.h"
#include "queue.h"
#include "value.h"
#include "scanner.h"
#include "fatal.h"
#include "equationConverter.h"

static Value *processExpression(Queue *);
static Value *readValue(FILE *);
static void printValue(Value *);
static bool commandLineHasFilename(int, char**);
static char *getFileName(int, char**);
int ProcessOptions(int, char**);

bool dFlag = false;
int main (int argc, char** argv) {
    Value *result = NULL;
    Queue *postFix = NULL;
    ProcessOptions(argc, argv);
    FILE *fp = NULL;
    if (commandLineHasFilename(argc, argv))
        fp = fopen(getFileName(argc, argv), "r");
    else {
        fp = stdin;
        printf("Enter an equation: ");
    }
    Queue *inputQueue = newQueue();
    Value *tempValue = NULL;
    while(!feof(fp)) {
        if ((tempValue = readValue(fp)) != NULL) {
            enqueue(inputQueue, tempValue);
            if (tempValue -> type == SEMICOLON) {
                postFix = convertToPostfix(inputQueue);
                result = processExpression(postFix);
            }
        }
    }
    while(!isEmptyQueue(postFix)) {
        printValue(dequeue(postFix));
    }
    printf("\n%d\n", result -> ival);
    return 0;
};

/*
 * Processes a postfix expression
 */
static Value *processExpression(Queue *q) {
    return q -> head -> val;
}

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
        else if ((*token == '-' && strlen(token) > 1)|| isdigit(*token))
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
        printf("%d ", value -> ival);
    else if (value -> type == DOUBLE)
        printf ("%f ", value -> dval);
    else
        printf("%s ", value -> sval);
};

/*
 * Checks if input is from file
 */
static bool commandLineHasFilename(int argc, char **argv) {
    if (argc == 1)
        return false;
    int argIndex = 1;
    while (argIndex < argc) {
        if (argv[argIndex][0] != '-')
            return true;
        argIndex++;
    }
    return false;

};

/*
 * Returns the filename from the commandline
 */
static char *getFileName(int argc, char **argv) {
    int argIndex = 1;
    while (argIndex < argc) {
        if (argv[argIndex][0] != '-')
            return argv[argIndex];
        argIndex++;
    }
    Fatal("No filename found");
    return NULL;
};

/*
 * Option Function taken from options.c
 *
 * only -oXXX or -o XXX options
 */
int
ProcessOptions(int argc, char **argv)
{
    int argIndex;
    int argUsed;
    int separateArg;

    argIndex = 1;

    while (argIndex < argc && *argv[argIndex] == '-')
        {
        /* check if stdin, represented by "-" is an argument */
        /* if so, the end of options has been reached */
        if (argv[argIndex][1] == '\0') return argIndex;

        separateArg = 0;
        argUsed = 0;

        if (argv[argIndex][2] == '\0')
            separateArg = 1;

        switch (argv[argIndex][1])
            {
            /*
             * when option has an argument, do this
             *
             *     examples are -m4096 or -m 4096
             *
             *     case 'm':
             *         MemorySize = atol(arg);
             *         argUsed = 1;
             *         break;
             *
             *
             * when option does not have an argument, do this
             *
             *     example is -a
             *
             *     case 'a':
             *         PrintActions = 1;
             *         break;
             */

            case 'v':
                printf("Jacob Tucker\n");
                exit(1);
                break;
            case 'd':
                dFlag = true;
                break;
            default:
                Fatal("option %s not understood\n",argv[argIndex]);
            }

        if (separateArg && argUsed)
            ++argIndex;

        ++argIndex;
        }

    return argIndex;
}
