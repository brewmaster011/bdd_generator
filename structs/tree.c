#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tree.h"
#include "list.h"

Tree newTreeNode(char data){

    Tree node = malloc(sizeof(Tree));
    assert(node != NULL);

    node->data = data;

    node->left = NULL;
    node->right = NULL;
    return node;
}

void listToTree(List l, Tree *t){

    while(l != NULL){

        Tree left = NULL;
        Tree right = NULL;

        switch (l->data){
        case '~':

            left = *t;
            *t = newTreeNode('~');
            (*t)->left = left;
            
            break;

        case '&':

            left = *t;
            *t = newTreeNode('&');
            (*t)->left = left;

            right = newTreeNode(l->next->data);
            (*t)->right = right;

            break;
        
        default:
            switch ((*t)->data){
            case '~':

                (*t)->left = newTreeNode(l->data);
                
                break;

            case '&':
            
                if((*t)->left == NULL) (*t)->left = newTreeNode(l->data);
                else (*t)->right = newTreeNode(l->data);

            default:
                break;
            }
            break;
        }
        l = l->next;
    }
}

void printTree(Tree t){

    if(t == NULL) return;

    printTree(t->left);
    printTree(t->right);

    printf("%c ", t->data);
}

void freeTree(Tree t){

    if(t == NULL) return;
    
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}