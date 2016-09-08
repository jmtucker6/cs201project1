#include "value.h"
#include <stdbool.h>

#ifndef BST_H
#define BST_H

typedef struct TreeNode {
    Value *data;
    Value *key;
    struct TreeNode *left;
    struct TreeNode *right;

} TreeNode;


extern TreeNode *insertTreeNode(TreeNode *,Value *, Value *);
extern Value *findValue(TreeNode *, Value *);
extern TreeNode *changeNodeData(TreeNode *, Value *, Value *);
extern bool isEmptyTree(TreeNode *);
extern TreeNode *newTreeNode(Value *, Value *);

#endif
