#include <stdlib.h>
#include "fatal.h"
#include "bst.h"
#include <string.h>

/*
 * bst.c
 *
 * Implementation of a standard binary search tree
 *
 * Written by Jacob Tucker
 */

static TreeNode *findNode(TreeNode *, Value *);
/*
 * PUBLIC FUNCTIONS
 */

/*
 * Inserts a key-data pair into the binary search tree
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

/*
 * Returns the data paired with the given key
 */
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

/*
 * Pairs the key with a different data value
 */
TreeNode *changeNodeData(TreeNode *treeNode ,Value *key, Value *data) {
    TreeNode *node = findNode(treeNode, key);
    if (node == NULL) 
        treeNode = insertTreeNode(treeNode, key, data);
    else
        node -> data = data;
    return treeNode;
};

/*
 * Returns if the tree is empty
 */
bool isEmptyTree(TreeNode *treeNode) {
    if (treeNode == NULL)
        return true;
    return false;
};

/*
 * Creates a key-data pair
 */
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

/*
 * Returns the node assosciated with its key
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
