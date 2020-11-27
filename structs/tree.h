#ifndef TREE_H
#define TREE_H

typedef struct Node *tree;

typedef struct Node{

    char data;
    tree left;
    tree right;

} Node;

tree newTreeNode(char data);
void freeTree(tree t);

#endif
