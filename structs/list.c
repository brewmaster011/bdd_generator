#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "list.h"

List newListNode(char data){

    List node = malloc(sizeof(List));
    assert(node != NULL);

    node->data = data;
    node->next = NULL;

    return node;
}

List readIntoList(char *array){

    List head = newListNode(array[0]);
    List next = newListNode(array[1]);
    List after = NULL;
    head->next = next;

    for(int i = 2; i < strlen(array); i++){

        after = newListNode(array[i]);
        next->next = after;
        next = after;
    }
    return head;
}

void freeList(List l){

    if(l == NULL) return;

    freeList(l->next);
    free(l);
}

void printList(List l){
    
    while(l != NULL){
        printf("%c", l->data);
        l = l->next;
    }
}