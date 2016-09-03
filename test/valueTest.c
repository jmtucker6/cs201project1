#include "../value.h"
#include "../scanner.h"
#include <stdio.h>

int main(void) {
    printf("Enter an int: ");
    Value *intVal = NULL;
    intVal = newValueInt(readInt(stdin));
    printf("Type: %d\n", intVal -> type);
    printf("Value: %d\n", intVal -> ival);
    
    printf ("Enter a double: ");
    Value *doubleVal = NULL;
    doubleVal = newValueDouble(readReal(stdin));
    printf("Type: %d\n", doubleVal -> type);
    printf("Value: %f\n", doubleVal -> dval);
    
    printf ("Enter a string: ");
    Value *stringVal = NULL;
    stringVal = newValueString(readString(stdin));
    printf("Type: %d\n", stringVal -> type);
    printf("Value: %s\n", stringVal -> sval);
   return 0;
};
