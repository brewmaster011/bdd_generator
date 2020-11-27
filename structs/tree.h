#ifndef TREE_H
#define TREE_H

typedef struct TreeNode *Tree;

typedef struct TreeNode{

    char data;
    Tree left;
    Tree right;

} TreeNode;

Tree newTreeNode(char data);
void freeTree(Tree t);

#endif
