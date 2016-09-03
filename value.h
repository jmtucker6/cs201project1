#ifndef VALUE_H
#define VALUE_H

typedef struct Value {
    int type;
    int ival;
    double dval;
    char *sval;
} Value;

extern int INTEGER;
extern int DOUBLE;
extern int STRING;
extern int VARIABLE;
extern int OPERATOR;
extern int SEMICOLON;

extern int PARENTHESES;
extern int ADD_SUB;
extern int MULT_DIV;

extern Value *newValueInt(int);
extern Value *newValueDouble(double);
extern Value *newValueString(char *);
extern Value *newValueVariable(char *);
extern Value *newValueOperator(char *);
extern Value *newValueSemicolon(char *);

#endif
