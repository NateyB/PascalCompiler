#include<stdlib.h>
#include<string.h>
#include<stdio.h> // TODO Remove

#include "../dataStructures/linkedList/linkedList.h"
#include "symbolTable.h"

LinkedList* symbolTable;

int initSymbolTable()
{
    symbolTable = malloc(sizeof(*symbolTable));
    symbolTable -> head = 0;
    return 0;
}

char* pushToSymbolTable(char* name, size_t length)
{
    add(symbolTable, name, sizeof(char)*length);
    return (char *)(symbolTable -> head -> data);
}

char* checkSymbolTable(char* word)
{
    // Then check the symbol table
    struct node* node = symbolTable -> head;
    while (node)
    {
        if (strcmp((char *) node -> data, word) == 0) // Match
            return (char *)(node -> data);
        node = node -> next;
    }

    return NULL;
}
