#ifndef LIST_H
#define LIST_H

typedef struct List *list;

typedef struct List{
    
    char data;
    list next;

} List;

list newListNode(char data);
void freeList(list l);

void printList(list l);

#endif