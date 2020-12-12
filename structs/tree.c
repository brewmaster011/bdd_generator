#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "tree.h"
#include "list.h"

Tree newTreeNode(char data, Tree left, Tree right){

    Tree node = malloc(sizeof(Tree));
    assert(node != NULL);

    node->data = data;

    node->left = left;
    node->right = right;
    return node;
}

int acceptChar(List *l, char c){

    if(*l != NULL && (*l)->data == c){
        *l = (*l)->next;
        return 1;
    }
    return 0;
}

int acceptIdentifier(Tree *t, List *l){

    if(*l != NULL && isalpha((*l)->data)){
        *t = newTreeNode((*l)->data, NULL, NULL);
        *l = (*l)->next;
        return 1;
    }
    return 0;
}

int acceptAtom(Tree *t, List *l){

    if(acceptIdentifier(t, l)) return 1;

    if(acceptChar(l, '(') && createTree(t, l) && acceptChar(l, ')')) return 1;

    return 0;
}

int checkNOT(Tree *t, List *l){

    if(acceptAtom(t, l)) return 1;

    if(acceptChar(l, '~')){
        Tree tL = NULL;
        if(acceptAtom(&tL, l)){
            *t = newTreeNode('~', tL, NULL);
            return 1;
        }
    }
    return 0;
}

int checkAND(Tree *t, List *l){

    if(!checkNOT(t, l)) return 0;

    while(acceptChar(l, '&')){
        Tree tL = *t;
        Tree tR = NULL;
        if(!checkNOT(&tR, l)){
            freeTree(tR);
            return 0;
        }
        *t = newTreeNode('&', tL, tR);
    }
    return 1;
}

int checkOR(Tree *t, List *l){

    if(!checkAND(t, l)) return 0;

    while(acceptChar(l, '|')){
        Tree tL = *t;
        Tree tR = NULL;
        if(!checkAND(&tR, l)){
            freeTree(tR);
            return 0;
        }
        *t = newTreeNode('|', tL, tR);
    }
    return 1;
}

int createTree(Tree *t, List *l){

    if(!checkOR(t, l)) return 0;
    return 1;
}

void printTree(Tree t){

    if(t == NULL) return;

    printf("%c", t->data);
    printTree(t->left);
    printTree(t->right);
}

void freeTree(Tree t){

    if(t == NULL) return;
    
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}