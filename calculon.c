#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "queue.h"
#include "value.h"
#include "scanner.h"
#include "bst.h"
#include "fatal.h"
#include "equationConverter.h"
#include "processEquation.h"

/*
 * calculon.c
 *
 * Main driver for calculon
 * Takes input from terminal or file
 * Outputs results to terminal
 *
 * -d prints the postfix of the last expression
 * -v prints the author
 *
 *  Written by Jacob Tucker
 */

static Value *readValue(FILE *);
static void printValue(Value *, TreeNode *);
static bool commandLineHasFilename(int, char**);
static char *getFileName(int, char**);
int ProcessOptions(int, char**);

bool dFlag = false;
int main (int argc, char** argv) {
    Value *result = NULL;
    Queue *postFix = NULL;
    Queue *tempQueue = NULL;
    TreeNode *root = NULL;
    root = insertTreeNode(root, newValueVariable(""), NULL); // empty root
    ProcessOptions(argc, argv);
    FILE *fp = NULL;
    if (commandLineHasFilename(argc, argv))
        fp = fopen(getFileName(argc, argv), "r");
    else {
        fp = stdin;
    }
    Queue *inputQueue = newQueue();
    Value *tempValue = NULL;
    while(!feof(fp)) {
        if ((tempValue = readValue(fp)) != NULL) {
            enqueue(inputQueue, tempValue);
            if (tempValue -> type == SEMICOLON) {
                postFix = convertToPostfix(inputQueue);
                tempQueue = duplicateQueue(postFix); //queue is consumed when processed
                result = processEquation(postFix, root);
            }
        }
    }
    if (dFlag == true) {
        while(!isEmptyQueue(tempQueue)) {
            printValue(dequeue(tempQueue), root);
        }
    } else {
        printValue(result, root);
    }
    printf("\n");
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
        v = newValueString(readString(fp));
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
static void printValue(Value *value, TreeNode *root) {
    if (value -> type == VARIABLE && dFlag == false)
        value = findValue(root, value);
    if (value -> type == INTEGER)
        printf("%d ", value -> ival);
    else if (value -> type == DOUBLE)
        printf ("%f ", value -> dval);
    else if (value -> type == STRING)
        printf("\"%s\" ", value -> sval);
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
                exit(0);
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
