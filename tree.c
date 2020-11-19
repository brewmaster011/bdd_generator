#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

tree newNode(char data){

    tree node = (tree)malloc(sizeof(tree));
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