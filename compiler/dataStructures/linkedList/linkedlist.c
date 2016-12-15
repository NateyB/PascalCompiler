#include<stdlib.h>
#include<stdio.h>

#include "linkedlist.h"


int add(LinkedList* list, void *data, int size)
{
    struct node* addition = malloc(sizeof(*addition));
    addition -> data = malloc(size);
    addition -> next = (list -> head);
    // Do a byte-by-byte copy of the data
    for (int i = 0; i < size; i++)
        *(char *) (addition -> data + i) = *(char *) (data + i);
    list -> size++;

    list -> head = addition;

    return list -> size;
}

// For use as a queue; slow, do not use
int addLast(LinkedList* list, void *data, int size)
{
    struct node* addition = malloc(sizeof(*addition));
    addition -> data = malloc(size);
    addition -> next = NULL;

    for (int i = 0; i < size; i++)
        *(char *) (addition -> data + i) = *(char *) (data + i);

    struct node* current = list -> head;

    if (list -> size == 0)
        list -> head = addition;
    else {
        while (current -> next != NULL)
            current = current -> next;

        current -> next = addition;
    }
    list -> size++;

}

void* pop(LinkedList* list)
{
    struct node* head = list -> head;
    struct node* next = head -> next;

    void* data = head -> data;
    list -> head = next;
    list -> size--;

    //free(head); // TODO this is necessary; should fix
    return data;
}
