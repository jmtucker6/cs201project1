#include "processEquation.h"
#include "fatal.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Value *add(Value *, Value *);
static Value *sub(Value *, Value *);
static Value *mult(Value *, Value *);
static Value *divide(Value *, Value *);
static Value *mod(Value *, Value *);
static Value *power(Value *, Value *);
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
static Value *poweDoubleInt(Value *, Value *);
static Value *powDoubleDouble(Value *, Value *);
static Value *powStringInt(Value *, Value *);
static Value *powIntString(Value *, Value *);
static Value *powStringDouble(Value *, Value *);
static Value *powDoubleString(Value *, Value *);
static char *concat(char *, char *);

Value *processEquation(Queue *);

/*
 * PRIVATE FUNCTIONS
 */

/*
 * Calls additionhelper function for every combination 
 * of INTEGER, DOUBLE, and STRING
 */
static Value *add(Value *val1, Value *val2) {
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
static Value *sub(Value *val1, Value *val2) {
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
            Fatal("Cannot subtract strings");
    };
    return NULL;
};
static Value *mult(Value *val1, Value *val2) {;
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
            return subStringDouble(val1, val2);
        else
            Fatal("Cannot multiply strings");
    };
    return NULL;
};
static Value *divide(Value *val1, Value *val2);
static Value *mod(Value *val1, Value *val2);
static Value *power(Value *val1, Value *val2);
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
    return newValueDouble(atof(val1 -> sval) * val2 -> ival);
};
static Value *multDoubleDouble(Value *val1, Value *val2) {
    return newValueDouble(val1 -> dval * val2 -> dval);
};
static Value *divIntInt(Value *val1, Value *val2);
static Value *divIntDouble(Value *val1, Value *val2);
static Value *divDoubleInt(Value *val1, Value *val2);
static Value *divStringInt(Value *val1, Value *val2);
static Value *divIntString(Value *val1, Value *val2);
static Value *divStringDouble(Value *val1, Value *val2);
static Value *divDoubleString(Value *val1, Value *val2);
static Value *divDoubleDouble(Value *val1, Value *val2);
static Value *modIntInt(Value *val1, Value *val2);
static Value *modIntString(Value *val1, Value *val2);
static Value *modStringInt(Value *val1, Value *val2);
static Value *powIntInt(Value *val1, Value *val2);
static Value *powIntDouble(Value *val1, Value *val2);
static Value *poweDoubleInt(Value *val1, Value *val2);
static Value *powDoubleDouble(Value *val1, Value *val2);
static Value *powStringInt(Value *val1, Value *val2);
static Value *powIntString(Value *val1, Value *val2);
static Value *powStringDouble(Value *val1, Value *val2);
static Value *powDoubleString(Value *val1, Value *val2);
static char *concat(char *a, char *b) {
    char *c = malloc(sizeof(char) * (strlen(a) + strlen(b) + 1));
    if (c == NULL)
        Fatal("Out of Memory\n");
    sprintf(c, "%s%s", a, b);
    return c;
};
