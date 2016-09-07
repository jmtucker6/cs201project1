#include <stdlib.h>
#include "bst.h"
#include "fatal.h"
#include <string.h>

/*
 * PUBLIC FUNCTIONS
 */

TreeNode *insertTreeNode(TreeNode *treeNode, Value *key, Value *data) {
    if (treeNode == NULL) {
        treeNode = newTreeNode(key, data);
        return treeNode;
    }
    if (strcmp(key -> sval, treeNode -> key -> sval) <= 0) {
        treeNode -> left = insertTreeNode(treeNode -> left, key, data);
        return treeNode;
    } else {
        treeNode -> right = insertTreeNode(treeNode -> right, key, data);
        return treeNode;
    }
};

Value *findValue(TreeNode *treeNode, Value *key) {
    int comp = strcmp(key->sval, treeNode -> key -> sval);
    if (comp > 0) {
        return findValue(treeNode -> right, key);
    } else if (comp < 0) {
        return findValue(treeNode -> left, key);
    } else {
        return treeNode -> data;
    }
    return NULL;
};

bool isEmptyTree(TreeNode *treeNode) {
    if (treeNode == NULL)
        return true;
    return false;
};

TreeNode *newTreeNode(Value *key, Value *data) {
    TreeNode *treeNode = NULL;
    treeNode = malloc(sizeof(TreeNode));
    treeNode -> data = data;
    treeNode -> key = key;
    treeNode -> left = NULL;
    treeNode -> right = NULL;
    return treeNode;
};

/*
 * PRIVATE FUNCTIONS
 */
