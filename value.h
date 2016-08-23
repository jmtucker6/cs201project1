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

extern Value *newValueInt(int);
extern Value *newValueDouble(double);
extern Value *newValueString(char *);
extern Value *newValueVariable(char *);
extern Value *newValueOperator(char *);
