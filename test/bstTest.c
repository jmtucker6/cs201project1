#include "../value.h"
#include "../bst.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    Value *a = newValueString("a");
    Value *aData = newValueInt(1);
    Value *b = newValueString("b");
    Value *bData = newValueInt(2);

    TreeNode *root = newTreeNode(a, aData);
    insertTreeNode(root, b, bData);
    printf("Inserted\n");
    Value *ab = newValueString("ab");
    Value *abData = newValueDouble(1.5);
    insertTreeNode(root, ab, abData);
    changeNodeData(root, a, newValueInt(100));
    printf("%d\n", findValue(root, a) -> ival);
    return 0;
}
