#ifndef LINKED_H_
#define LINKED_H_

// Behaves like a stack
struct node {
    void* data;
    struct node* next;
};

typedef struct LinkedNodes {
    struct node* head;
    int size;
} LinkedList;

// Add an item to the front of the linked list
int add(LinkedList* list, void* data, int size);
// For use as a queue; slow, do not use
int addLast(LinkedList* list, void *data, int size);


// Pop an item from the front of the linked list
void* pop(LinkedList* list);

#endif // LINKED_H_
