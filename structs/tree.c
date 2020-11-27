#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tree.h"

Tree newTreeNode(char data){

    Tree node = malloc(sizeof(Tree));
    assert(node != NULL);

    node->data = data;

    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(Tree t){

    if(t == NULL) return;
    
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}