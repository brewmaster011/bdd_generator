#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tree.h"

tree newTreeNode(char data){

    tree node = malloc(sizeof(tree));
    assert(node != NULL);

    node->data = data;

    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(tree t){

    if(t == NULL){
        return;
    }
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}