#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "list.h"

list newListNode(char data){

    list node = malloc(sizeof(list));
    assert(node != NULL);

    node->data = data;
    node->next = NULL;

    return node;
}

void freeList(list l){

    if(l == NULL) return;

    freeList(l->next);
    free(l);
}

void printList(list l){
    
    while(l != NULL){
        printf("%c ", l->data);
        l = l->next;
    }
}