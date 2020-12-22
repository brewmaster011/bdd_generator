#ifndef LIST_H
#define LIST_H

typedef struct ListNode *List;

typedef struct ListNode{
    
    char data;
    List next;

} ListNode;

List newListNode(char data);
List readIntoList(char *array);

void freeList(List l);
void printList(List l);

#endif