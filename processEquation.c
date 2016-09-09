#include "processEquation.h"
#include "stack.h"
#include "bst.h"
#include "fatal.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/* processEquation.c
 *
 * Reduces a postfix queue to a single equivalent value
 *
 * Helper functions are self explanatory
 * Written by Jacob Tucker
 *
 */

static Value *add(Value *, Value *);
static Value *sub(Value *, Value *);
static Value *mult(Value *, Value *);
static Value *divide(Value *, Value *);
static Value *mod(Value *, Value *);
static Value *power(Value *, Value *);
static Value *equals(Value *, Value *);
static Value *addIntInt(Value *, Value *);
static Value *addIntDouble(Value *, Value *);
static Value *addStringString(Value *, Value *);
static Value *addStringInt(Value *, Value *);
static Value *addStringDouble(Value *, Value *);
static Value *addDoubleDouble(Value *, Value *);
static Value *subIntInt(Value *, Value *);
static Value *subIntDouble(Value *, Value *);
static Value *subDoubleInt(Value *, Value *);
static Value *subStringInt(Value *, Value *);
static Value *subIntString(Value *, Value *);
static Value *subStringDouble(Value *, Value *);
static Value *subDoubleString(Value *, Value *);
static Value *subDoubleDouble(Value *, Value *);
static Value *multIntInt(Value *, Value *);
static Value *multIntDouble(Value *, Value *);
static Value *multStringInt(Value *, Value *);
static Value *multStringDouble(Value *, Value *);
static Value *multDoubleDouble(Value *, Value *);
static Value *divIntInt(Value *, Value *);
static Value *divIntDouble(Value *, Value *);
static Value *divDoubleInt(Value *, Value *);
static Value *divStringInt(Value *, Value *);
static Value *divIntString(Value *, Value *);
static Value *divStringDouble(Value *, Value *);
static Value *divDoubleString(Value *, Value *);
static Value *divDoubleDouble(Value *, Value *);
static Value *modIntInt(Value *, Value *);
static Value *modIntString(Value *, Value *);
static Value *modStringInt(Value *, Value *);
static Value *powIntInt(Value *, Value *);
static Value *powIntDouble(Value *, Value *);
static Value *powDoubleInt(Value *, Value *);
static Value *powDoubleDouble(Value *, Value *);
static Value *powStringInt(Value *, Value *);
static Value *powIntString(Value *, Value *);
static Value *powStringDouble(Value *, Value *);
static Value *powDoubleString(Value *, Value *);
static char *concat(char *, char *);
static Value *isInitialized(Value *);

TreeNode *root = NULL;

/*
 * Reduces a queue of values down to one value by applying its operators
 */
Value *processEquation(Queue *postFixQueue, TreeNode *treeRoot) {
    root = treeRoot;
    Value *v = NULL;
    Value *val1 = NULL;
    Value *val2 = NULL;
    Stack *stack = newStack();
    while(!isEmptyQueue(postFixQueue)) {
        v = dequeue(postFixQueue);
        if (v -> type == OPERATOR) {
            val2 = pop(stack);
            val1 = pop(stack);
            if (*(v -> sval) == '+')
                push(stack, add(val1, val2));
            else if (*(v -> sval) == '-')
                push(stack, sub(val1, val2));
            else if(*(v -> sval) == '*')
                push(stack, mult(val1, val2));
            else if(*(v -> sval) == '/')
                push(stack, divide(val1, val2));
            else if(*(v -> sval) == '%')
                push(stack, mod(val1, val2));
            else if(*(v -> sval) == '^')
                push(stack, power(val1, val2));
            else if(*(v -> sval) == '=')
                push(stack, equals(val1, val2));
            else
                Fatal("Operator %s is not implemented.\n", v ->sval);
        } else {
            push(stack, v);
        };
    };
    return pop(stack);
};

/*
 * PRIVATE FUNCTIONS
 */

/*
 * Calls additionhelper function for every combination 
 * of INTEGER, DOUBLE, and STRING
 */
static Value *add(Value *val1, Value *val2) {
    if (val1 -> type == VARIABLE) {
        val1 = isInitialized(val1);
    }
    if (val2 -> type == VARIABLE) {
        val2 = isInitialized(val2);
    }
    if (val1 -> type == INTEGER) {
        if (val2 -> type == INTEGER)
            return addIntInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            return addIntDouble(val1, val2);
        else
            return addStringInt(val2, val1);
    } else if (val1 -> type == DOUBLE) {
        if (val2 -> type == INTEGER)
            return addIntDouble(val2, val1);
        else if (val2 -> type == DOUBLE)
            return addDoubleDouble(val1, val2);
        else
            return addStringDouble(val2, val1);
    } else {
        if (val2 -> type == INTEGER)
            return addStringInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            return addStringDouble(val1, val2);
        else
            return addStringString(val1, val2);
    };
};

/*
 * Calls subtraction helper function for every combination 
 * of INTEGER, DOUBLE, and STRING
 */
static Value *sub(Value *val1, Value *val2) {
    if (val1 -> type == VARIABLE) {
        val1 = isInitialized(val1);
    }
    if (val2 -> type == VARIABLE) {
        val2 = isInitialized(val2);
    }
    if (val1 -> type == INTEGER) {
        if (val2 -> type == INTEGER)
            return subIntInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            return subIntDouble(val1, val2);
        else
            return subIntString(val1, val2);
    } else if (val1 -> type == DOUBLE) {
        if (val2 -> type == INTEGER)
            return subDoubleInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            return subDoubleDouble(val1, val2);
        else
            return subDoubleString(val1, val2);
    } else {
        if (val2 -> type == INTEGER)
            return subStringInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            return subStringDouble(val1, val2);
        else
            Fatal("Cannot subtract strings\n");
    };
    return NULL;
};

/*
 * Calls multiply helper function for every combination 
 * of INTEGER, DOUBLE, and STRING
 */
static Value *mult(Value *val1, Value *val2) {;
    if (val1 -> type == VARIABLE) {
        val1 = isInitialized(val1);
    }
    if (val2 -> type == VARIABLE) {
        val2 = isInitialized(val2);
    }
    if (val1 -> type == INTEGER) {
        if (val2 -> type == INTEGER)
            return multIntInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            return multIntDouble(val1, val2);
        else
            return multStringInt(val2, val1);
    } else if (val1 -> type == DOUBLE) {
        if (val2 -> type == INTEGER)
            return multIntDouble(val2, val1);
        else if (val2 -> type == DOUBLE)
            return multDoubleDouble(val1, val2);
        else
            return multStringDouble(val2, val1);
    } else {
        if (val2 -> type == INTEGER)
            return multStringInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            return multStringDouble(val1, val2);
        else
            Fatal("Cannot multiply strings\n");
    };
    return NULL;
};

/*
 * Calls divide helper function for every combination 
 * of INTEGER, DOUBLE, and STRING
 */
static Value *divide(Value *val1, Value *val2) {
    if (val1 -> type == VARIABLE) {
        val1 = isInitialized(val1);
    }
    if (val2 -> type == VARIABLE) {
        val2 = isInitialized(val2);
    }
    if (val1 -> type == INTEGER) {
        if (val2 -> type == INTEGER)
            return divIntInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            return divIntDouble(val1, val2);
        else
            return divIntString(val1, val2);
    } else if (val1 -> type == DOUBLE) {
        if (val2 -> type == INTEGER)
            return divDoubleInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            return divDoubleDouble(val1, val2);
        else
            return divDoubleString(val1, val2);
    } else {
        if (val2 -> type == INTEGER)
            return divStringInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            return divStringDouble(val1, val2);
        else
            Fatal("Cannot divide strings\n");
    };
    return NULL;
};

/*
 * Calls mod helper function for every combination 
 * of INTEGER, DOUBLE, and STRING
 */
static Value *mod(Value *val1, Value *val2) {
    if (val1 -> type == VARIABLE) {
        val1 = isInitialized(val1);
    }
    if (val2 -> type == VARIABLE) {
        val2 = isInitialized(val2);
    }
    if (val1 -> type == INTEGER) {
        if (val2 -> type == INTEGER)
            return modIntInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            Fatal("Cannot mod by double\n");
        else
            return modIntString(val1, val2);
    } else if (val1 -> type == DOUBLE) {
        if (val2 -> type == INTEGER)
            Fatal("Cannot mod a double\n");
        else if (val2 -> type == DOUBLE)
            Fatal("Cannot mod a double by a double\n");
        else
            Fatal("Cannot mod a double\n");
    } else {
        if (val2 -> type == INTEGER)
            return modStringInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            Fatal("Cannot mod by double\n");
        else
            Fatal("Cannot mod strings\n");
    };
    return NULL;
};

/*
 * Calls power helper function for every combination 
 * of INTEGER, DOUBLE, and STRING
 */
static Value *power(Value *val1, Value *val2) {
    if (val1 -> type == VARIABLE) {
        val1 = isInitialized(val1);
    }
    if (val2 -> type == VARIABLE) {
        val2 = isInitialized(val2);
    }
    if (val1 -> type == INTEGER) {
        if (val2 -> type == INTEGER)
            return powIntInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            return powIntDouble(val1, val2);
        else
            return powIntString(val1, val2);
    } else if (val1 -> type == DOUBLE) {
        if (val2 -> type == INTEGER)
            return powDoubleInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            return powDoubleDouble(val1, val2);
        else
            return powDoubleString(val1, val2);
    } else {
        if (val2 -> type == INTEGER)
            return powStringInt(val1, val2);
        else if (val2 -> type == DOUBLE)
            return powStringDouble(val1, val2);
        else
            Fatal("Cannot exponent strings\n");
    };
    return NULL;
};

/*
 * Handles variable assignment
 */
static Value *equals(Value *var, Value *val2) {
    if (val2 -> type == VARIABLE) {
        val2 = isInitialized(val2);
    }
    root = changeNodeData(root, var, val2);
    return val2;
};

/*
 * Helper Functions
 */
static Value *addIntInt(Value *val1, Value *val2) {
    return newValueInt(val1 -> ival + val2 -> ival);
};
static Value *addIntDouble(Value *val1, Value *val2) {
    return newValueDouble(val1 -> ival + val2 -> dval);
};
static Value *addStringString(Value *val1, Value *val2) {
    return newValueString(concat(val1 -> sval, val2 -> sval));
};
static Value *addStringInt(Value *val1, Value *val2) {
    return newValueInt(atoi(val1 -> sval) + val2 -> ival);
};
static Value *addStringDouble(Value *val1, Value *val2) {
    return newValueDouble(atof(val1 -> sval) + val2 -> dval);
};
static Value *addDoubleDouble(Value *val1, Value *val2) {
    return newValueDouble(val1 -> dval + val2 -> dval);
};
static Value *subIntInt(Value *val1, Value *val2) {
    return newValueInt(val1 -> ival - val2 -> ival);
};
static Value *subIntDouble(Value *val1, Value *val2) {
    return newValueDouble(val1 -> ival - val2 -> dval);
};
static Value *subDoubleInt(Value *val1, Value *val2) {
    return newValueDouble(val1 -> dval - val2 -> ival);
};
static Value *subStringInt(Value *val1, Value *val2) {
    return newValueInt(atoi(val1 -> sval) - val2 -> ival);
};
static Value *subIntString(Value *val1, Value *val2) {
    return newValueInt(val1 -> ival - atoi(val2 -> sval));
};
static Value *subStringDouble(Value *val1, Value *val2) {
    return newValueDouble(atof(val1 -> sval) - val2 -> dval);
};
static Value *subDoubleString(Value *val1, Value *val2) {
    return newValueDouble(val1 -> dval - atof(val2 -> sval));
};
static Value *subDoubleDouble(Value *val1, Value *val2) {
    return newValueDouble(val1 -> dval - val2 -> dval);
};
static Value *multIntInt(Value *val1, Value *val2) {
    return newValueInt(val1 -> ival * val2 -> ival);
};
static Value *multIntDouble(Value *val1, Value *val2) {
    return newValueDouble(val1 -> ival * val2 -> dval);
};
static Value *multStringInt(Value *val1, Value *val2) {
    return newValueInt(atoi(val1 -> sval) * val2 -> ival);
};
static Value *multStringDouble(Value *val1, Value *val2) {
    return newValueDouble(atof(val1 -> sval) * val2 -> dval);
};
static Value *multDoubleDouble(Value *val1, Value *val2) {
    return newValueDouble(val1 -> dval * val2 -> dval);
};
static Value *divIntInt(Value *val1, Value *val2) {
    return newValueInt(val1 -> ival / val2 -> ival);
};
static Value *divIntDouble(Value *val1, Value *val2) {
    return newValueDouble(val1 -> ival / val2 -> dval);
};
static Value *divDoubleInt(Value *val1, Value *val2) {
    return newValueDouble(val1 -> dval / val2 -> ival);
};
static Value *divStringInt(Value *val1, Value *val2) {
    return newValueInt(atoi(val1 -> sval) / val2 -> ival);
};
static Value *divIntString(Value *val1, Value *val2) {
    return newValueInt(val1 -> ival / atoi(val2 -> sval));
};
static Value *divStringDouble(Value *val1, Value *val2) {
    return newValueDouble(atof(val1 -> sval) / val2 -> dval);
};
static Value *divDoubleString(Value *val1, Value *val2) {
    return newValueDouble(val1 -> dval / atof(val2 -> sval));
};
static Value *divDoubleDouble(Value *val1, Value *val2) {
    return newValueDouble(val1 -> dval / val2 -> dval);
};
static Value *modIntInt(Value *val1, Value *val2) {
    return newValueInt(val1 -> ival % val2 -> ival);
};
static Value *modIntString(Value *val1, Value *val2) {
    return newValueInt(val1 -> ival % atoi(val2 -> sval));
};
static Value *modStringInt(Value *val1, Value *val2) {
    return newValueInt(atoi(val1 -> sval) % val2 -> ival);
};
static Value *powIntInt(Value *val1, Value *val2) {
    return newValueInt((int) pow((double) val1 -> ival, (double) val2 -> ival));
};
static Value *powIntDouble(Value *val1, Value *val2) {
    return newValueDouble(pow((double) val1 -> ival, val2 -> dval));
};
static Value *powDoubleInt(Value *val1, Value *val2){
    return newValueDouble(pow(val1 -> dval, (double) val2 -> ival));
};
static Value *powDoubleDouble(Value *val1, Value *val2) {
    return newValueDouble(pow(val1 -> dval, val2 -> dval));
};
static Value *powStringInt(Value *val1, Value *val2) {
    return newValueInt((int) pow(atof(val1 -> sval), (double) val2 -> ival));
};
static Value *powIntString(Value *val1, Value *val2) {
    return newValueInt((int) pow((double) val1 -> ival, atof(val2 -> sval)));
};
static Value *powStringDouble(Value *val1, Value *val2) {
    return newValueDouble(pow(atof(val1 -> sval), val2 -> dval));
};
static Value *powDoubleString(Value *val1, Value *val2) {
    return newValueDouble(pow(val1 -> dval, atof(val2 -> sval)));
};
static char *concat(char *a, char *b) {
    char *c = malloc(sizeof(char) * (strlen(a) + strlen(b) + 1));
    if (c == NULL)
        Fatal("Out of Memory\n");
    sprintf(c, "%s%s", a, b);
    return c;
};

static Value *isInitialized(Value *v) {
    Value *tempVariable = findValue(root, v);
    if (tempVariable == NULL)
        Fatal("Variable %s was not declared\n", v -> sval);
    return tempVariable;
};
