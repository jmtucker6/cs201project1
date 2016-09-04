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
int SEMICOLON = 5;

/*
 * CONSTANT PRECEDENCE LEVELS
 */

int PARENTHESES = 1;
int ADD_SUB = 2;
int MULT_DIV = 3;

/*
 * PUBLIC FUNCTIONS
 */

/*
 * Creates an integer value
 */
Value *newValueInt(int i) {
    Value *val = newValue(INTEGER);
    val -> ival = i;
    return val;
};

/*
 * Creates a double value
 */
Value *newValueDouble(double d) {
    Value *val = newValue(DOUBLE);
    val -> dval = d;
    return val;
};

/*
 * Creates a string value
 */
Value *newValueString(char *s) {
    Value *val = newValue(STRING);
    val -> sval = s;
    return val;
};

/*
 * Creates a variable value
 */
Value *newValueVariable(char *s) {
    Value *val = newValue(VARIABLE);
    val -> sval = s;
    return val;
};

/*
 * Creates an operator value
 */
Value *newValueOperator(char *s) {
    Value *val = newValue(OPERATOR);
    val -> sval = s;
    if (*s == '+' || *s == '-')
        val -> ival = ADD_SUB;
    else if (*s == '*' || *s == '/')
        val -> ival = MULT_DIV;
    else 
        val -> ival = PARENTHESES;
    return val;
};

/*
 * Creates a semicolon value
 */
Value *newValueSemicolon(char *s) {
    Value *val = newValue(SEMICOLON);
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

