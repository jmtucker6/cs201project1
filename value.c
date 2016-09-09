#include <stdlib.h>
#include "value.h"
#include "fatal.h"

/*
 * value.c
 *
 * Implementation of value objects
 * Written by Jacob Tucker
 */

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

int EQUALS = 0;
int PARENTHESES = 10;
int ADD = 2;
int SUB = 3;
int MULT = 4;
int DIV = 5;
int MOD = 6;
int POW = 7;

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
    if (*s == '+')
        val -> ival = ADD;
    else if (*s == '-')
        val -> ival = SUB;
    else if (*s == '*' || *s == '/')
        val -> ival = MULT;
    else if (*s == '/')
        val -> ival = DIV;
    else if (*s == '=')
        val -> ival = EQUALS;
    else if (*s == '%')
        val -> ival = MOD;
    else if (*s == '^')
        val -> ival = POW;
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
    if (v == NULL)
        Fatal("Out of Memory");
    v -> type = t;
    v -> ival = 0;
    v -> dval = 0;
    v -> sval = 0;
    return v;
};

