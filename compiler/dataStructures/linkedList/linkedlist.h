#ifndef LINKED_H_
#define LINKED_H_

// Because, at least in its current form, nothing will ever be removed
// from this list, it's very straightforward to implement ;)

struct node {
    void* data;
    struct node* next;
};

typedef struct LinkedNodes {
    struct node* head;
    int size;
} LinkedList;

int add(LinkedList* list, void* data, size_t size);

#endif // LINKED_H_
