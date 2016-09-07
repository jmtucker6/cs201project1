#include "value.h"
#include <stdbool.h>
typedef struct TreeNode {
    Value *data;
    Value *key;
    struct TreeNode *left;
    struct TreeNode *right;

} TreeNode;


extern TreeNode *insertTreeNode(TreeNode *,Value *, Value *);
extern Value *findValue(TreeNode *, Value *);
extern bool isEmptyTree(TreeNode *);
extern TreeNode *newTreeNode(Value *, Value *);
