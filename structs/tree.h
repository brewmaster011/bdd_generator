#ifndef TREE_H
#define TREE_H

#include "list.h"

typedef struct TreeNode *Tree;

typedef struct TreeNode{

    char data;
    Tree left;
    Tree right;

} TreeNode;

Tree newTreeNode(char data);
void listToTree(List l, Tree *t);

void freeTree(Tree t);
void printTree(Tree t);

#endif
