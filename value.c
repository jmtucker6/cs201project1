#include <stdlib.h>
#include "value.h"

static Value *newValue(int);

/*
 * CONSTANT TYPE VALUES
 */

int INTEGER = 0;
int DOUBLE = 1;
int STRING = 2;
int VARIABLE = 3;
int OPERATOR = 4;

/*
 * PUBLIC FUNCTIONS
 */

Value *newValueInt(int i) {
    Value *val = newValue(INTEGER);
    val -> ival = i;
    return val;
};

Value *newValueDouble(double d) {
    Value *val = newValue(DOUBLE);
    val -> dval = d;
    return val;
};

Value *newValueString(char *s) {
    Value *val = newValue(STRING);
    val -> sval = s;
    return val;
};

Value *newValueVariable(char *s) {
    Value *val = newValue(VARIABLE);
    val -> sval = s;
    return val;
};

Value *newValueOperator(char *s) {
    Value *val = newValue(OPERATOR);
    val -> sval = s;
    return val;
};

/*
 * PRIVATE FUNCTIONS
 */
static Value *newValue(int t) {
    Value *v = malloc(sizeof(Value));
    v -> type = t;
    v -> ival = 0;
    v -> dval = 0;
    v -> sval = 0;
    return v;
};

