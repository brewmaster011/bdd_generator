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
        // Tree right = NULL;

        switch (l->data){
        case '~':

            if((*t) == NULL) *t = newTreeNode('~');

            else if((*t)->left == NULL) {

                left = *t;
                *t = newTreeNode('~');
                (*t)->left = left;

            } else if ((*t)->right == NULL) (*t)->right = newTreeNode('~');

            break;

        case '&':

            left = *t;
            *t = newTreeNode('&');
            (*t)->left = left;

            break;
        
        default:
            switch ((*t)->data){
            case '~':

                (*t)->left = newTreeNode(l->data);
                
                break;

            case '&':
            
                if((*t)->left == NULL) (*t)->left = newTreeNode(l->data);

                else if ((*t)->right == NULL) (*t)->right = newTreeNode(l->data);

                else (*t)->right->left = newTreeNode(l->data);

                break;

            case '\0':

                *t = newTreeNode(l->data);
                break;

            default:
                printf("Why?\n");
                break;
            }
            break;
        }
        l = l->next;
    }
}

void printTree(Tree t){

    if(t == NULL) return;
    else printf("%c ", t->data);

    printTree(t->left);
    printTree(t->right);

    // printf("%c ", t->data);
}

void freeTree(Tree t){

    if(t == NULL) return;
    
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}