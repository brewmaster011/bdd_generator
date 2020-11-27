#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

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
        printf("%c", l->data);
        l = l->next;
    }
}

list readIntoList(char *array){

    list head = newListNode(array[0]);
    list next = newListNode(array[1]);
    list after = NULL;
    head->next = next;

    for(int i = 2; i < strlen(array); i++){
        after = newListNode(array[i]);
        next->next = after;
        next = after;
    }
    return head;
}