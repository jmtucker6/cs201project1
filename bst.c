#include <stdlib.h>
#include "fatal.h"
#include "bst.h"
#include <string.h>

static TreeNode *findNode(TreeNode *, Value *);
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
    if (isEmptyTree(treeNode))
        return NULL;
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

TreeNode *changeNodeData(TreeNode *treeNode ,Value *key, Value *data) {
    TreeNode *node = findNode(treeNode, key);
    if (node == NULL) 
        treeNode = insertTreeNode(treeNode, key, data);
    else
        node -> data = data;
    return treeNode;
};

bool isEmptyTree(TreeNode *treeNode) {
    if (treeNode == NULL)
        return true;
    return false;
};

TreeNode *newTreeNode(Value *key, Value *data) {
    TreeNode *treeNode = NULL;
    treeNode = malloc(sizeof(TreeNode));
    if (treeNode == NULL)
        Fatal("Out of Mememory\n");
    treeNode -> data = data;
    treeNode -> key = key;
    treeNode -> left = NULL;
    treeNode -> right = NULL;
    return treeNode;
};

/*
 * PRIVATE FUNCTIONS
 */

static TreeNode *findNode(TreeNode *treeNode, Value *key) {
    if (isEmptyTree(treeNode))
        return NULL;
    int comp = strcmp(key->sval, treeNode -> key -> sval);
    if (comp > 0) {
        return findNode(treeNode -> right, key);
    } else if (comp < 0) {
        return findNode(treeNode -> left, key);
    } else {
        return treeNode;
    }
    return NULL;
};
